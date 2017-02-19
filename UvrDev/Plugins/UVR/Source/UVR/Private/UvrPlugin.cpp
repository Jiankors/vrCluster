// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrPlugin.h"

#include "Cluster/UvrClusterManager.h"
#include "Config/UvrConfigManager.h"
#include "Game/UvrGameManager.h"
#include "Input/UvrInputManager.h"
#include "Render/UvrRenderManager.h"



UvrPlugin* UvrPlugin::ms_instance = nullptr;


UvrPlugin::UvrPlugin()
{
	UE_LOG(LogUvrPlugin, Verbose, TEXT("UvrPlugin .ctor"));
	UvrPlugin::ms_instance = this;
}

UvrPlugin::~UvrPlugin()
{
	UE_LOG(LogUvrPlugin, Verbose, TEXT("UvrPlugin .dtor"));
	if(UvrPlugin::ms_instance == this)
		UvrPlugin::ms_instance = nullptr;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IModuleInterface
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrPlugin::StartupModule()
{
	UE_LOG(LogUvrPlugin, Verbose, TEXT("StartupModule"));
}

void UvrPlugin::ShutdownModule()
{
	UE_LOG(LogUvrPlugin, Verbose, TEXT("ShutdownModule"));

	// Clean everything before .dtor call
	Release();
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrPlugin
//////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrManager
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrPlugin::Init()
{
	UE_LOG(LogUvrPlugin, Log, TEXT("Init"));

	// Initialize internals
	ConfigMgr.Reset(new UvrConfigManager);
	ClusterMgr.Reset(new UvrClusterManager);
	InputMgr.Reset(new UvrInputManager);
	GameMgr.Reset(new UvrGameManager);
	RenderMgr.Reset(new UvrRenderManager);

	//@note: I use if-based solution instead of 'result = result && mgr->Init()' to allow
	// all managers to be initialized even if some have previously failed. UE4 compiler
	// optimization settings breaks the idea and not further initialization performed
	// after first fail.
	bool result = true;
	if (!ConfigMgr->Init())  result = false;
	if (!ClusterMgr->Init()) result = false;
	if (!InputMgr->Init())   result = false;
	if (!GameMgr->Init())    result = false;
	if (!RenderMgr->Init())  result = false;

	return result;
}

void UvrPlugin::Release()
{
	UE_LOG(LogUvrPlugin, Log, TEXT("Release"));

	//@note: don't confuse with TUniquePtr.Release(). This one is IPUvrManager::Release() virtual call.
	if (ClusterMgr) ClusterMgr->Release();
	if (InputMgr)   InputMgr->Release();
	if (GameMgr)    GameMgr->Release();
	if (ConfigMgr)  ConfigMgr->Release();
	if (RenderMgr)  RenderMgr->Release();
}

bool UvrPlugin::StartSession(const FString& configPath)
{
	UE_LOG(LogUvrPlugin, Log, TEXT("StartSession: config path is %s"), *configPath);

	//@note: I use if-based solution instead of 'result = result && mgr->Init()' to allow
	// all managers to be initialized even if some have previously failed. UE4 compiler
	// optimization settings breaks the idea and not further initialization performed
	// after first fail.
	bool result = true;
	if (!ConfigMgr->StartSession(configPath))  result = false;
	if (!ClusterMgr->StartSession(configPath)) result = false;
	if (!InputMgr->StartSession(configPath))   result = false;
	if (!GameMgr->StartSession(configPath))    result = false;
	if (!RenderMgr->StartSession(configPath))  result = false;

	return result;
}

void UvrPlugin::EndSession()
{
	UE_LOG(LogUvrPlugin, Log, TEXT("EndSession"));

	if(ClusterMgr) ClusterMgr->EndSession();
	if(InputMgr)   InputMgr->EndSession();
	if(GameMgr)    GameMgr->EndSession();
	if(RenderMgr)  RenderMgr->EndSession();
	if(ConfigMgr)  ConfigMgr->EndSession();
}

bool UvrPlugin::StartGame(UWorld* pWorld)
{
	UE_LOG(LogUvrPlugin, Log, TEXT("StartGame"));
	check(pWorld);

	m_pWorld = pWorld;


	//@note: I use if-based solution instead of 'result = result && mgr->Init()' to allow
	// all managers to be initialized even if some have previously failed. UE4 compiler
	// optimization settings breaks the idea and not further initialization performed
	// after first fail.
	bool result = true;
	if (!ConfigMgr->StartGame(pWorld))  result = false;
	if (!ClusterMgr->StartGame(pWorld)) result = false;
	if (!InputMgr->StartGame(pWorld))   result = false;
	if (!GameMgr->StartGame(pWorld))    result = false;
	if (!RenderMgr->StartGame(pWorld))  result = false;

	return result;
}

void UvrPlugin::EndGame()
{
	UE_LOG(LogUvrPlugin, Log, TEXT("EndGame"));

	if (ClusterMgr) ClusterMgr->EndGame();
	if (InputMgr)   InputMgr->EndGame();
	if (GameMgr)    GameMgr->EndGame();
	if (RenderMgr)  RenderMgr->EndGame();
	if (ConfigMgr)  ConfigMgr->EndGame();
}

void UvrPlugin::PreTick(float DeltaSeconds)
{
	UE_LOG(LogUvrPlugin, Verbose, TEXT("PreTick: delta - %f"), DeltaSeconds);

	if (ConfigMgr)  ConfigMgr->PreTick(DeltaSeconds);
	if (ClusterMgr) ClusterMgr->PreTick(DeltaSeconds);
	if (InputMgr)   InputMgr->PreTick(DeltaSeconds);
	if (GameMgr)    GameMgr->PreTick(DeltaSeconds);
	if (RenderMgr)  RenderMgr->PreTick(DeltaSeconds);
}

void UvrPlugin::PostTick(float DeltaSeconds)
{
	UE_LOG(LogUvrPlugin, Verbose, TEXT("PostTick: delta - %f"), DeltaSeconds);

	if (ConfigMgr)  ConfigMgr->PostTick(DeltaSeconds);
	if (ClusterMgr) ClusterMgr->PostTick(DeltaSeconds);
	if (InputMgr)   InputMgr->PostTick(DeltaSeconds);
	if (GameMgr)    GameMgr->PostTick(DeltaSeconds);
	if (RenderMgr)  RenderMgr->PostTick(DeltaSeconds);
}


IMPLEMENT_MODULE(UvrPlugin, UVR)
