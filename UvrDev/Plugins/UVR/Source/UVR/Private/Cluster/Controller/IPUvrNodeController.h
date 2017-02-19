// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Network/Protocol/IPUvrClusterSyncProtocol.h"
#include "Network/Protocol/IPUvrSwapSyncProtocol.h"


struct IPUvrNodeController :
	public IPUvrClusterSyncProtocol,
	public IPUvrSwapSyncProtocol
{
	virtual ~IPUvrNodeController()
	{ }

	virtual bool Initialize() = 0;
	virtual void Release() = 0;

	virtual bool IsMaster() const = 0;
	virtual bool IsSlave() const = 0;
	virtual bool IsStandalone() const = 0;
	virtual bool IsCluster() const = 0;
	virtual FString GetNodeId() const = 0;
	virtual FString GetControllerName() const = 0;
};

