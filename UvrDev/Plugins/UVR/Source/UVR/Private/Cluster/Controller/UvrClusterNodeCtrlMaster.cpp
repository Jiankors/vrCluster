
// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrClusterNodeCtrlMaster.h"

#include "UvrPlugin.h"



UvrClusterNodeCtrlMaster::UvrClusterNodeCtrlMaster(const FString& ctrlName, const FString& nodeName) :
	UvrClusterNodeCtrlSlave(ctrlName, nodeName)
{
}

UvrClusterNodeCtrlMaster::~UvrClusterNodeCtrlMaster()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrNodeController
//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrNodeController
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrClusterNodeCtrlMaster::GetSyncData(UvrMessage::DataType& data)
{
	// Override slave implementation with empty one.
	// There is no need to sync on master side since it have source data being synced.
}

void UvrClusterNodeCtrlMaster::GetInputData(UvrMessage::DataType& data)
{
	// Override slave implementation with empty one.
	// There is no need to sync on master side since it have source data being synced.
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrNodeCtrlBase
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrClusterNodeCtrlMaster::InitializeServers()
{
	if (!UvrClusterNodeCtrlSlave::InitializeServers())
		return false;

	UE_LOG(LogUvrCluster, Log, TEXT("%s - initializing master servers..."), *GetControllerName());

	// Get config data
	SUvrConfigClusterNode masterCfg;
	if (UvrPlugin::get().ConfigMgr->GetMasterClusterNode(masterCfg) == false)
	{
		UE_LOG(LogUvrCluster, Error, TEXT("No master node configuration data found"));
		return false;
	}

	// Instantiate node servers
	UE_LOG(LogUvrCluster, Log, TEXT("Servers: addr %s, port_cs %d, port_ss %d"), *masterCfg.Addr, masterCfg.Port_CS, masterCfg.Port_SS);
	m_srvCS.Reset(new UvrClusterSyncService(masterCfg.Addr, masterCfg.Port_CS));
	m_srvSS.Reset(new UvrSwapSyncService(masterCfg.Addr, masterCfg.Port_SS));

	return m_srvCS.IsValid() && m_srvSS.IsValid();
}

bool UvrClusterNodeCtrlMaster::StartServers()
{
	if (!UvrClusterNodeCtrlSlave::StartServers())
		return false;

	UE_LOG(LogUvrCluster, Log, TEXT("%s - starting master servers..."), *GetControllerName());

	// CS server start
	if (m_srvCS->Start())
	{
		UE_LOG(LogUvrCluster, Log, TEXT("%s started"), *m_srvCS->GetName());
	}
	else
	{
		UE_LOG(LogUvrCluster, Error, TEXT("%s failed to start"), *m_srvCS->GetName());
	}

	// SS server start
	if (m_srvSS->Start())
	{
		UE_LOG(LogUvrCluster, Log, TEXT("%s started"), *m_srvSS->GetName());
	}
	else
	{
		UE_LOG(LogUvrCluster, Error, TEXT("%s failed to start"), *m_srvSS->GetName());
	}

	// Start the servers
	return m_srvCS->IsRunning() && m_srvSS->IsRunning();
}

void UvrClusterNodeCtrlMaster::StopServers()
{
	UvrClusterNodeCtrlSlave::StopServers();

	m_srvCS->Shutdown();
	m_srvSS->Shutdown();
}

bool UvrClusterNodeCtrlMaster::InitializeClients()
{
	if (!UvrClusterNodeCtrlSlave::InitializeClients())
		return false;

	// Master clients initialization
	// ...

	return true;
}

bool UvrClusterNodeCtrlMaster::StartClients()
{
	if (!UvrClusterNodeCtrlSlave::StartClients())
		return false;

	// Master clients start
	// ...

	return true;
}

void UvrClusterNodeCtrlMaster::StopClients()
{
	UvrClusterNodeCtrlSlave::StopClients();

	// Master clients stop
	// ...
}

