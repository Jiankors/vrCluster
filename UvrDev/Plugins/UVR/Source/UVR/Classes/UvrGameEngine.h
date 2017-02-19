// Copyright 2016 Pixela Labs. All Rights Reserved.
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameEngine.h"
#include "UvrGameEngine.generated.h"

/**
 * 
 */
UCLASS()
class UVR_API UUvrGameEngine : public UGameEngine
{
	GENERATED_BODY()
	
private:
	virtual void Init(class IEngineLoop* InEngineLoop) override;
	virtual void PreExit() override;
	virtual void Tick(float DeltaSeconds, bool bIdleMode) override;

	virtual bool LoadMap(FWorldContext& WorldContext, FURL URL, class UPendingNetGame* Pending, FString& Error) override;

protected:
	virtual bool UvrInitializeEngine();

private:
	SUvrConfigDebug m_CfgDebug;
	bool m_bIsCluster;
};
