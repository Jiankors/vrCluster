// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrConfigParser.h"

class UvrConfigParserText : public UvrConfigParser
{
public:
	UvrConfigParserText(IUvrConfigParserListener* const pListener, const FString& cfgPath);

protected:
	// Entry point for file parsing
	virtual bool ParseFile(const FString& path) override;

	// Entry point for line parsing
	void ParseLine(const FString& line);

	// Data type parsing
	template <typename T>
	inline T impl_parse(const FString& line)
	{
		static_assert(std::is_base_of<SUvrConfigBase, T>::value, "Only UVR config types allowed");
		T tmp; bool result = static_cast<SUvrConfigBase&>(tmp).DeserializeFromString(line);
		UE_LOG(LogUvrConfig, Log, TEXT("Deserialization: %s"), result ? TEXT("ok") : TEXT("failed"));
		return tmp;
	}
};

