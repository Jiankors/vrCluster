// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrGameMode.h"

#include "UvrPlugin.h"
#include "UvrRoot.h"
#include "UVR.h"

#include "UvrPlayerController.h"
#include "UvrHUD.h"



AUvrGameMode::AUvrGameMode() :
	Super()
{
	UE_LOG(LogUvrGame, Verbose, TEXT("AUvrGameMode .ctor"));

	DefaultPawnClass = AUvrRoot::StaticClass();
	PlayerControllerClass = AUvrPlayerController::StaticClass();
	HUDClass = AUvrHUD::StaticClass();
}

AUvrGameMode::~AUvrGameMode()
{
	UE_LOG(LogUvrGame, Verbose, TEXT("AUvrGameMode .dtor"));

	if (GEngine && GEngine->IsEditor())
	{
		UvrPlugin::get().EndSession();
		UvrPlugin::get().Release();
	}
}

void AUvrGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	UE_LOG(LogUvrGame, Verbose, TEXT("AUvrGameMode InitGame"));

	Super::InitGame(MapName, Options, ErrorMessage);

	if (GEngine && GEngine->IsEditor())
	{
		// Initialize UVR plugin
		if (!UvrPlugin::get().Init())
		{
			UE_LOG(LogUvrGame, Error, TEXT("Couldn't initialize UVR plugin"));
			GetWorld()->Exec(GetWorld(), TEXT("quit"));
			return;
		}
		
		// Firstly, check out if config file is specified in command line arguments because it has higher priority.
		// If no then in-scene settings will be used.
		FString cmdLineConfigPath;
		if (FParse::Value(FCommandLine::Get(), UvrStrings::args::Config, cmdLineConfigPath) == false)
		{
			UE_LOG(LogUvrConfig, Log, TEXT("No config file specified in command line. In-scene settings will be used."));
			cmdLineConfigPath = AUVR::ms_EditorConfigPath;
		}

		// Starting session
		if (!UvrPlugin::get().StartSession(cmdLineConfigPath))
		{
			UE_LOG(LogUvrGame, Error, TEXT("Couldn't start UVR session"));
			GetWorld()->Exec(GetWorld(), TEXT("quit"));
			return;
		}
	}
}

void AUvrGameMode::StartPlay()
{
	UE_LOG(LogUvrGame, Verbose, TEXT("AUvrGameMode StartPlay"));

	Super::StartPlay();
}

void AUvrGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine && GEngine->IsEditor())
	{
		if (!UvrPlugin::get().StartGame(GetWorld()))
		{
			UE_LOG(LogUvrGame, Error, TEXT("Couldn't start game"));
			GetWorld()->Exec(GetWorld(), TEXT("quit"));
			return;
		}
	}
}

void AUvrGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GEngine && GEngine->IsEditor())
	{
		UvrPlugin::get().InputMgr->Update();
	}
}

