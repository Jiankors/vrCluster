// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrCameraComponent.h"
#include "UvrScreenComponent.h"
#include "UvrRoot.h"


struct IUvrGameManager
{
	virtual ~IUvrGameManager()
	{ }

	virtual AUvrRoot*                    GetRoot() const = 0;

	virtual UUvrScreenComponent*         GetActiveScreen() const = 0;
	virtual UUvrScreenComponent*         GetScreenById(const FString& id) const = 0;
	virtual TArray<UUvrScreenComponent*> GetAllScreens() const = 0;
	virtual int32                        GetScreensAmount() const = 0;

	virtual UUvrCameraComponent*         GetActiveCamera() const = 0;
	virtual UUvrCameraComponent*         GetCameraById(const FString& id) const = 0;
	virtual TArray<UUvrCameraComponent*> GetAllCameras() const = 0;
	virtual int32                        GetCamerasAmount() const = 0;
	virtual void                         SetActiveCamera(int32 idx) = 0;
	virtual void                         SetActiveCamera(const FString& id) = 0;

	virtual UUvrSceneComponent*          GetNodeById(const FString& id) const = 0;
	virtual TArray<UUvrSceneComponent*>  GetAllNodes() const = 0;

	virtual USceneComponent*             GetTranslationDirectionComponent() const = 0;
	virtual void                         SetTranslationDirectionComponent(USceneComponent* const pComp) = 0;
	virtual void                         SetTranslationDirectionComponent(const FString& id) = 0;

	virtual USceneComponent*             GetRotateAroundComponent() const = 0;
	virtual void                         SetRotateAroundComponent(USceneComponent* const pComp) = 0;
	virtual void                         SetRotateAroundComponent(const FString& id) = 0;
};
