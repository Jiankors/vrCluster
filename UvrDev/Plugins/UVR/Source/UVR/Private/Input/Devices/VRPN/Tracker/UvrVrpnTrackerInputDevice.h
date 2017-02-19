// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrVrpnTrackerInputDataHolder.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#include "vrpn/vrpn_Tracker.h"
#include "HideWindowsPlatformTypes.h"
#endif


class UvrVrpnTrackerInputDevice :
	public UvrVrpnTrackerInputDataHolder
{
public:
	UvrVrpnTrackerInputDevice(const SUvrConfigInput& config);
	virtual ~UvrVrpnTrackerInputDevice();

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrInputDevice
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Update() override;
	virtual void PostUpdate() override;
	virtual bool Initialize() override;

protected:
	// Per-channel dirty state
	TMap<int32, bool> m_dirtyMap;

	// Transform form tracker space to UVR space
	void TransformCoordinates(SUvrVrpnTrackerChannelData& data) const;


private:
	// Tracker origin
	FVector  m_OriginLoc = FVector::ZeroVector;
	FRotator m_OriginRot = FRotator::ZeroRotator;

private:
	// Coordinate system conversion
	enum AxisMapType { X = 0, NX, Y, NY, Z, NZ };

	// Internal conversion helpers
	AxisMapType String2Map(const FString& str, const AxisMapType defaultMap) const;
	FVector  GetMappedLocation(const FVector& loc, const AxisMapType front, const AxisMapType right, const AxisMapType up) const;
	FRotator GetMappedRotation(const FRotator& rot, const AxisMapType front, const AxisMapType right, const AxisMapType up) const;

	// Tracker space to UVR space axis mapping
	AxisMapType m_axisFront;
	AxisMapType m_axisRight;
	AxisMapType m_axisUp;

private:
	// Data update handler
	static void VRPN_CALLBACK HandleTrackerDevice(void *userData, vrpn_TRACKERCB const tr);

private:
	// The device (PIMPL)
	TUniquePtr<vrpn_Tracker_Remote> m_pDevImpl;
};
