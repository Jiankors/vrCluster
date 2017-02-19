// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrInputDeviceTraits.h"
#include "IUvrInputDevice.h"

template <int DevTypeID>
class UvrInputDeviceBase :
	public IUvrInputDevice
{
public:
	typedef typename uvr_input_device_traits<DevTypeID>::dev_channel_data_type   TChannelData;

public:
	UvrInputDeviceBase(const SUvrConfigInput& config);
	virtual ~UvrInputDeviceBase();

public:
	virtual bool GetChannelData(const uint8 channel, TChannelData& data) const;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrInputDevice
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual FString GetId() const override
	{ return m_ConfigData.Id; }

	virtual FString GetType() const override
	{ return m_ConfigData.Type; }

	virtual EUvrInputDevice::Type GetTypeId() const override
	{ return static_cast<EUvrInputDevice::Type>(DevTypeID); }

	virtual SUvrConfigInput GetConfig() const override
	{ return m_ConfigData; }

	virtual void PreUpdate() override
	{ }

	virtual void Update() override
	{ }

	virtual void PostUpdate() override
	{ }

	virtual FString ToString() const override
	{ return FString::Printf(TEXT("UVR input device: id=%s, type=%s"), *GetId(), *GetType()); }

protected:
	//@todo: move to string helpers
	bool ExtractParam(const FString& param, FString& value, bool bTrimQuotes = true) const;

	// Original config data
	const SUvrConfigInput m_ConfigData;
	// Device data
	TMap<int32, TChannelData> m_data;
};
