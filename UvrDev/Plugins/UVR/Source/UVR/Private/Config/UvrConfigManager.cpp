// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrConfigManager.h"

#include "Config/Parser/UvrConfigParserText.h"
#include "Config/Parser/UvrConfigParserXml.h"
#include "UVR.h"


UvrConfigManager::UvrConfigManager()
{
	UE_LOG(LogUvrConfig, Verbose, TEXT("UvrConfigManager .ctor"));
}

UvrConfigManager::~UvrConfigManager()
{
	UE_LOG(LogUvrConfig, Verbose, TEXT("UvrConfigManager .dtor"));
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrManager
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrConfigManager::Init()
{
	return true;
}

void UvrConfigManager::Release()
{
}

bool UvrConfigManager::StartSession(const FString& configPath)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Starting session with config: %s"), *configPath);

	m_configPath = configPath;

	// Prepare the string
	UvrHelpers::str::DustCommandLineValue(m_configPath);

	// Parse the source
	return ParseConfig(m_configPath);
}

void UvrConfigManager::EndSession()
{
	ResetConfigData();
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrConfigManager
//////////////////////////////////////////////////////////////////////////////////////////////
// Cluster nodes
int32 UvrConfigManager::GetClusterNodesAmount() const
{
	return m_CNodes.Num();
}

TArray<SUvrConfigClusterNode> UvrConfigManager::GetClusterNodes() const
{
	return m_CNodes;
}

bool UvrConfigManager::GetClusterNode(int32 idx, SUvrConfigClusterNode& node) const
{
	return GetItem(m_CNodes, idx, node, FString("GetNode"));
}

bool UvrConfigManager::GetClusterNode(const FString& id, SUvrConfigClusterNode& node) const
{
	return GetItem(m_CNodes, id, node, FString("GetNode"));
}

bool UvrConfigManager::GetMasterClusterNode(SUvrConfigClusterNode& node) const
{
	auto pFound = m_CNodes.FindByPredicate([](const SUvrConfigClusterNode& item)
	{
		return item.IsMaster == true;
	});

	if (!pFound)
	{
		UE_LOG(LogUvrConfig, Error, TEXT("Master node configuration not found"));
		return false;
	}

	node = *pFound;
	return true;
}

bool UvrConfigManager::GetLocalClusterNode(SUvrConfigClusterNode& node) const
{
	const FString nodeId = UvrPlugin::get().ClusterMgr->GetNodeId();
	return GetItem(m_CNodes, nodeId, node, FString("GetLocalNode"));
}


// Screens
int32 UvrConfigManager::GetScreensAmount() const
{
	return m_Screens.Num();
}

TArray<SUvrConfigScreen> UvrConfigManager::GetScreens() const
{
	return m_Screens;
}

bool UvrConfigManager::GetScreen(int32 idx, SUvrConfigScreen& screen) const
{
	return GetItem(m_Screens, idx, screen, FString("GetScreen"));
}

bool UvrConfigManager::GetScreen(const FString& id, SUvrConfigScreen& screen) const
{
	return GetItem(m_Screens, id, screen, FString("GetScreen"));
}

bool UvrConfigManager::GetLocalScreen(SUvrConfigScreen& screen) const
{
	SUvrConfigClusterNode localNode;
	if (GetLocalClusterNode(localNode))
		return GetItem(m_Screens, localNode.ScreenId, screen, FString("GetLocalScreen"));

	return false;
}

// Cameras
int32 UvrConfigManager::GetCamerasAmount() const
{
	return m_Cameras.Num();
}

TArray<SUvrConfigCamera> UvrConfigManager::GetCameras() const
{
	return m_Cameras;
}

bool UvrConfigManager::GetCamera(int32 idx, SUvrConfigCamera& camera) const
{
	return GetItem(m_Cameras, idx, camera, FString("GetCamera"));
}

bool UvrConfigManager::GetCamera(const FString& id, SUvrConfigCamera& camera) const
{
	return GetItem(m_Cameras, id, camera, FString("GetCamera"));
}



// Viewports
int32 UvrConfigManager::GetViewportsAmount() const
{
	return static_cast<uint32>(m_Viewports.Num());
}

TArray<SUvrConfigViewport> UvrConfigManager::GetViewports() const
{
	return m_Viewports;
}

bool UvrConfigManager::GetViewport(int32 idx, SUvrConfigViewport& viewport) const
{
	return GetItem(m_Viewports, idx, viewport, FString("GetViewport"));
}

bool UvrConfigManager::GetViewport(const FString& id, SUvrConfigViewport& viewport) const
{
	return GetItem(m_Viewports, id, viewport, FString("GetViewport"));
}

bool UvrConfigManager::GetLocalViewport(SUvrConfigViewport& viewport) const
{
	SUvrConfigClusterNode localNode;
	if (GetLocalClusterNode(localNode))
		return GetItem(m_Viewports, localNode.ViewportId, viewport, FString("GetLocalViewport"));

	return false;
}


// Scene nodes
int32 UvrConfigManager::GetSceneNodesAmount() const
{
	return static_cast<uint32>(m_SNodes.Num());
}

TArray<SUvrConfigSceneNode> UvrConfigManager::GetSceneNodes() const
{
	return m_SNodes;
}

bool UvrConfigManager::GetSceneNode(int32 idx, SUvrConfigSceneNode& actor) const
{
	return GetItem(m_SNodes, idx, actor, FString("GetActor"));
}

bool UvrConfigManager::GetSceneNode(const FString& id, SUvrConfigSceneNode& actor) const
{
	return GetItem(m_SNodes, id, actor, FString("GetActor"));
}


// Input devices
int32 UvrConfigManager::GetInputDevicesAmount() const
{
	return m_InputDevs.Num();
}

TArray<SUvrConfigInput> UvrConfigManager::GetInputDevices() const
{
	return m_InputDevs;
}

bool UvrConfigManager::GetInputDevice(int32 idx, SUvrConfigInput& input) const
{
	return GetItem(m_InputDevs, idx, input, FString("GetInputDevice"));
}

bool UvrConfigManager::GetInputDevice(const FString& id, SUvrConfigInput& input) const
{
	return GetItem(m_InputDevs, id, input, FString("GetInputDevice"));
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrConfigParserListener
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrConfigManager::AddClusterNode(const SUvrConfigClusterNode& cfgCNode)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found cluster node: %s"), *cfgCNode.ToString());
	m_CNodes.Add(cfgCNode);
}

void UvrConfigManager::AddScreen(const SUvrConfigScreen& cfgScreen)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found screen: %s"), *cfgScreen.ToString());
	m_Screens.Add(cfgScreen);
}

