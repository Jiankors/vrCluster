// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

struct IUvrSerializable
{
	virtual ~IUvrSerializable()
	{ }

	virtual bool Serialize  (FMemoryWriter& ar) = 0;
	virtual bool Deserialize(FMemoryReader& ar) = 0;
};
