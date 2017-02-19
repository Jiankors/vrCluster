// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrStringSerializable.h"


struct IUvrClusterSyncObject : public IUvrStringSerializable
{
	virtual ~IUvrClusterSyncObject()
	{ }

	// Unique ID of synced object
	virtual FString GetSyncId() const = 0;
};
