// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrGameManager.h"
#include "IPUvrManager.h"


struct IPUvrGameManager :
	public IUvrGameManager,
	public IPUvrManager
{
	virtual ~IPUvrGameManager()
	{ }

};
