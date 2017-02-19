// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrConfigParser.h"

class UvrConfigParserXml : public UvrConfigParser
{
public:
	UvrConfigParserXml(IUvrConfigParserListener* const pListener, const FString& cfgPath);

public:
	// Entry point for file parsing
	virtual bool ParseFile(const FString& path) override
	{
		// Not implemented yet
		return false;
	}

protected:
	//virtual bool ReadConfigFile(const FString& path);
};

