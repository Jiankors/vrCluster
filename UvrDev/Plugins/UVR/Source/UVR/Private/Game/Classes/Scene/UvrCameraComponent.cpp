// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrCameraComponent.h"


UUvrCameraComponent::UUvrCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UUvrCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


void UUvrCameraComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UUvrCameraComponent::UvrSetSettings(const SUvrConfigSceneNode* const pConfig)
{
	Super::UvrSetSettings(pConfig);
}

bool UUvrCameraComponent::UvrApplySettings()
{
	return Super::UvrApplySettings();
}
