// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "GameFramework/HUD.h"
#include "UvrHUD.generated.h"


UCLASS()
class UVR_API AUvrHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUvrHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

public:
	static float ms_Threshold;
	static float ms_Delay;
	static float ms_Render;
	static int ms_policy;
private:

};

