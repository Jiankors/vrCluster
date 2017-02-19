// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Devices/UvrInputDeviceTraits.h"
#include "Network/UvrMessage.h"

struct IUvrInputDevice;
struct SUvrVrpnAnalogChannelData;
struct SUvrVrpnButtonChannelData;
struct SUvrVrpnTrackerChannelData;


class UvrInputManager :
	public  IPUvrInputManager,
	private UvrNoncopyable,
	private UvrNonmoveable
{
public:
	UvrInputManager();
	virtual ~UvrInputManager();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool Init() override;
	virtual void Release() override;
	virtual bool StartSession(const FString& configPath) override;
	virtual void EndSession() override;
	virtual bool StartGame(UWorld* pWorld) override;
	virtual void EndGame() override;
	virtual void PreTick(float DeltaSeconds);

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrInputManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Device amount
	virtual uint32 GetAxisDeviceAmount()    const override;
	virtual uint32 GetButtonDeviceAmount()  const override;
	virtual uint32 GetTrackerDeviceAmount() const override;

	// Device IDs
	virtual bool GetAxisDeviceIds   (TArray<FString>& ids) const override;
	virtual bool GetButtonDeviceIds (TArray<FString>& ids) const override;
	virtual bool GetTrackerDeviceIds(TArray<FString>& ids) const override;

	// Simple input access
	virtual bool GetButtonState    (const FString& devId, const uint8 btn) const override;
	virtual bool IsButtonPressed   (const FString& devId, const uint8 btn) const override;
	virtual bool IsButtonReleased  (const FString& devId, const uint8 btn) const override;
	virtual bool WasButtonPressed  (const FString& devId, const uint8 btn) const override;
	virtual bool WasButtonReleased (const FString& devId, const uint8 btn) const override;
	virtual float GetAxis(const FString& devId, const uint8 axis) const override;
	virtual FVector  GetTrackerLocation(const FString& devId, const uint8 tr) const override;
	virtual FRotator GetTrackerRotation(const FString& devId, const uint8 tr) const override;

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IPUvrInputManager
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Update() override;

	virtual void ExportInputData(UvrMessage::DataType& data) const override;
	virtual void ImportInputData(const UvrMessage::DataType& data) override;

private:
	typedef TUniquePtr<IUvrInputDevice>    TDevice;
	typedef TMap<FString, TDevice>         TDeviceClassMap;
	typedef TMap<int, TDeviceClassMap>     TDeviceMap;

	bool InitDevices();
	void ReleaseDevices();
	void UpdateInputDataCache();

	// Device data
	bool GetAxisData   (const FString& devId, const uint8 channel, SUvrVrpnAnalogChannelData&  data) const;
	bool GetButtonData (const FString& devId, const uint8 channel, SUvrVrpnButtonChannelData&  data) const;
	bool GetTrackerData(const FString& devId, const uint8 channel, SUvrVrpnTrackerChannelData& data) const;

private:
	mutable FCriticalSection m_Lock;
	
	// Input devices
	TDeviceMap m_devices;
	// Input state data cache
	UvrMessage::DataType m_packedTransferData;

private:

	template<int DevTypeID>
	uint32 GetDeviceAmount_impl() const
	{
		if (!m_devices.Contains(DevTypeID))
			return 0;

		return static_cast<uint32>(m_devices[DevTypeID].Num());
	}

	template<int DevTypeID>
	bool GetDeviceIds_impl(TArray<FString>& ids) const
	{
		if (!m_devices.Contains(DevTypeID))
			return false;

		m_devices[DevTypeID].GenerateKeyArray(ids);
		return true;
	}

	template<int DevTypeID>
	bool GetChannelData_impl(const FString& devId, const uint8 channel, typename uvr_input_device_traits<DevTypeID>::dev_channel_data_type& data) const
	{
		if (!m_devices.Contains(DevTypeID))
			return false;

		if (!m_devices[DevTypeID].Contains(devId))
			return false;

		return static_cast<UvrInputDeviceBase<DevTypeID>*>(m_devices[DevTypeID][devId].Get())->GetChannelData(channel, data);
	}

private:
	static constexpr auto SerializationDeviceTypeNameDelimiter = TEXT(" ");
};

