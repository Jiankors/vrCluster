// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrSceneComponentSync.h"
#include "UvrSceneComponentSyncThis.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UVR_API UUvrSceneComponentSyncThis :
	public UUvrSceneComponentSync
{
	GENERATED_BODY()

public:
	UUvrSceneComponentSyncThis();

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
