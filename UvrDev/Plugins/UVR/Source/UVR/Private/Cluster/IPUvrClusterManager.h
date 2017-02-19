// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrClusterManager.h"
#include "IPUvrManager.h"
#include "Network/UvrMessage.h"

// Forward declaration
struct IPUvrNodeController;
struct IUvrClusterSyncObject;


struct IPUvrClusterManager :
	public IUvrClusterManager,
	public IPUvrManager
{
	virtual ~IPUvrClusterManager()
	{ }

	virtual IPUvrNodeController* GetController() const = 0;
	
	virtual float GetDeltaTime() const = 0;
	virtual void  SetDeltaTime(float deltaTime) = 0;
	
	virtual void RegisterSyncObject  (IUvrClusterSyncObject* pSyncObj) = 0;
	virtual void UnregisterSyncObject(IUvrClusterSyncObject* pSyncObj) = 0;

	virtual void ExportSyncData(UvrMessage::DataType& data) const = 0;
	virtual void ImportSyncData(const UvrMessage::DataType& data) = 0;

	virtual void SyncObjects() = 0;
	virtual void SyncInput()   = 0;
};
