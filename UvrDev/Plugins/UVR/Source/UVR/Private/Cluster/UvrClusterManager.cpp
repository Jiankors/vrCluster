// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrClusterManager.h"

#include "UvrPlugin.h"
#include "IUvrClusterSyncObject.h"

#include "Cluster/Controller/UvrNodeCtrlStandalone.h"
#include "Cluster/Controller/UvrClusterNodeCtrlMaster.h"
#include "Cluster/Controller/UvrClusterNodeCtrlSlave.h"
#include "UVR.h"


UvrClusterManager::UvrClusterManager()
{
	UE_LOG(LogUvrCluster, Verbose, TEXT("UvrClusterManager .ctor"));

	m_objects.Reserve(64);
}

UvrClusterManager::~UvrClusterManager()
{
	UE_LOG(LogUvrCluster, Verbose, TEXT("UvrClusterManager .dtor"));
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrManager
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrClusterManager::Init()
{
	return true;
}

void UvrClusterManager::Release()
{
}

bool UvrClusterManager::StartSession(const FString& configPath)
{
	// Read node id
	if (GIsEditor == false)
	{
		if (FParse::Value(FCommandLine::Get(), UvrStrings::args::Node, m_nodeId) == false)
		{
			UE_LOG(LogUvrCluster, Warning, TEXT("Node name was not specified. Trying to resolve address from available interfaces..."));

			// Try to find the node ID by address (this won't work if you want to run several cluster nodes on the same address)
			if (!GetResolvedNodeId(m_nodeId))
			{
				UE_LOG(LogUvrCluster, Error, TEXT("Unable to resolve node ID by local addresses"));
				return false;
			}
		}
	}
	else
	{
		// Get in-scene settings
		m_nodeId = AUVR::ms_EditorNodeName;
	}

	// Prepare the string (trim/cleaning)
	UvrHelpers::str::DustCommandLineValue(m_nodeId);

	UE_LOG(LogUvrCluster, Log, TEXT("Node ID: %s"), *m_nodeId);

	// Node name must be specified in cluster mode
	if (m_nodeId.IsEmpty())
	{
		UE_LOG(LogUvrCluster, Error, TEXT("Node name was not specified"));
		return false;
	}

	// Save nodes amount
	m_nodesAmount = UvrPlugin::get().ConfigMgr->GetClusterNodesAmount();

	// Instantiate node controller
	m_controller = CreateController();

	if (!m_controller)
	{
		UE_LOG(LogUvrCluster, Error, TEXT("Couldn't create a controller."));
		return false;
	}

	// Initialize the controller
	UE_LOG(LogUvrCluster, Log, TEXT("Initializing the controller..."));
	if (!m_controller->Initialize())
	{
		UE_LOG(LogUvrCluster, Error, TEXT("Couldn't initialize a controller."));
		m_controller.Reset();
		return false;
	}

	return true;
}

void UvrClusterManager::EndSession()
{
	{
		FScopeLock lock(&m_lock);
		if (m_controller)
		{
			m_controller->Release();
			m_controller.Reset();
		}
	}
}

bool UvrClusterManager::StartGame(UWorld* pWorld)
{
	return true;
}

void UvrClusterManager::EndGame()
{
	{
		FScopeLock lock(&m_cs_objects);
		m_objects.Reset();
	}
}

void UvrClusterManager::PreTick(float DeltaSeconds)
{
	// Clear cached data from previous game frame
	{
		FScopeLock lock(&m_cs_objects);
		m_objectsCache.Empty(m_objectsCache.Num() | 0x07);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrClusterManager
//////////////////////////////////////////////////////////////////////////////////////////////
IPUvrNodeController* UvrClusterManager::GetController() const
{
	FScopeLock lock(&m_lock);
	return m_controller ? m_controller.Get() : nullptr;
}

bool UvrClusterManager::IsMaster() const
{
	return m_controller->IsMaster();
}

bool UvrClusterManager::IsSlave() const
{
	return m_controller->IsSlave();
}

bool UvrClusterManager::IsStandalone() const
{
	return m_controller->IsStandalone();
}

bool UvrClusterManager::IsCluster() const
{
	return m_controller->IsCluster();
}

//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrClusterManager
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrClusterManager::RegisterSyncObject(IUvrClusterSyncObject* pSyncObj)
{
	FScopeLock lock(&m_cs_objects);
	m_objects.Add(pSyncObj);
	UE_LOG(LogUvrCluster, Log, TEXT("Registered sync object: %s"), *pSyncObj->GetSyncId());
}

void UvrClusterManager::UnregisterSyncObject(IUvrClusterSyncObject* pSyncObj)
{
	FScopeLock lock(&m_cs_objects);
	m_objects.Remove(pSyncObj);
	UE_LOG(LogUvrCluster, Log, TEXT("Unregistered sync object: %s"), *pSyncObj->GetSyncId());
}

void UvrClusterManager::ExportSyncData(TMap<FString, FString>& data) const
{
	{
		FScopeLock lock(&m_cs_objects);

		// Cache the data for current frame.
		// There is on check for m_objects emptiness because we always have at least one
		// shared transform which is AUvrRoot.
		if (m_objectsCache.Num() == 0)
		{
			for (auto obj : m_objects)
				m_objectsCache.Add(obj->GetSyncId(), obj->SerializeToString());
		}
	}

	data = m_objectsCache;
}

void UvrClusterManager::ImportSyncData(const TMap<FString, FString>& data)
{
	if (data.Num() > 0)
	{
		for (auto it = data.CreateConstIterator(); it; ++it)
			UE_LOG(LogUvrCluster, Verbose, TEXT("sync-data: %s=%s"), *it->Key, *it->Value);

		for (auto obj : m_objects)
		{
			const FString syncId = obj->GetSyncId();
			if (!data.Contains(syncId))
			{
				UE_LOG(LogUvrCluster, Error, TEXT("%s not found in sync data"), *syncId);
				continue;
			}

			UE_LOG(LogUvrCluster, Verbose, TEXT("Found %s in sync data. Applying..."), *syncId);
			if (!obj->DeserializeFromString(data[syncId]))
				UE_LOG(LogUvrCluster, Error, TEXT("Couldn't apply sync data for sync object %s"), *syncId);
		}
	}
}

void UvrClusterManager::SyncObjects()
{
	//@note:
	// Don't use FScopeLock lock(&m_cs_objects) here because
	// a) There are no race conditions at this point. We're in single-threaded mode right now (see UUvrGameEngine::Tick())
	// b) Performance

	// No need to do the sync for master
	if (IsSlave())
	{
		UE_LOG(LogUvrCluster, Verbose, TEXT("Downloading synchronization data (objects)..."));
		TMap<FString, FString> data;
		m_controller->GetSyncData(data);
		UE_LOG(LogUvrCluster, Verbose, TEXT("Downloading finished. Available %d records (objects)."), data.Num());

		// Perform data load (objects state update)
		ImportSyncData(data);
	}
}

void UvrClusterManager::SyncInput()
{
	// No need to do the sync for master
	if (IsSlave())
	{
		UE_LOG(LogUvrCluster, Verbose, TEXT("Downloading synchronization data (input)..."));
		TMap<FString, FString> data;
		m_controller->GetInputData(data);
		UE_LOG(LogUvrCluster, Verbose, TEXT("Downloading finished. Available %d records (input)."), data.Num());

		// Perform data load (objects state update)
		UvrPlugin::get().InputMgr->ImportInputData(data);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrClusterManager
//////////////////////////////////////////////////////////////////////////////////////////////
UvrClusterManager::TController UvrClusterManager::CreateController() const
{
	const bool bCluster = FParse::Param(FCommandLine::Get(), UvrStrings::args::Cluster);
	UvrNodeCtrlBase* pController = nullptr;

	if (bCluster == true)
	{
		UE_LOG(LogUvrCluster, Log, TEXT("Running in cluster mode"));

		SUvrConfigClusterNode nodeCfg;
		if (UvrPlugin::get().ConfigMgr->GetClusterNode(m_nodeId, nodeCfg) == false)
		{
			UE_LOG(LogUvrCluster, Error, TEXT("Configuration data for node %s not found"), *m_nodeId);
			return nullptr;
		}
		
		if (nodeCfg.IsMaster)
		{
			UE_LOG(LogUvrCluster, Log, TEXT("Instantiating cluster master controller..."));
			pController = new UvrClusterNodeCtrlMaster(FString("[CTRL-M]"), m_nodeId);
		}
		else
		{
			UE_LOG(LogUvrCluster, Log, TEXT("Instantiating cluster slave controller..."));
			pController = new UvrClusterNodeCtrlSlave(FString("[CTRL-S]"), m_nodeId);
		}
	}
	else
	{
		UE_LOG(LogUvrCluster, Log, TEXT("Running in standalone mode. Instantiating standalone controller"));
		pController = new UvrNodeCtrlStandalone(FString("[CTRL-STNDA]"), FString("standalone"));
	}

	// Return the controller
	return TController(pController);
}

bool UvrClusterManager::GetResolvedNodeId(FString& id) const
{
	TArray<TSharedPtr<FInternetAddr>> addrs;
	if (!ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalAdapterAddresses(addrs))
	{
		UE_LOG(LogUvrCluster, Error, TEXT("Couldn't get local addresses list. Cannot find node ID by its address."));
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::KillImmediately, FString("Cluster manager init error"));
		return false;
	}

	if (addrs.Num() <= 0)
	{
		UE_LOG(LogUvrCluster, Error, TEXT("No local addresses found"));
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::KillImmediately, FString("Cluster manager init error"));
		return false;
	}

	auto cnodes = UvrPlugin::get().ConfigMgr->GetClusterNodes();

	// Look for associated node in config
	auto pNode = cnodes.FindByPredicate([addrs](const SUvrConfigClusterNode& node)
	{
		for (auto addr : addrs)
		{
			const FIPv4Endpoint ep(addr);
			const FString epaddr = ep.Address.ToString();
			UE_LOG(LogUvrCluster, Log, TEXT("Comparing addresses: %s - %s"), *epaddr, *node.Addr);

			//@note: don't add "127.0.0.1" or "localhost" here. There will be a bug. It has been proved already.
			if (epaddr == node.Addr)
				return true;
		}
		return false;
	});

	if (!pNode)
	{
		UE_LOG(LogUvrCluster, Error, TEXT("Couldn't find any local address in config file"));
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::KillImmediately, FString("Cluster manager init error"));
		return false;
	}

	// Ok, we found the node ID by address (this won't work if you want to run several cluster nodes on the same address)
	id = pNode->Id;
	return true;
}
