// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrVrpnButtonInputDataHolder.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#include "vrpn/vrpn_Button.h"
#include "HideWindowsPlatformTypes.h"
#endif


class UvrVrpnButtonInputDevice :
	public UvrVrpnButtonInputDataHolder
{
public:
	UvrVrpnButtonInputDevice(const SUvrConfigInput& config);
	virtual ~UvrVrpnButtonInputDevice();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrInputDevice
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual bool Initialize() override;

private:
	// Data update handler
	static void VRPN_CALLBACK HandleButtonDevice(void *userData, vrpn_BUTTONCB const b);

private:
	// The device (PIMPL)
	TUniquePtr<vrpn_Button_Remote> m_pDevImpl;
};
