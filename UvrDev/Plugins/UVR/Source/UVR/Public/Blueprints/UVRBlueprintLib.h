// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UVRBlueprintLib.generated.h"


UCLASS()
class UUVRBlueprintLib : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get plugin version string"), Category = "UVR")
	static FString UvrGetVersionString();
};
