// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "GameFramework/PlayerController.h"
#include "UvrPlayerController.generated.h"

UCLASS()
class UVR_API AUvrPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
};

