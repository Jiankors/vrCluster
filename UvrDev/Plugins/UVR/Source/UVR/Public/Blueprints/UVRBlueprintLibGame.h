// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UVRBlueprintLibGame.generated.h"


UCLASS()
class UUVRBlueprintLibGame : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	//////////////////////////////////////////////////////////////////////////
	// Root
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get root"), Category = "UVR|Game")
	static AUvrRoot* UvrGetRoot();

	//////////////////////////////////////////////////////////////////////////
	// Screens
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get active screen"), Category = "UVR|Game")
	static UUvrScreenComponent* UvrGetActiveScreen();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get screen by ID"), Category = "UVR|Game")
	static UUvrScreenComponent* UvrGetScreenById(const FString& id);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get all screens"), Category = "UVR|Game")
	static TArray<UUvrScreenComponent*> UvrGetAllScreens();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get amount of screens"), Category = "UVR|Game")
	static int32 UvrGetScreensAmount();

	//////////////////////////////////////////////////////////////////////////
	// Cameras
	/*
	virtual UUvrCameraComponent*         GetActiveCamera() const = 0;
	virtual UUvrCameraComponent*         GetCameraById(const FString& id) const = 0;
	virtual TArray<UUvrCameraComponent*> GetAllCameras() const = 0;
	virtual int32                        GetCamerasAmount() const = 0;
	virtual void                         SetActiveCamera(int32 idx) = 0;
	virtual void                         SetActiveCamera(const FString& id) = 0;
	*/

	//////////////////////////////////////////////////////////////////////////
	// Nodes
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get node by ID"), Category = "UVR|Game")
	static UUvrSceneComponent* UvrGetNodeById(const FString& id);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get all nodes"), Category = "UVR|Game")
	static TArray<UUvrSceneComponent*> UvrGetAllNodes();

	//////////////////////////////////////////////////////////////////////////
	// Navigation
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get translation direction component"), Category = "UVR|Game")
	static USceneComponent* UvrGetTranslationDirectionComponent();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set translation direction component"), Category = "UVR|Game")
	static void UvrSetTranslationDirectionComponent(USceneComponent* const pComp);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set translation direction component by ID"), Category = "UVR|Game")
	static void UvrSetTranslationDirectionComponentId(const FString& id);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get rotate around component"), Category = "UVR|Game")
	static USceneComponent* UvrGetRotateAroundComponent();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set rotate around component"), Category = "UVR|Game")
	static void UvrSetRotateAroundComponent(USceneComponent* const pComp);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set rotate around component by ID"), Category = "UVR|Game")
	static void UvrSetRotateAroundComponentId(const FString& id);
};
