// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UVRBlueprintLibInput.generated.h"


UCLASS()
class UUVRBlueprintLibInput : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	//////////////////////////////////////////////////////////////////////////
	// Device information
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get amount of VRPN axis devices"), Category = "UVR|Input")
	static int32 UvrGetAxisDeviceAmount();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get amount of VRPN button devices"), Category = "UVR|Input")
	static int32 UvrGetButtonDeviceAmount();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get amount of VRPN tracker devices"), Category = "UVR|Input")
	static int32 UvrGetTrackerDeviceAmount();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get IDs of VRPN axis devices"), Category = "UVR|Input")
	static TArray<FString> UvrGetAxisDeviceIds();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get IDs of VRPN button devices"), Category = "UVR|Input")
	static TArray<FString> UvrGetButtonDeviceIds();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get IDs of VRPN tracker devices"), Category = "UVR|Input")
	static TArray<FString> UvrGetTrackerDeviceIds();

	//////////////////////////////////////////////////////////////////////////
	// Buttons
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get VRPN button state"), Category = "UVR|Input")
	static bool UvrGetButtonState(const FString& DeviceId, uint8 DeviceChannel);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is VRPN button pressed"), Category="UVR|Input")
	static bool UvrIsButtonPressed(const FString& DeviceId, uint8 DeviceChannel);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is VRPN button released"), Category="UVR|Input")
	static bool UvrIsButtonReleased(const FString& DeviceId, uint8 DeviceChannel);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Was VRPN button pressed"), Category="UVR|Input")
	static bool UvrWasButtonPressed(const FString& DeviceId, uint8 DeviceChannel);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Was VRPN button released"), Category="UVR|Input")
	static bool UvrWasButtonReleased(const FString& DeviceId, uint8 DeviceChannel);

	//////////////////////////////////////////////////////////////////////////
	// Axises
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get VRPN axis value"), Category="UVR|Input")
	static float UvrGetAxis(const FString& DeviceId, uint8 DeviceChannel);

	//////////////////////////////////////////////////////////////////////////
	// Trackers
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get VRPN tracker location"), Category="UVR|Input")
	static FVector UvrGetTrackerLocation(const FString& DeviceId, uint8 DeviceChannel);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get VRPN tracker rotation"), Category="UVR|Input")
	static FRotator UvrGetTrackerRotation(const FString& DeviceId, uint8 DeviceChannel);
};
