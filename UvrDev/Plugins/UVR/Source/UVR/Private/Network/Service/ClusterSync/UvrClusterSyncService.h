// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Misc/UvrBarrier.h"
#include "Network/Service/UvrService.h"
#include "Network/Protocol/IPUvrClusterSyncProtocol.h"



class UvrClusterSyncService :
	public  UvrService,
	private IPUvrClusterSyncProtocol
{
public:
	UvrClusterSyncService(const FString& addr, const int32 port);
	virtual ~UvrClusterSyncService();

public:
	virtual bool Start() override;
	void Shutdown() override;

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrSessionListener
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void NotifySessionOpen(UvrSession* pSession) override;
	virtual void NotifySessionClose(UvrSession* pSession) override;
	virtual UvrMessage::Ptr ProcessMessage(UvrMessage::Ptr msg) override;

private:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrClusterSyncProtocol
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void WaitForGameStart() override;
	virtual void WaitForFrameStart() override;
	virtual void WaitForFrameEnd() override;
	virtual void WaitForTickEnd() override;
	virtual void GetDeltaTime(float& deltaTime) override;
	virtual void GetSyncData(UvrMessage::DataType& data)  override;
	virtual void GetInputData(UvrMessage::DataType& data) override;

private:
	// Game start sync barrier
	UvrBarrier m_barrierGameStart;
	// Frame start barrier
	UvrBarrier m_barrierFrameStart;
	// Frame end barrier
	UvrBarrier m_barrierFrameEnd;
	// Tick end barrier
	UvrBarrier m_barrierTickEnd;
};

