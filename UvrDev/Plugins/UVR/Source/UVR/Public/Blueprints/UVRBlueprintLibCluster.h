// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UVRBlueprintLibCluster.generated.h"


UCLASS()
class UUVRBlueprintLibCluster : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is master node"), Category = "UVR|Cluster")
	static bool UvrIsMaster();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is slave node"), Category = "UVR|Cluster")
	static bool UvrIsSlave();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is cluster mode"), Category = "UVR|Cluster")
	static bool UvrIsCluster();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is standalone mode"), Category = "UVR|Cluster")
	static bool UvrIsStandalone();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get node ID"), Category = "UVR|Cluster")
	static FString UvrGetNodeId();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get nodes amount"), Category = "UVR|Cluster")
	static int32 UvrGetNodesAmount();
};
