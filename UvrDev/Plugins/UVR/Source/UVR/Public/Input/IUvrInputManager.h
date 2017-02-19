// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once


struct IUvrInputManager
{
	virtual ~IUvrInputManager()
	{ }

	//////////////////////////////////////////////////////////////////////////
	// Device amount
	virtual uint32 GetAxisDeviceAmount()    const = 0;
	virtual uint32 GetButtonDeviceAmount()  const = 0;
	virtual uint32 GetTrackerDeviceAmount() const = 0;

	//////////////////////////////////////////////////////////////////////////
	// Device IDs
	virtual bool GetAxisDeviceIds   (TArray<FString>& ids) const = 0;
	virtual bool GetButtonDeviceIds (TArray<FString>& ids) const = 0;
	virtual bool GetTrackerDeviceIds(TArray<FString>& ids) const = 0;

	//////////////////////////////////////////////////////////////////////////
	// Simple input access
	virtual bool GetButtonState    (const FString& devId, const uint8 btn) const = 0;
	virtual bool IsButtonPressed   (const FString& devId, const uint8 btn) const = 0;
	virtual bool IsButtonReleased  (const FString& devId, const uint8 btn) const = 0;
	virtual bool WasButtonPressed  (const FString& devId, const uint8 btn) const = 0;
	virtual bool WasButtonReleased (const FString& devId, const uint8 btn) const = 0;

	virtual float GetAxis(const FString& devId, const uint8 axis) const = 0;

	virtual FVector  GetTrackerLocation(const FString& devId, const uint8 tr) const = 0;
	virtual FRotator GetTrackerRotation(const FString& devId, const uint8 tr) const = 0;
};
