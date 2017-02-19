// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrVrpnButtonInputDevice.h"


UvrVrpnButtonInputDevice::UvrVrpnButtonInputDevice(const SUvrConfigInput& config) :
	UvrVrpnButtonInputDataHolder(config)
{
}

UvrVrpnButtonInputDevice::~UvrVrpnButtonInputDevice()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrVrpnButtonInputDevice::PreUpdate()
{
	// Update 'old' states before calling mainloop
	for (auto it = m_data.CreateIterator(); it; ++it)
		it->Value.btnStateOld = it->Value.btnStateNew;
}

void UvrVrpnButtonInputDevice::Update()
{
	if (m_pDevImpl)
	{
		UE_LOG(LogUvrInput, Verbose, TEXT("Updating device: %s"), *GetId());
		m_pDevImpl->mainloop();
	}
}

bool UvrVrpnButtonInputDevice::Initialize()
{
	FString addr;
	if (!ExtractParam(FString(UvrStrings::cfg::data::input::Address), addr))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - device address not found"), *ToString());
		return false;
	}

	// Instantiate device implementation
	m_pDevImpl.Reset(new vrpn_Button_Remote(TCHAR_TO_UTF8(*addr)));
	// Register update handler
	if(m_pDevImpl->register_change_handler(this, &UvrVrpnButtonInputDevice::HandleButtonDevice) != 0)
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - couldn't register VRPN change handler"), *ToString());
		return false;
	}

	// Base initialization
	return UvrVrpnButtonInputDataHolder::Initialize();
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrVrpnButtonInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
void VRPN_CALLBACK UvrVrpnButtonInputDevice::HandleButtonDevice(void *userData, vrpn_BUTTONCB const b)
{
	auto pDev = reinterpret_cast<UvrVrpnButtonInputDevice*>(userData);
	
	auto pItem = pDev->m_data.Find(b.button);
	if (!pItem)
	{
		pItem = &pDev->m_data.Add(b.button);
		// Explicit initial old state set
		pItem->btnStateOld = false;
	}

	//@note: Actually the button can change state for several time during one update cycle. For example
	//       it could change 0->1->0. Then we will send only the latest state and as a result the state
	//       change won't be processed. I don't process such situations because it's not ok if button
	//       changes the state so quickly. It's probably a contact shiver or something else. Normal button
	//       usage will lead to state change separation between update frames.


	// Convert button state from int to bool here. Actually VRPN has only two states for
	// buttons (0-released, 1-pressed) but still uses int32 type for the state.
	pItem->btnStateNew = (b.state != 0);
	UE_LOG(LogUvrInput, VeryVerbose, TEXT("Button %s:%d - %d"), *pDev->GetId(), b.button, b.state);
}

