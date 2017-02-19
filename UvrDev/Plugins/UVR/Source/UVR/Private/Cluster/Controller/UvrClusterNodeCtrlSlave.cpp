// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrClusterNodeCtrlSlave.h"

#include "UvrPlugin.h"


UvrClusterNodeCtrlSlave::UvrClusterNodeCtrlSlave(const FString& ctrlName, const FString& nodeName) :
	UvrClusterNodeCtrlBase(ctrlName, nodeName)
{
}

UvrClusterNodeCtrlSlave::~UvrClusterNodeCtrlSlave()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrNodeController
//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrClusterSyncProtocol
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrClusterNodeCtrlSlave::WaitForGameStart()
{
	m_clnCS->WaitForGameStart();
}

void UvrClusterNodeCtrlSlave::WaitForFrameStart()
{
	m_clnCS->WaitForFrameStart();
}

void UvrClusterNodeCtrlSlave::WaitForFrameEnd()
{
	m_clnCS->WaitForFrameEnd();
}

void UvrClusterNodeCtrlSlave::WaitForTickEnd()
{
	m_clnCS->WaitForTickEnd();
}

void UvrClusterNodeCtrlSlave::GetDeltaTime(float& deltaTime)
{
	m_clnCS->GetDeltaTime(deltaTime);
}

void UvrClusterNodeCtrlSlave::GetSyncData(UvrMessage::DataType& data)
{
	m_clnCS->GetSyncData(data);
}

void UvrClusterNodeCtrlSlave::GetInputData(UvrMessage::DataType& data)
{
	m_clnCS->GetInputData(data);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrSwapSyncProtocol
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrClusterNodeCtrlSlave::WaitForSwapSync(double* pThreadWaitTime, double* pBarrierWaitTime)
{
	check(m_clnSS.IsValid());
	m_clnSS->WaitForSwapSync(pThreadWaitTime, pBarrierWaitTime);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrNodeCtrlBase
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrClusterNodeCtrlSlave::InitializeServers()
{
	if (!UvrClusterNodeCtrlBase::InitializeServers())
		return false;

	// Slave servers initialization
	// ...

	return true;
}

bool UvrClusterNodeCtrlSlave::StartServers()
{
	if (!UvrClusterNodeCtrlBase::StartServers())
		return false;

	// Slave servers start
	// ...

	return true;
}

void UvrClusterNodeCtrlSlave::StopServers()
{
	UvrClusterNodeCtrlBase::StopServers();

	// Slave servers stop
	// ...
}

bool UvrClusterNodeCtrlSlave::InitializeClients()
{
	if (!UvrClusterNodeCtrlBase::InitializeClients())
		return false;

	UE_LOG(LogUvrCluster, Log, TEXT("%s - initializing slave clients..."), *GetControllerName());

	// Instantiate local clients
	m_clnCS.Reset(new UvrClusterSyncClient());
	m_clnSS.Reset(new UvrSwapSyncClient());

	return m_clnCS.IsValid() && m_clnSS.IsValid();
}

bool UvrClusterNodeCtrlSlave::StartClients()
{
	if (!UvrClusterNodeCtrlBase::StartClients())
		return false;

	UE_LOG(LogUvrCluster, Log, TEXT("%s - initializing slave clients..."), *GetControllerName());

	// Master config
	SUvrConfigClusterNode masterCfg;
	if (UvrPlugin::get().ConfigMgr->GetMasterClusterNode(masterCfg) == false)
	{
		UE_LOG(LogUvrCluster, Error, TEXT("No master node configuration data found"));
		return false;
	}

	// CS client
	if (m_clnCS->Connect(masterCfg.Addr, masterCfg.Port_CS))
	{
		UE_LOG(LogUvrCluster, Log, TEXT("%s connected to the server %s:%d"), *m_clnCS->GetName(), *masterCfg.Addr, masterCfg.Port_CS);
	}
	else
	{
		UE_LOG(LogUvrCluster, Error, TEXT("%s couldn't connect to the server %s:%d"), *m_clnCS->GetName(), *masterCfg.Addr, masterCfg.Port_CS);
		// No need to wait again for next client connection
		return false;
	}

	// SS client
	if (m_clnSS->Connect(masterCfg.Addr, masterCfg.Port_SS))
	{
		UE_LOG(LogUvrCluster, Log, TEXT("%s connected to the server %s:%d"), *m_clnSS->GetName(), *masterCfg.Addr, masterCfg.Port_SS);
	}
	else
	{
		UE_LOG(LogUvrCluster, Error, TEXT("%s couldn't connect to the server %s:%d"), *m_clnSS->GetName(), *masterCfg.Addr, masterCfg.Port_SS);
		return false;
	}

	return m_clnCS->IsConnected() && m_clnSS->IsConnected();
}

void UvrClusterNodeCtrlSlave::StopClients()
{
	UvrClusterNodeCtrlBase::StopClients();

	m_clnCS->Disconnect();
	m_clnSS->Disconnect();
}
