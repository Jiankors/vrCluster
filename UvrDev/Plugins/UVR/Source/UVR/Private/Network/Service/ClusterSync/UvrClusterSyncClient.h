// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Network/UvrClient.h"
#include "Network/Protocol/IPUvrClusterSyncProtocol.h"


class UvrClusterSyncClient :
	public UvrClient,
	public IPUvrClusterSyncProtocol
{
public:
	UvrClusterSyncClient();
	UvrClusterSyncClient(const FString& name);

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrClusterSyncProtocol
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void WaitForGameStart() override;
	virtual void WaitForFrameStart() override;
	virtual void WaitForFrameEnd() override;
	virtual void WaitForTickEnd() override;
	virtual void GetDeltaTime(float& deltaTime) override;
	virtual void GetSyncData(UvrMessage::DataType& data) override;
	virtual void GetInputData(UvrMessage::DataType& data) override;
};

