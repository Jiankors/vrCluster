// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Parser/IUvrConfigParserListener.h"
#include "UvrPlugin.h"


class UvrConfigParser;

class UvrConfigManager :
	public    IPUvrConfigManager,
	protected IUvrConfigParserListener,
	private   UvrNoncopyable,
	private   UvrNonmoveable
{
public:
	UvrConfigManager();
	virtual ~UvrConfigManager();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool Init() override;
	virtual void Release() override;
	virtual bool StartSession(const FString& configPath) override;
	virtual void EndSession() override;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrConfigManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual int32 GetClusterNodesAmount() const override;
	virtual TArray<SUvrConfigClusterNode> GetClusterNodes() const override;
	virtual bool GetClusterNode(int32 idx, SUvrConfigClusterNode& node) const override;
	virtual bool GetClusterNode(const FString& id, SUvrConfigClusterNode& node) const override;
	virtual bool GetMasterClusterNode(SUvrConfigClusterNode& node) const override;
	virtual bool GetLocalClusterNode(SUvrConfigClusterNode& node) const override;

	virtual int32 GetScreensAmount() const override;
	virtual TArray<SUvrConfigScreen> GetScreens() const override;
	virtual bool GetScreen(int32 idx, SUvrConfigScreen& screen) const override;
	virtual bool GetScreen(const FString& id, SUvrConfigScreen& screen) const override;
	virtual bool GetLocalScreen(SUvrConfigScreen& screen) const override;

	virtual int32 GetCamerasAmount() const override;
	virtual TArray<SUvrConfigCamera> GetCameras() const override;
	virtual bool GetCamera(int32 idx, SUvrConfigCamera& camera) const override;
	virtual bool GetCamera(const FString& id, SUvrConfigCamera& camera) const override;

	virtual int32 GetViewportsAmount() const override;
	virtual TArray<SUvrConfigViewport> GetViewports() const override;
	virtual bool GetViewport(int32 idx, SUvrConfigViewport& viewport) const override;
	virtual bool GetViewport(const FString& id, SUvrConfigViewport& viewport) const override;
	virtual bool GetLocalViewport(SUvrConfigViewport& screen) const override;

	virtual int32 GetSceneNodesAmount() const override;
	virtual TArray<SUvrConfigSceneNode> GetSceneNodes() const override;
	virtual bool GetSceneNode(int32 idx, SUvrConfigSceneNode& actor) const override;
	virtual bool GetSceneNode(const FString& id, SUvrConfigSceneNode& actor) const override;

	virtual int32 GetInputDevicesAmount() const override;
	virtual TArray<SUvrConfigInput> GetInputDevices() const override;
	virtual bool GetInputDevice(int32 idx, SUvrConfigInput& input) const override;
	virtual bool GetInputDevice(const FString& id, SUvrConfigInput& input) const override;

	virtual SUvrConfigGeneral GetConfigGeneral() const override
	{ return m_CfgGeneral; }

	virtual SUvrConfigStereo  GetConfigStereo() const override
	{ return m_CfgStereo; }

	virtual SUvrConfigRender  GetConfigRender() const override
	{ return m_CfgRender; }

	virtual SUvrConfigDebug   GetConfigDebug() const override
	{ return m_CfgDebug; }

	virtual SUvrConfigCustom  GetConfigCustom() const override
	{ return m_CfgCustom; }

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrConfigManager
	//////////////////////////////////////////////////////////////////////////////////////////////

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrConfigParserListener
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void AddClusterNode(const SUvrConfigClusterNode& cfgCNode) override;
	virtual void AddScreen(const SUvrConfigScreen& cfgScreen) override;
	virtual void AddViewport(const SUvrConfigViewport& cfgViewport) override;
	virtual void AddCamera(const SUvrConfigCamera& cfgCamera) override;
	virtual void AddSceneNode(const SUvrConfigSceneNode& cfgSNode)  override;
	virtual void AddGeneral(const SUvrConfigGeneral& cfgGeneral)  override;
	virtual void AddRender(const SUvrConfigRender& cfgRender)  override;
	virtual void AddStereo(const SUvrConfigStereo& cfgStereo)  override;
	virtual void AddDebug(const SUvrConfigDebug& cfgDebug)  override;
	virtual void AddInput(const SUvrConfigInput& cfgInput)  override;
	virtual void AddCustom(const SUvrConfigCustom& cfgCustom) override;

private:
	enum class EConfigFileType
	{
		Unknown,
		Text,
		Xml
	};

	template <typename DataType>
	bool GetItem(const TArray<DataType>& container, uint32 idx, DataType& item, const FString& logHeader) const
	{
		if (idx >= static_cast<uint32>(container.Num()))
		{
			UE_LOG(LogUvrConfig, Error, TEXT("%s: index is out of bound <%d>"), *logHeader, idx);
			return false;
		}

		item = container[static_cast<int32>(idx)];
		return true;
	}

	template <typename DataType>
	bool GetItem(const TArray<DataType>& container, const FString& id, DataType& item, const FString& logHeader) const
	{
		auto pFound = container.FindByPredicate([id](const DataType& _item)
		{
			return _item.Id == id;
		});

		if (!pFound)
		{
			UE_LOG(LogUvrConfig, Warning, TEXT("%s: ID not found <%s>"), *logHeader, *id);
			return false;
		}

		item = *pFound;
		return true;
	}

	EConfigFileType GetConfigFileType(const FString& cfgPath) const;
	bool ParseConfig(const FString& cfgPath);
	void ResetConfigData();

private:
	FString m_configPath;

	TArray<SUvrConfigClusterNode> m_CNodes;
	TArray<SUvrConfigScreen>      m_Screens;
	TArray<SUvrConfigViewport>    m_Viewports;
	TArray<SUvrConfigCamera>      m_Cameras;
	TArray<SUvrConfigSceneNode>   m_SNodes;
	TArray<SUvrConfigInput>       m_InputDevs;

	SUvrConfigGeneral m_CfgGeneral;
	SUvrConfigStereo  m_CfgStereo;
	SUvrConfigRender  m_CfgRender;
	SUvrConfigDebug   m_CfgDebug;
	SUvrConfigCustom  m_CfgCustom;
};
