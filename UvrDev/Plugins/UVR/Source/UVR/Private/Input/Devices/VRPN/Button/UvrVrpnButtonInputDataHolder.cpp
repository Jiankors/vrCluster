// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrVrpnButtonInputDataHolder.h"



UvrVrpnButtonInputDataHolder::UvrVrpnButtonInputDataHolder(const SUvrConfigInput& config) :
	UvrInputDeviceBase(config)
{
}

UvrVrpnButtonInputDataHolder::~UvrVrpnButtonInputDataHolder()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrVrpnButtonInputDataHolder::Initialize()
{
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrStringSerializable
//////////////////////////////////////////////////////////////////////////////////////////////
FString UvrVrpnButtonInputDataHolder::SerializeToString() const
{
	FString result;
	result.Reserve(64);

	for (auto it = m_data.CreateConstIterator(); it; ++it)
		result += FString::Printf(TEXT("%d%s%d%s%d%s"), it->Key, SerializationDelimiter, it->Value.btnStateOld, SerializationDelimiter, it->Value.btnStateNew, SerializationDelimiter);

	return result;
}

bool UvrVrpnButtonInputDataHolder::DeserializeFromString(const FString& data)
{
	TArray<FString> parsed;
	data.ParseIntoArray(parsed, SerializationDelimiter);

	if (parsed.Num() % SerializationItems)
	{
		UE_LOG(LogUvrInput, Error, TEXT("Wrong items amount after deserialization [%s]"), *data);
		return false;
	}

	for (int i = 0; i < parsed.Num(); i += SerializationItems)
	{
		const int  ch = FCString::Atoi(*parsed[i]);
		const bool stateOld = (FCString::Atoi(*parsed[i + 1]) != 0);
		const bool stateNew = (FCString::Atoi(*parsed[i + 2]) != 0);
		m_data.Add(ch, SUvrVrpnButtonChannelData{ stateOld, stateNew });
	}

	return true;
}
