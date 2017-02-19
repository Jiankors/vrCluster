// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UVR.h"


FString AUVR::ms_EditorConfigPath = FString();
FString AUVR::ms_EditorNodeName   = FString();
bool AUVR::ms_EditorShowProjectionScreens = false;


AUVR::AUVR()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUVR::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUVR::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

#if WITH_EDITOR
void AUVR::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateUvrSettings();
}

void AUVR::PostLoad()
{
	Super::PostLoad();
	UpdateUvrSettings();
}

inline void AUVR::UpdateUvrSettings()
{
	UE_LOG(LogUvrGame, Log, TEXT("UVR editor settings update:\nConfig path: %s\nNode name: %s"), *UvrEditorConfigPath, *UvrEditorNodeName);
	AUVR::ms_EditorConfigPath = UvrEditorConfigPath;
	AUVR::ms_EditorNodeName = UvrEditorNodeName;
	AUVR::ms_EditorShowProjectionScreens = UvrEditorShowProjectionScreens;
}
#endif
