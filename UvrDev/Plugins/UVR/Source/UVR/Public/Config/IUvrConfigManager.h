// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrConfigTypes.h"


struct IUvrConfigManager
{
	virtual ~IUvrConfigManager()
	{ }

	virtual int32 GetClusterNodesAmount() const = 0;
	virtual TArray<SUvrConfigClusterNode> GetClusterNodes() const = 0;
	virtual bool GetClusterNode(int32 idx, SUvrConfigClusterNode& cnode) const = 0;
	virtual bool GetClusterNode(const FString& id, SUvrConfigClusterNode& cnode) const = 0;
	virtual bool GetMasterClusterNode(SUvrConfigClusterNode& cnode) const = 0;
	virtual bool GetLocalClusterNode(SUvrConfigClusterNode& cnode) const = 0;

	virtual int32 GetScreensAmount() const = 0;
	virtual TArray<SUvrConfigScreen> GetScreens() const = 0;
	virtual bool GetScreen(int32 idx, SUvrConfigScreen& screen) const = 0;
	virtual bool GetScreen(const FString& id, SUvrConfigScreen& screen) const = 0;
	virtual bool GetLocalScreen(SUvrConfigScreen& screen) const = 0;

	virtual int32 GetCamerasAmount() const = 0;
	virtual TArray<SUvrConfigCamera> GetCameras() const = 0;
	virtual bool GetCamera(int32 idx, SUvrConfigCamera& camera) const = 0;
	virtual bool GetCamera(const FString& id, SUvrConfigCamera& camera) const = 0;

	virtual int32 GetViewportsAmount() const = 0;
	virtual TArray<SUvrConfigViewport> GetViewports() const = 0;
	virtual bool GetViewport(int32 idx, SUvrConfigViewport& viewport) const = 0;
	virtual bool GetViewport(const FString& id, SUvrConfigViewport& viewport) const = 0;
	virtual bool GetLocalViewport(SUvrConfigViewport& screen) const = 0;

	virtual int32 GetSceneNodesAmount() const = 0;
	virtual TArray<SUvrConfigSceneNode> GetSceneNodes() const = 0;
	virtual bool GetSceneNode(int32 idx, SUvrConfigSceneNode& snode) const = 0;
	virtual bool GetSceneNode(const FString& id, SUvrConfigSceneNode& snode) const = 0;

	virtual int32 GetInputDevicesAmount() const = 0;
	virtual TArray<SUvrConfigInput> GetInputDevices() const = 0;
	virtual bool GetInputDevice(int32 idx, SUvrConfigInput& input) const = 0;
	virtual bool GetInputDevice(const FString& id, SUvrConfigInput& input) const = 0;

	virtual SUvrConfigGeneral GetConfigGeneral() const = 0;
	virtual SUvrConfigStereo  GetConfigStereo()  const = 0;
	virtual SUvrConfigRender  GetConfigRender()  const = 0;
	virtual SUvrConfigDebug   GetConfigDebug()   const = 0;
	virtual SUvrConfigCustom  GetConfigCustom()  const = 0;
};
