// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Network/UvrMessage.h"


class IPUvrClusterSyncProtocol
{
public:
	// Game start barrier
	virtual void WaitForGameStart() = 0;

	// Frame start barrier
	virtual void WaitForFrameStart() = 0;

	// Frame end barrier
	virtual void WaitForFrameEnd() = 0;

	// Tick end barrier
	virtual void WaitForTickEnd() = 0;

	// Provides with time delta for current frame
	virtual void GetDeltaTime(float& deltaTime) = 0;

	// Sync objects
	virtual void GetSyncData(UvrMessage::DataType& data) = 0;

	// Sync input
	virtual void GetInputData(UvrMessage::DataType& data) = 0;
};

