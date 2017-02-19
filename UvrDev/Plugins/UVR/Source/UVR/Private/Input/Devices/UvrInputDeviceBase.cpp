// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrInputDeviceBase.h"



template <int DevTypeID>
UvrInputDeviceBase<DevTypeID>::UvrInputDeviceBase(const SUvrConfigInput& config) :
	m_ConfigData(config)
{
}

template <int DevTypeID>
UvrInputDeviceBase<DevTypeID>::~UvrInputDeviceBase()
{
}


template <int DevTypeID>
bool UvrInputDeviceBase<DevTypeID>::GetChannelData(const uint8 channel, TChannelData& data) const
{
	if (!m_data.Contains(static_cast<int32>(channel)))
	{
		UE_LOG(LogUvrInput, Log, TEXT("%s - channel %d data is not available yet"), *GetId(), channel);
		return false;
	}

	data = m_data[static_cast<int32>(channel)];

	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrInputDeviceBase
//////////////////////////////////////////////////////////////////////////////////////////////
//@todo: move to string helpers
template <int DevTypeID>
bool UvrInputDeviceBase<DevTypeID>::ExtractParam(const FString& param, FString& value, bool bTrimQuotes) const
{
	// Extract device address
	if (!FParse::Value(*m_ConfigData.Params, *param, value, false))
	{
		UE_LOG(LogUvrInput, Error, TEXT("Parameter %s not found for device %s"), *param, *m_ConfigData.Id);
		return false;
	}

	UvrHelpers::str::DustCommandLineValue(value, bTrimQuotes);

	return true;
}
