// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Engine.h"
#include "IUvrStringSerializable.h"


//////////////////////////////////////////////////////////////////////////////////////////////
// Base interface for config data holders
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigBase : public IUvrStringSerializable
{
	virtual ~SUvrConfigBase()
	{ }

	// Prints in human readable format
	virtual FString ToString() const
	{ return FString("[]"); }

	// Currently no need to serialize the data
	virtual FString SerializeToString() const override final
	{ return FString(); }

	// Deserialization from config file
	virtual bool    DeserializeFromString(const FString& line) override
	{ return true; }
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Cluster node configuration (separate application)
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigClusterNode : public SUvrConfigBase
{
	FString Id;
	FString Addr;
	FString ScreenId;
	FString ViewportId;
	bool    IsMaster = false;
	int32   Port_CS = -1;
	int32   Port_SS = -1;

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Viewport configuration
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigViewport : public SUvrConfigBase
{
	FString   Id;
	FIntPoint Loc  = FIntPoint::ZeroValue;
	FIntPoint Size = FIntPoint::ZeroValue;
	bool FlipHorizontal = false;
	bool FlipVertical = false;

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Scene node configuration (UVR hierarchy is built from such nodes)
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigSceneNode : public SUvrConfigBase
{
	FString  Id;
	FString  ParentId;
	FVector  Loc = FVector::ZeroVector;
	FRotator Rot = FRotator::ZeroRotator;
	FString  TrackerId;
	int32    TrackerCh = -1;

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Projection screen configuration (used for asymmetric frustum calculation)
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigScreen : public SUvrConfigSceneNode
{
	FVector2D Size = FVector2D::ZeroVector;

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Camera configuration (UVR camera)
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigCamera : public SUvrConfigSceneNode
{

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Input device configuration (VRPN and other possible devices)
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigInput : public SUvrConfigBase
{
	FString Id;
	FString Type;
	FString Params;

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// General UVR configuration
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigGeneral : public SUvrConfigBase
{
	int32 SwapSyncPolicy = 0;

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Render configuration
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigRender : public SUvrConfigBase
{

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Stereo configuration
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigStereo : public SUvrConfigBase
{
	bool  EyeSwap = false;
	float EyeDist = 0.064f;

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Debug settings
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigDebug : public SUvrConfigBase
{
	bool  DrawStats = false;
	bool  LagSimulateEnabled = false;
	float LagMaxTime = 0.5f; // seconds

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Custom development settings
//////////////////////////////////////////////////////////////////////////////////////////////
struct SUvrConfigCustom : public SUvrConfigBase
{
	TMap<FString, FString> Args;

	virtual FString ToString() const override;
	virtual bool    DeserializeFromString(const FString& line) override;
};
