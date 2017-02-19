// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrSceneComponentSyncParent.h"

#include "UvrPlugin.h"


UUvrSceneComponentSyncParent::UUvrSceneComponentSyncParent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUvrSceneComponentSyncParent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void UUvrSceneComponentSyncParent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UUvrSceneComponentSyncParent::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);
}



//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrClusterSyncObject
//////////////////////////////////////////////////////////////////////////////////////////////
FString UUvrSceneComponentSyncParent::GetSyncId() const
{
	return FString::Printf(TEXT("SP_%s.%s"), *GetOwner()->GetName(), *GetAttachParent()->GetName());
}

//////////////////////////////////////////////////////////////////////////////////////////////
// UUvrSceneComponentSync
//////////////////////////////////////////////////////////////////////////////////////////////
FTransform UUvrSceneComponentSyncParent::GetSyncTransform() const
{
	return GetAttachParent()->GetRelativeTransform();
}

void UUvrSceneComponentSyncParent::SetSyncTransform(const FTransform& t)
{
	GetAttachParent()->SetRelativeTransform(t);
}
