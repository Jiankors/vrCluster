// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrVrpnAnalogInputDataHolder.h"


UvrVrpnAnalogInputDataHolder::UvrVrpnAnalogInputDataHolder(const SUvrConfigInput& config) :
	UvrInputDeviceBase(config)
{
}

UvrVrpnAnalogInputDataHolder::~UvrVrpnAnalogInputDataHolder()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrVrpnAnalogInputDataHolder::Initialize()
{
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrStringSerializable
//////////////////////////////////////////////////////////////////////////////////////////////
FString UvrVrpnAnalogInputDataHolder::SerializeToString() const
{
	FString result;
	result.Reserve(128);

	for (auto it = m_data.CreateConstIterator(); it; ++it)
		result += FString::Printf(TEXT("%d%s%f%s"), it->Key, SerializationDelimiter, it->Value.axisValue, SerializationDelimiter);

	return result;
}

bool UvrVrpnAnalogInputDataHolder::DeserializeFromString(const FString& data)
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
		const int   ch = FCString::Atoi(*parsed[i]);
		const float val = FCString::Atof(*parsed[i + 1]);
		m_data.Add(ch, SUvrVrpnAnalogChannelData{ val });
	}

	return true;
}
