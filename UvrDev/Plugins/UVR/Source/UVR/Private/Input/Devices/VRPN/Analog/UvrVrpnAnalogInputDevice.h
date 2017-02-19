// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrVrpnAnalogInputDataHolder.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#include "vrpn/vrpn_Analog.h"
#include "HideWindowsPlatformTypes.h"
#endif


class UvrVrpnAnalogInputDevice :
	public UvrVrpnAnalogInputDataHolder
{
public:
	UvrVrpnAnalogInputDevice(const SUvrConfigInput& config);
	virtual ~UvrVrpnAnalogInputDevice();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrInputDevice
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Update() override;
	virtual bool Initialize() override;

private:
	// Data update handler
	static void VRPN_CALLBACK HandleAnalogDevice(void *userData, vrpn_ANALOGCB const tr);

private:
	// The device (PIMPL)
	TUniquePtr<vrpn_Analog_Remote> m_pDevImpl;
};
