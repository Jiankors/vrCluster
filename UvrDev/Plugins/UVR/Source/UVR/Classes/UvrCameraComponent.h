// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrSceneComponent.h"
#include "UvrCameraComponent.generated.h"


UCLASS( ClassGroup=(Custom) )
class UVR_API UUvrCameraComponent : public UUvrSceneComponent
{
	GENERATED_BODY()

public:
	UUvrCameraComponent();

public:
	virtual void UvrSetSettings(const SUvrConfigSceneNode* const pConfig) override;
	virtual bool UvrApplySettings() override;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
