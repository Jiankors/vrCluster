// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrSceneComponentSync.h"
#include "UvrSceneComponentSyncParent.generated.h"


// Synchronize parent scene component. Currently I use it to sync the root note which
// has a collision component as a root component.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UVR_API UUvrSceneComponentSyncParent :
	public UUvrSceneComponentSync
{
	GENERATED_BODY()

public:
	UUvrSceneComponentSyncParent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	virtual void DestroyComponent(bool bPromoteChildren) override;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrClusterSyncObject
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual FString GetSyncId() const override;

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// UUvrSceneComponentSync
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual FTransform GetSyncTransform() const override;
	virtual void SetSyncTransform(const FTransform& t) override;
};
