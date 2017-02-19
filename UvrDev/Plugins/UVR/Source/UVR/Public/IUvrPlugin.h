// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "ModuleManager.h"
#include "ModuleInterface.h"


struct IUvrRenderManager;
struct IUvrClusterManager;
struct IUvrInputManager;
struct IUvrConfigManager;
struct IUvrGameManager;

struct IUvrPlugin : public IModuleInterface
{
	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline IUvrPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked<IUvrPlugin>(IUvrPlugin::ModuleName);
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded(IUvrPlugin::ModuleName);
	}

	/**
	* Access to the device manager.
	*
	* @return Current device manager or nullptr
	*/
	virtual IUvrRenderManager* const GetRenderMgr() = 0;

	/**
	* Access to the cluster manager.
	*
	* @return Current cluster manager or nullptr
	*/
	virtual IUvrClusterManager* const GetClusterMgr() = 0;

	/**
	* Access to the input manager.
	*
	* @return Current cluster manager or nullptr
	*/
	virtual IUvrInputManager* const GetInputMgr() = 0;

	/**
	* Access to the config manager.
	*
	* @return Current config manager or nullptr
	*/
	virtual IUvrConfigManager* const GetConfigMgr() = 0;

	/**
	* Access to the game manager.
	*
	* @return Current game manager or nullptr
	*/
	virtual IUvrGameManager* const GetGameMgr() = 0;

private:
	static constexpr auto ModuleName = "UVR";
};
