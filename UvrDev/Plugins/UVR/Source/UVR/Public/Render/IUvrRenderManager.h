// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrStereoDevice.h"


struct IUvrRenderManager
{
	virtual ~IUvrRenderManager()
	{ }

	virtual IUvrStereoDevice* GetStereoDevice() = 0;
};
