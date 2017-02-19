// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrVrpnTrackerInputDataHolder.h"

#include "UvrPlugin.h"



UvrVrpnTrackerInputDataHolder::UvrVrpnTrackerInputDataHolder(const SUvrConfigInput& config) :
	UvrInputDeviceBase(config)
{
}

UvrVrpnTrackerInputDataHolder::~UvrVrpnTrackerInputDataHolder()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrVrpnTrackerInputDataHolder::Initialize()
{
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrStringSerializable
//////////////////////////////////////////////////////////////////////////////////////////////
FString UvrVrpnTrackerInputDataHolder::SerializeToString() const
{
	FString result;
	result.Reserve(256);

	for (auto it = m_data.CreateConstIterator(); it; ++it)
		result += FString::Printf(TEXT("%d%s%s%s%s%s"),
			it->Key, SerializationDelimiter, *it->Value.trLoc.ToString(), SerializationDelimiter, *it->Value.trRot.ToString(), SerializationDelimiter);

	return result;
}

bool UvrVrpnTrackerInputDataHolder::DeserializeFromString(const FString& data)
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
		FVector  loc;
		FRotator rot;
		loc.InitFromString(parsed[i + 1]);
		rot.InitFromString(parsed[i + 2]);

		m_data.Add(ch, SUvrVrpnTrackerChannelData{ loc, rot });
	}

	return true;
}

