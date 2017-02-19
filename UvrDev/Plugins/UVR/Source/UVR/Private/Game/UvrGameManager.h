// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrRoot.h"
#include "UvrScreenComponent.h"
#include "UvrCameraComponent.h"


class UvrGameManager :
	public  IPUvrGameManager,
	private UvrNoncopyable,
	private UvrNonmoveable
{
public:
	UvrGameManager();
	virtual ~UvrGameManager();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool Init() override;
	virtual void Release() override;
	virtual bool StartSession(const FString& configPath) override;
	virtual void EndSession() override;
	virtual bool StartGame(UWorld* pWorld) override;
	virtual void EndGame() override;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrGameManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual AUvrRoot*                    GetRoot() const override;

	virtual UUvrScreenComponent*         GetActiveScreen() const override;
	virtual UUvrScreenComponent*         GetScreenById(const FString& id) const override;
	virtual TArray<UUvrScreenComponent*> GetAllScreens() const override;
	virtual int32                        GetScreensAmount() const override;

	virtual UUvrCameraComponent*         GetActiveCamera() const override;
	virtual UUvrCameraComponent*         GetCameraById(const FString& id) const override;
	virtual TArray<UUvrCameraComponent*> GetAllCameras() const override;
	virtual int32                        GetCamerasAmount() const override;
	virtual void                         SetActiveCamera(int32 idx) override;
	virtual void                         SetActiveCamera(const FString& id) override;

	virtual UUvrSceneComponent*          GetNodeById(const FString& id) const override;
	virtual TArray<UUvrSceneComponent*>  GetAllNodes() const override;

	virtual USceneComponent*             GetTranslationDirectionComponent() const override;
	virtual void                         SetTranslationDirectionComponent(USceneComponent* const pComp) override;
	virtual void                         SetTranslationDirectionComponent(const FString& id) override;

	virtual USceneComponent*             GetRotateAroundComponent() const override;
	virtual void                         SetRotateAroundComponent(USceneComponent* const pComp) override;
	virtual void                         SetRotateAroundComponent(const FString& id) override;

private:
	// Creates UVR actor and fulfills with components hierarchy
	bool InitializeUvrActor();

	bool CreateScreens();
	bool CreateNodes();
	bool CreateCameras();

	// Extracts array of values from a map
	template <typename ObjType>
	inline TArray<ObjType*> GetMapValues(const TMap<FString, ObjType*>& container) const
	{
		TArray<ObjType*> items;
		container.GenerateValueArray(items);
		return items;
	}

	// Gets item by id. Performs checks and logging.
	template <typename DataType>
	DataType* GetItem(const TMap<FString, DataType*>& container, const FString& id, const FString& logHeader) const
	{
		if (container.Contains(id))
			return container[id];

		UE_LOG(LogUvrGame, Warning, TEXT("%s: ID not found <%s>. Return nullptr."), *logHeader, *id);
		return nullptr;
	}

private:
	// Current UE world
	UWorld* m_pWorld = nullptr;

	// UVR root actor
	AUvrRoot* m_pRoot = nullptr;
	// Currently active projection screen (for this cluster node)
	UUvrScreenComponent* m_pScreen = nullptr;
	// Currently active camera (joint component)
	UUvrCameraComponent* m_pCamera = nullptr;

	// Available screens (from config file)
	TMap<FString, UUvrScreenComponent*> m_screens;
	// Available cameras (from config file)
	TMap<FString, UUvrCameraComponent*> m_cameras;
	// All available UVR nodes in hierarchy
	TMap<FString, UUvrSceneComponent*> m_nodes;

	// Sync access to the internals
	mutable FCriticalSection       m_sync;
};

