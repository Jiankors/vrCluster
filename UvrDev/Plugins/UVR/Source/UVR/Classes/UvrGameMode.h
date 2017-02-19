// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "GameFramework/GameMode.h"
#include "UvrGameMode.generated.h"

/**
 * This class is responsible for:
 * - spawning basic UVR classes (AUvrRoot, AUvrHud, AUvrController)
 * - basic in-editor debug (standalone mode)
 */
UCLASS()
class UVR_API AUvrGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AUvrGameMode();
	~AUvrGameMode();

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
};
