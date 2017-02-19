// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Misc/UvrBarrier.h"
#include "Network/Service/UvrService.h"
#include "Network/Protocol/IPUvrSwapSyncProtocol.h"


class UvrSwapSyncService :
	public  UvrService,
	private IPUvrSwapSyncProtocol
{
public:
	UvrSwapSyncService(const FString& addr, const int32 port);
	virtual ~UvrSwapSyncService();

public:
	virtual bool Start() override;
	virtual void Shutdown() override;

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrSessionListener
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void NotifySessionOpen(UvrSession* pSession) override;
	virtual void NotifySessionClose(UvrSession* pSession) override;
	virtual UvrMessage::Ptr ProcessMessage(UvrMessage::Ptr msg) override;

private:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrSwapSyncProtocol
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void WaitForSwapSync(double* pThreadWaitTime, double* pBarrierWaitTime) override;


private:
	// Swap sync barrier
	UvrBarrier m_barrierSwap;
};

