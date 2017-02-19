// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrInputDataTypes.h"


namespace EUvrInputDevice
{
	enum Type
	{
		VrpnAnalog = 0,
		VrpnButton,
		VrpnTracker
	};
}


template<int DevTypeID>
struct uvr_input_device_traits { };


template <>
struct uvr_input_device_traits<EUvrInputDevice::VrpnAnalog>
{
	typedef SUvrVrpnAnalogChannelData           dev_channel_data_type;
};


template <>
struct uvr_input_device_traits<EUvrInputDevice::VrpnButton>
{
	typedef SUvrVrpnButtonChannelData           dev_channel_data_type;
};


template <>
struct uvr_input_device_traits<EUvrInputDevice::VrpnTracker>
{
	typedef SUvrVrpnTrackerChannelData          dev_channel_data_type;
};
