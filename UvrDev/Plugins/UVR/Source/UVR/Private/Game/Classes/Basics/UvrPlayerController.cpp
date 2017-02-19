// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrPlayerController.h"

#include "UvrPlugin.h"


void AUvrPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (WasInputKeyJustPressed(EKeys::Escape))
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, FString("Exit on ESC requested"));
}

void AUvrPlayerController::BeginPlay()
{
	Super::BeginPlay();

#if 0
	//@todo: temporary solution. we need generic UVR access to statistics
	SUvrConfigDebug cfgDebug = UvrPlugin::get().ConfigMgr->GetConfigDebug();
	if (cfgDebug.DrawStats)
	{
		UE_LOG(LogUvrGame, Log, TEXT("Activating onscreen stats"));
		ConsoleCommand(FString("stat fps"),  true);
		ConsoleCommand(FString("stat unit"), true);
	}
#endif
}

