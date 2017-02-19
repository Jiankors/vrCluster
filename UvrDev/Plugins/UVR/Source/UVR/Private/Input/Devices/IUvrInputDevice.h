// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrInputDeviceTraits.h"
#include "IUvrStringSerializable.h"


struct IUvrInputDevice : public IUvrStringSerializable
{
	virtual ~IUvrInputDevice() = 0
	{ }

	virtual FString GetId() const = 0;
	virtual FString GetType() const = 0;
	virtual EUvrInputDevice::Type GetTypeId() const = 0;
	virtual SUvrConfigInput GetConfig() const = 0;

	virtual bool Initialize() = 0;
	virtual void PreUpdate() = 0;
	virtual void Update() = 0;
	virtual void PostUpdate() = 0;

	virtual FString ToString() const = 0;
};

