// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Components/SceneComponent.h"
#include "IUvrClusterSyncObject.h"
#include "UvrSceneComponentSync.generated.h"


UCLASS(Abstract)
class UVR_API UUvrSceneComponentSync :
	public USceneComponent,
	public IUvrClusterSyncObject
{
	GENERATED_BODY()

public:
	UUvrSceneComponentSync();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	virtual void DestroyComponent(bool bPromoteChildren) override;

protected:
	virtual FTransform GetSyncTransform() const
	{ return FTransform(); }

	virtual void SetSyncTransform(const FTransform& t)
	{ }

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrClusterSyncObject
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual FString GetSyncId() const override;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrStringSerializable
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual FString SerializeToString() const override final;
	virtual bool    DeserializeFromString(const FString& data) override final;

private:
	FString m_syncId;
};
