// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrConfigManager.h"
#include "IPUvrManager.h"


struct IPUvrConfigManager :
	public IUvrConfigManager,
	public IPUvrManager
{
	virtual ~IPUvrConfigManager()
	{ }

};
