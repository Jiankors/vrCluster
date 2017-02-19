// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrClusterNodeCtrlSlave.h"

#include "Network/Service/ClusterSync/UvrClusterSyncService.h"
#include "Network/Service/SwapSync/UvrSwapSyncService.h"


class UvrClusterNodeCtrlMaster : public UvrClusterNodeCtrlSlave
{
public:
	UvrClusterNodeCtrlMaster(const FString& ctrlName, const FString& nodeName);
	virtual ~UvrClusterNodeCtrlMaster();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrNodeController
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool IsSlave() const override final
	{ return false; }

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrNodeController
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void GetSyncData(UvrMessage::DataType& data)  override;
	virtual void GetInputData(UvrMessage::DataType& data) override;

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// UvrNodeCtrlBase
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool InitializeServers() override;
	virtual bool StartServers()      override;
	virtual void StopServers()       override;

	virtual bool InitializeClients() override;
	virtual bool StartClients()      override;
	virtual void StopClients()       override;

private:
	// Node servers
	TUniquePtr<UvrClusterSyncService> m_srvCS;
	TUniquePtr<UvrSwapSyncService>    m_srvSS;
};

