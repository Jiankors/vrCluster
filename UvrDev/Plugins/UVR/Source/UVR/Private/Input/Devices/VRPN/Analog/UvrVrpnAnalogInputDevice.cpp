// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrVrpnAnalogInputDevice.h"


UvrVrpnAnalogInputDevice::UvrVrpnAnalogInputDevice(const SUvrConfigInput& config) :
	UvrVrpnAnalogInputDataHolder(config)
{
}

UvrVrpnAnalogInputDevice::~UvrVrpnAnalogInputDevice()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrVrpnAnalogInputDevice::Update()
{
	if (m_pDevImpl)
	{
		UE_LOG(LogUvrInput, Verbose, TEXT("Updating device: %s"), *GetId());
		m_pDevImpl->mainloop();
	}
}

bool UvrVrpnAnalogInputDevice::Initialize()
{
	FString addr;
	if (!ExtractParam(FString(UvrStrings::cfg::data::input::Address), addr))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - device address not found"), *ToString());
		return false;
	}

	// Instantiate device implementation
	m_pDevImpl.Reset(new vrpn_Analog_Remote(TCHAR_TO_UTF8(*addr)));
	
	// Register update handler
	if (m_pDevImpl->register_change_handler(this, &UvrVrpnAnalogInputDevice::HandleAnalogDevice) != 0)
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - couldn't register VRPN change handler"), *ToString());
		return false;
	}

	// Base initialization
	return UvrVrpnAnalogInputDataHolder::Initialize();
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrVrpnAnalogInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
void VRPN_CALLBACK UvrVrpnAnalogInputDevice::HandleAnalogDevice(void * userData, vrpn_ANALOGCB const an)
{
	auto pDev = reinterpret_cast<UvrVrpnAnalogInputDevice*>(userData);

	for (int32 i = 0; i < an.num_channel; ++i)
	{
		auto pItem = pDev->m_data.Find(i);
		if (!pItem)
			pItem = &pDev->m_data.Add(i);

		pItem->axisValue = static_cast<float>(an.channel[i]);
		UE_LOG(LogUvrInput, VeryVerbose, TEXT("Axis %s:%d - %f"), *pDev->GetId(), i, pItem->axisValue);
	}
}
