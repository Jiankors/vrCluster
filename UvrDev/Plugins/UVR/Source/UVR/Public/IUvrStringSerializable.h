// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Engine.h"


struct IUvrStringSerializable
{
	virtual ~IUvrStringSerializable()
	{ }

	virtual FString SerializeToString() const = 0;
	virtual bool    DeserializeFromString(const FString& ar) = 0;
};
