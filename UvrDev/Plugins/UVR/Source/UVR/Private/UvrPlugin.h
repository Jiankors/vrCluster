// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrPlugin.h"


class UvrPlugin final :
	public  IUvrPlugin,
	private IPUvrManager
{
public:
	UvrPlugin();
	virtual ~UvrPlugin();

public:
	// Internal singleton like fast access.
	static inline UvrPlugin& get()
	{ return *ms_instance; }

	// Make it public for internal fast access from within plugin
	TUniquePtr<IPUvrClusterManager> ClusterMgr;
	TUniquePtr<IPUvrRenderManager>  RenderMgr;
	TUniquePtr<IPUvrInputManager>   InputMgr;
	TUniquePtr<IPUvrConfigManager>  ConfigMgr;
	TUniquePtr<IPUvrGameManager>    GameMgr;

public:
	// Internal access to the current world context
	inline UWorld* GetWorld() const
	{ return m_pWorld; }

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrPlugin
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual IUvrRenderManager*  const GetRenderMgr()  override { return RenderMgr.IsValid()  ? RenderMgr.Get()  : nullptr; }
	virtual IUvrClusterManager* const GetClusterMgr() override { return ClusterMgr.IsValid() ? ClusterMgr.Get() : nullptr; }
	virtual IUvrInputManager*   const GetInputMgr()   override { return InputMgr.IsValid()   ? InputMgr.Get()   : nullptr; }
	virtual IUvrConfigManager*  const GetConfigMgr()  override { return ConfigMgr.IsValid()  ? ConfigMgr.Get()  : nullptr; }
	virtual IUvrGameManager*    const GetGameMgr()    override { return GameMgr.IsValid()    ? GameMgr.Get()    : nullptr; }

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
	virtual void PreTick(float DeltaSeconds) override;
	virtual void PostTick(float DeltaSeconds) override;

private:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IModuleInterface
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//virtual void PreUnloadCallback() override;
	//virtual void PostLoadCallback() override;
	//virtual bool SupportsDynamicReloading() override;  // default is true
	//virtual bool SupportsAutomaticShutdown() override; // default is true
	//virtual bool IsGameModule() const override; default is false

private:
	// This instance (internal fast access)
	static UvrPlugin* ms_instance;
	// Current world
	UWorld* m_pWorld = nullptr;
};
