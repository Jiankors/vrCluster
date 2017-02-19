// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once


struct IUvrClusterManager
{
	virtual ~IUvrClusterManager()
	{ }

	virtual bool IsMaster()         const = 0;
	virtual bool IsSlave()          const = 0;
	virtual bool IsStandalone()     const = 0;
	virtual bool IsCluster()        const = 0;
	virtual FString GetNodeId()     const = 0;
	virtual uint32 GetNodesAmount() const = 0;
};