void UvrConfigManager::AddViewport(const SUvrConfigViewport& cfgViewport)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found viewport: %s"), *cfgViewport.ToString());
	m_Viewports.Add(cfgViewport);
}

void UvrConfigManager::AddCamera(const SUvrConfigCamera& cfgCamera)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found camera: %s"), *cfgCamera.ToString());
	m_Cameras.Add(cfgCamera);
}

void UvrConfigManager::AddSceneNode(const SUvrConfigSceneNode& cfgSNode)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found scene node: %s"), *cfgSNode.ToString());
	m_SNodes.Add(cfgSNode);
}

void UvrConfigManager::AddInput(const SUvrConfigInput& cfgInput)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found input device: %s"), *cfgInput.ToString());
	m_InputDevs.Add(cfgInput);
}

void UvrConfigManager::AddGeneral(const SUvrConfigGeneral& cfgGeneral)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found general: %s"), *cfgGeneral.ToString());
	m_CfgGeneral = cfgGeneral;
}

void UvrConfigManager::AddRender(const SUvrConfigRender& cfgRender)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found render: %s"), *cfgRender.ToString());
	m_CfgRender = cfgRender;
}

void UvrConfigManager::AddStereo(const SUvrConfigStereo& cfgStereo)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found stereo: %s"), *cfgStereo.ToString());
	m_CfgStereo = cfgStereo;
}

void UvrConfigManager::AddDebug(const SUvrConfigDebug& cfgDebug)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found debug: %s"), *cfgDebug.ToString());
	m_CfgDebug = cfgDebug;
}

void UvrConfigManager::AddCustom(const SUvrConfigCustom& cfgCustom)
{
	UE_LOG(LogUvrConfig, Log, TEXT("Found custom: %s"), *cfgCustom.ToString());
	m_CfgCustom = cfgCustom;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrConfigManager
//////////////////////////////////////////////////////////////////////////////////////////////
UvrConfigManager::EConfigFileType UvrConfigManager::GetConfigFileType(const FString& cfgPath) const
{
	if (FPaths::FileExists(cfgPath) == false)
	{
		UE_LOG(LogUvrConfig, Warning, TEXT("File not found: %s"), *cfgPath);
		return EConfigFileType::Unknown;
	}

	auto ext = FPaths::GetExtension(cfgPath).ToLower();
	if (ext == FString(UvrStrings::cfg::file::FileExtXml).ToLower())
	{
		UE_LOG(LogUvrConfig, Log, TEXT("XML config: %s"), *cfgPath);
		return EConfigFileType::Xml;
	}
	else if (
		ext == FString(UvrStrings::cfg::file::FileExtCfg1).ToLower() ||
		ext == FString(UvrStrings::cfg::file::FileExtCfg2).ToLower() ||
		ext == FString(UvrStrings::cfg::file::FileExtCfg3).ToLower() ||
		ext == FString(UvrStrings::cfg::file::FileExtTxt).ToLower())
	{
		UE_LOG(LogUvrConfig, Log, TEXT("TXT config: %s"), *cfgPath);
		return EConfigFileType::Text;
	}

	UE_LOG(LogUvrConfig, Warning, TEXT("Unknown config: %s"), *cfgPath);
	return EConfigFileType::Unknown;
}

bool UvrConfigManager::ParseConfig(const FString& cfgPath)
{
	TScopedPointer<UvrConfigParser> parser;

	switch (GetConfigFileType(cfgPath))
	{
	case EConfigFileType::Text:
		parser.Reset(new UvrConfigParserText(this, cfgPath));
		break;

	case EConfigFileType::Xml:
		parser.Reset(new UvrConfigParserXml(this, cfgPath));
		break;

	default:
		UE_LOG(LogUvrConfig, Error, TEXT("Unknown config type"));
		return false;
	}

	return true;
}

void UvrConfigManager::ResetConfigData()
{
	m_configPath.Reset();

	m_CNodes.Reset();
	m_Screens.Reset();
	m_Viewports.Reset();
	m_Cameras.Reset();
	m_SNodes.Reset();
	m_InputDevs.Reset();

	m_CfgGeneral = SUvrConfigGeneral();
	m_CfgStereo  = SUvrConfigStereo();
	m_CfgRender  = SUvrConfigRender();
	m_CfgDebug   = SUvrConfigDebug();
	m_CfgCustom  = SUvrConfigCustom();
}
