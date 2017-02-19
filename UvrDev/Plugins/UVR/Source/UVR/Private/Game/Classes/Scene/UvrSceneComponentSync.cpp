// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrSceneComponentSync.h"

#include "UvrPlugin.h"


UUvrSceneComponentSync::UUvrSceneComponentSync()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUvrSceneComponentSync::BeginPlay()
{
	Super::BeginPlay();

	// Generate unique sync id
	m_syncId = GetSyncId();

	// Register sync object
	if (UvrPlugin::get().ClusterMgr.IsValid())
	{
		UvrPlugin::get().ClusterMgr->RegisterSyncObject(this);
	}
	else
	{
		UE_LOG(LogUvrGame, Warning, TEXT("Couldn't register %s scene component sync. Looks like we're in non-UVR mode."), *m_syncId);
	}
}


void UUvrSceneComponentSync::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UUvrSceneComponentSync::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrClusterSyncObject
//////////////////////////////////////////////////////////////////////////////////////////////
FString UUvrSceneComponentSync::GetSyncId() const
{
	return FString::Printf(TEXT("S_%s"), *GetOwner()->GetName());
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrStringSerializable
//////////////////////////////////////////////////////////////////////////////////////////////
FString UUvrSceneComponentSync::SerializeToString() const
{
	return GetSyncTransform().ToString();
}

bool UUvrSceneComponentSync::DeserializeFromString(const FString& data)
{
	FTransform t;
	if (!t.InitFromString(data))
	{
		UE_LOG(LogUvrGame, Error, TEXT("Unable to deserialize transform data"));
		return false;
	}

	UE_LOG(LogUvrGame, Verbose, TEXT("%s: applying transform data <%s>"), *m_syncId, *t.ToHumanReadableString());
	SetSyncTransform(t);

	return true;
}
