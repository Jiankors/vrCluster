// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Network/UvrClient.h"
#include "Network/Protocol/IPUvrSwapSyncProtocol.h"


class UvrSwapSyncClient :
	public UvrClient,
	public IPUvrSwapSyncProtocol
{
public:
	UvrSwapSyncClient();
	UvrSwapSyncClient(const FString& name);

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrSwapSyncProtocol
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void WaitForSwapSync(double* pThreadWaitTime, double* pBarrierWaitTime) override;
};

