// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrRenderManager.h"
#include "IPUvrManager.h"


struct IPUvrRenderManager :
	public IUvrRenderManager,
	public IPUvrManager
{
	virtual ~IPUvrRenderManager()
	{ }

};
