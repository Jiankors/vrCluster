// Copyright 2016 Pixela Labs. All Rights Reserved.
// Fill out your copyright notice in the Description page of Project Settings.

#include "UvrPrivatePCH.h"
#include "UvrGameEngine.h"

#include "UvrPlugin.h"


void UUvrGameEngine::Init(class IEngineLoop* InEngineLoop)
{
	UE_LOG(LogUvrEngine, VeryVerbose, TEXT("UUvrGameEngine::Init"));

	m_bIsCluster = FParse::Param(FCommandLine::Get(), UvrStrings::args::Cluster);

	if (m_bIsCluster)
	{
		// Initialize UVR
		if (!UvrPlugin::get().Init())
			UvrAppExit::ExitApplication(UvrAppExit::ExitType::KillImmediately, FString("Couldn't initialize UVR plugin"));

		// Save config path from command line
		FString configPath;
		if (!FParse::Value(FCommandLine::Get(), UvrStrings::args::Config, configPath))
			UE_LOG(LogUvrEngine, Warning, TEXT("No config file specified"));

		// Prepare the path
		UvrHelpers::str::DustCommandLineValue(configPath);

		// Start game session
		if (!UvrPlugin::get().StartSession(configPath))
			UvrAppExit::ExitApplication(UvrAppExit::ExitType::KillImmediately, FString("Couldn't start UVR session"));

		// Initialize base stuff.
		UGameEngine::Init(InEngineLoop);

		// Initialize internals
		UvrInitializeEngine();
	}
	else
	{
		// Initialize base stuff.
		UGameEngine::Init(InEngineLoop);
	}
}

bool UUvrGameEngine::UvrInitializeEngine()
{
	UE_LOG(LogUvrEngine, VeryVerbose, TEXT("UUvrGameEngine::UvrInitializeEngine"));
	
	// Store debug settings locally
	m_CfgDebug = UvrPlugin::get().ConfigMgr->GetConfigDebug();

	return true;
}

void UUvrGameEngine::PreExit()
{
	UE_LOG(LogUvrEngine, VeryVerbose, TEXT("UUvrGameEngine::PreExit"));

	if (m_bIsCluster)
	{
		// Process end game to release in-level resources
		UvrPlugin::get().EndGame();
		// Perform UVR pre-exit before internal engine release
		UvrPlugin::get().EndSession();
		// Release the engine
		UGameEngine::PreExit();
		// Release UVR
		UvrPlugin::get().Release();
	}
	else
	{
		// Release the engine
		UGameEngine::PreExit();
	}
}

bool UUvrGameEngine::LoadMap(FWorldContext& WorldContext, FURL URL, class UPendingNetGame* Pending, FString& Error)
{
	UE_LOG(LogUvrEngine, VeryVerbose, TEXT("UUvrGameEngine::LoadMap"));

	if (m_bIsCluster)
	{
		// Stop current map
		UvrPlugin::get().EndGame();

		// Perform map loading
		if (!Super::LoadMap(WorldContext, URL, Pending, Error))
			return false;

		// Start new map
		UvrPlugin::get().StartGame(WorldContext.World());

		// Game start barrier
		UvrPlugin::get().ClusterMgr->GetController()->WaitForGameStart();
	}
	else
	{
		// Perform map loading
		if (!Super::LoadMap(WorldContext, URL, Pending, Error))
			return false;
	}

	return true;
}

void UUvrGameEngine::Tick(float DeltaSeconds, bool bIdleMode)
{
	UE_LOG(LogUvrEngine, VeryVerbose, TEXT("UUvrGameEngine::Tick"));

	if (m_bIsCluster)
	{
		// Get internals
		const auto& clusterMgr = UvrPlugin::get().ClusterMgr;
		const auto& inputMgr = UvrPlugin::get().InputMgr;
		auto* const controller = clusterMgr->GetController();

		// Update input device state (master only)
		inputMgr->Update();

		// Update delta time. Cluster slaves will get this value from the master few steps later
		clusterMgr->SetDeltaTime(DeltaSeconds);

		// Sync cluster objects
		clusterMgr->SyncObjects();

		//////////////////////////////////////////////////////////////////////////////////////////////
		// Frame start barrier
		controller->WaitForFrameStart();
		UE_LOG(LogUvrEngine, Verbose, TEXT("Sync frame start"));

		// Get UVR time delta
		controller->GetDeltaTime(DeltaSeconds);
		UE_LOG(LogUvrEngine, Log, TEXT("UVR delta time (seconds): %f"), DeltaSeconds);

		// Update delta time in the application
		FApp::SetDeltaTime(DeltaSeconds);

		// Update input state in the cluster
		clusterMgr->SyncInput();

		// Perform PreTick for UVR plugin
		UE_LOG(LogUvrEngine, Verbose, TEXT("Perform PreTick()"));
		UvrPlugin::get().PreTick(DeltaSeconds);

		// Perform Tick() calls for scene actors
		UE_LOG(LogUvrEngine, Verbose, TEXT("Perform Tick()"));
		Super::Tick(DeltaSeconds, bIdleMode);

		if (m_CfgDebug.LagSimulateEnabled)
		{
#if 1
			const float lag = FMath::RandRange(0.f, m_CfgDebug.LagMaxTime);
#else
			const float lag = m_CfgDebug.LagMaxTime;
#endif
			UE_LOG(LogUvrEngine, Log, TEXT("Simulating lag: %f seconds"), lag);
			FPlatformProcess::Sleep(lag);
		}

		// Perform PostTick for UVR plugin
		UE_LOG(LogUvrEngine, Verbose, TEXT("Perform PostTick()"));
		UvrPlugin::get().PostTick(DeltaSeconds);

#if 0
		//////////////////////////////////////////////////////////////////////////////////////////////
		// Tick end barrier
		controller->WaitForTickEnd();
#endif

#if 0
		//////////////////////////////////////////////////////////////////////////////////////////////
		// Frame end barrier
		controller->WaitForFrameEnd();
		UE_LOG(LogUvrEngine, Verbose, TEXT("Sync frame end"));
#endif
	}
	else
	{
		Super::Tick(DeltaSeconds, bIdleMode);
	}
}

