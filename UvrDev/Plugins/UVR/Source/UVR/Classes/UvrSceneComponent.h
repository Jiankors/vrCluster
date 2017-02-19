// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Components/SceneComponent.h"
#include "Config/UvrConfigTypes.h"

#include "UvrSceneComponent.generated.h"


class UUvrSceneComponentSync;


UCLASS( ClassGroup=(Custom) )
class UVR_API UUvrSceneComponent :
	public USceneComponent
{
	GENERATED_BODY()

public:
	UUvrSceneComponent();

public:
	virtual void UvrSetSettings(const SUvrConfigSceneNode* const pConfig);
	virtual bool UvrApplySettings();

	inline FString UvrGetId() const
	{ return m_config.Id; }

	inline FString UvrGetParentId() const
	{ return m_config.ParentId; }

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	const SUvrConfigSceneNode m_config;
};
