// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "IUvrInputManager.h"
#include "IPUvrManager.h"


struct IPUvrInputManager :
	public IUvrInputManager,
	public IPUvrManager
{
	virtual ~IPUvrInputManager()
	{ }

	virtual void Update() = 0;

	virtual void ExportInputData(UvrMessage::DataType& data) const = 0;
	virtual void ImportInputData(const UvrMessage::DataType& data) = 0;
};
