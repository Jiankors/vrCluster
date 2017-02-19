// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrSceneComponentSyncThis.h"

#include "UvrPlugin.h"


UUvrSceneComponentSyncThis::UUvrSceneComponentSyncThis()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUvrSceneComponentSyncThis::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void UUvrSceneComponentSyncThis::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UUvrSceneComponentSyncThis::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrClusterSyncObject
//////////////////////////////////////////////////////////////////////////////////////////////
FString UUvrSceneComponentSyncThis::GetSyncId() const
{
	return FString::Printf(TEXT("ST_%s"), *GetOwner()->GetName());
}

//////////////////////////////////////////////////////////////////////////////////////////////
// UUvrSceneComponentSync
//////////////////////////////////////////////////////////////////////////////////////////////
FTransform UUvrSceneComponentSyncThis::GetSyncTransform() const
{
	return GetRelativeTransform();
}

void UUvrSceneComponentSyncThis::SetSyncTransform(const FTransform& t)
{
	SetRelativeTransform(t);
}
