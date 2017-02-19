// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrClusterNodeCtrlBase.h"
#include "Network/Service/ClusterSync/UvrClusterSyncClient.h"
#include "Network/Service/SwapSync/UvrSwapSyncClient.h"


class UvrClusterNodeCtrlSlave : public UvrClusterNodeCtrlBase
{
public:
	UvrClusterNodeCtrlSlave(const FString& ctrlName, const FString& nodeName);
	virtual ~UvrClusterNodeCtrlSlave();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrNodeController
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool IsSlave() const override
	{ return true; }

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrClusterSyncProtocol
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void WaitForGameStart()  override final;
	virtual void WaitForFrameStart() override final;
	virtual void WaitForFrameEnd()   override final;
	virtual void WaitForTickEnd()    override final;
	virtual void GetDeltaTime(float& deltaTime) override final;
	virtual void GetSyncData(UvrMessage::DataType& data)  override;
	virtual void GetInputData(UvrMessage::DataType& data) override;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrSwapSyncProtocol
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void WaitForSwapSync(double* pThreadWaitTime, double* pBarrierWaitTime) override final;

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
	// Cluster node clients
	TUniquePtr<UvrClusterSyncClient> m_clnCS;
	TUniquePtr<UvrSwapSyncClient>    m_clnSS;
};

