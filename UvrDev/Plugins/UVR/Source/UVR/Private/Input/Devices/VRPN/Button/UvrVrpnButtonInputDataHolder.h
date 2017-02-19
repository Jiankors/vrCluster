// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Input/Devices/UvrInputDeviceTraits.h"
#include "Input/Devices/UvrInputDeviceBase.h"


class UvrVrpnButtonInputDataHolder :
	public UvrInputDeviceBase<EUvrInputDevice::VrpnButton>
{
public:
	UvrVrpnButtonInputDataHolder(const SUvrConfigInput& config);
	virtual ~UvrVrpnButtonInputDataHolder();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrInputDevice
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool Initialize() override;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrStringSerializable
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual FString SerializeToString() const override final;
	virtual bool    DeserializeFromString(const FString& data) override final;

private:
	// Serialization constants
	static constexpr auto SerializationDelimiter = TEXT("@");
	static constexpr auto SerializationItems = 3;
};
