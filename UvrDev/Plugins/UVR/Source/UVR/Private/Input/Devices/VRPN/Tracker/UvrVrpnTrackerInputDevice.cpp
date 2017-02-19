// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrVrpnTrackerInputDevice.h"

#include "UvrPlugin.h"


UvrVrpnTrackerInputDevice::UvrVrpnTrackerInputDevice(const SUvrConfigInput& config) :
	UvrVrpnTrackerInputDataHolder(config)
{
}

UvrVrpnTrackerInputDevice::~UvrVrpnTrackerInputDevice()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrVrpnTrackerInputDevice::Update()
{
	if (m_pDevImpl)
	{
		UE_LOG(LogUvrInput, Verbose, TEXT("Updating device: %s"), *GetId());
		m_pDevImpl->mainloop();
	}
}

void UvrVrpnTrackerInputDevice::PostUpdate()
{
	// Perform coordinates conversion
	for (auto it = m_data.CreateIterator(); it; ++it)
	{
		if (m_dirtyMap.Contains(it->Key))
		{
			// Convert data from updated channels only
			if (m_dirtyMap[it->Key] == true)
			{
				TransformCoordinates(it->Value);
				m_dirtyMap[it->Key] = false;
			}
		}
	}
}

bool UvrVrpnTrackerInputDevice::Initialize()
{
	FString addr;
	if (!ExtractParam(UvrStrings::cfg::data::input::Address, addr))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - device address not found"), *ToString());
		return false;
	}

	// Instantiate device implementation
	m_pDevImpl.Reset(new vrpn_Tracker_Remote(TCHAR_TO_UTF8(*addr)));

	// Register update handler
	if (m_pDevImpl->register_change_handler(this, &UvrVrpnTrackerInputDevice::HandleTrackerDevice) != 0)
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - couldn't register VRPN change handler"), *ToString());
		return false;
	}

	// Extract tracker location
	FString loc;
	if (!ExtractParam(UvrStrings::cfg::data::Loc, loc, false))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - tracker origin location not found"), *ToString());
		return false;
	}

	// Extract tracker rotation
	FString rot;
	if (!ExtractParam(UvrStrings::cfg::data::Rot, rot, false))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - tracker origin rotation not found"), *ToString());
		return false;
	}

	// Parse location
	if (!m_OriginLoc.InitFromString(loc))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - unable to parse the tracker origin location"), *ToString());
		return false;
	}

	// Parse rotation
	if (!m_OriginRot.InitFromString(rot))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - unable to parse the tracker origin rotation"), *ToString());
		return false;
	}

	// Parse 'right' axis mapping
	FString right;
	if (!ExtractParam(UvrStrings::cfg::data::input::Right, right))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - 'right' axis mapping not found"), *ToString());
		return false;
	}

	// Parse 'forward' axis mapping
	FString front;
	if (!ExtractParam(UvrStrings::cfg::data::input::Front, front))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - 'front' axis mapping not found"), *ToString());
		return false;
	}

	// Parse 'up' axis mapping
	FString up;
	if (!ExtractParam(UvrStrings::cfg::data::input::Up, up))
	{
		UE_LOG(LogUvrInput, Error, TEXT("%s - 'up' axis mapping not found"), *ToString());
		return false;
	}

	// Store mapping rules
	m_axisFront = String2Map(front, AxisMapType::X);
	m_axisRight = String2Map(right, AxisMapType::Y);
	m_axisUp = String2Map(up, AxisMapType::Z);

	// Base initialization
	return UvrVrpnTrackerInputDataHolder::Initialize();
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrVrpnTrackerInputDevice
//////////////////////////////////////////////////////////////////////////////////////////////
#ifdef UVR_USE_GENERIC_COORDINATE_SYSTEM_CONVERSION
namespace
{
	// Location
	float LocGetX(const FVector& loc)  { return  loc.X; }
	float LocGetNX(const FVector& loc) { return -loc.X; }

	float LocGetY(const FVector& loc)  { return  loc.Y; }
	float LocGetNY(const FVector& loc) { return -loc.Y; }

	float LocGetZ(const FVector& loc)  { return  loc.Z; }
	float LocGetNZ(const FVector& loc) { return -loc.Z; }

	// Rotation
	float RotGetP(const FRotator& rot)  { return  rot.Pitch; }
	float RotGetNP(const FRotator& rot) { return -rot.Pitch; }

	float RotGetY(const FRotator& rot)  { return  rot.Yaw; }
	float RotGetNY(const FRotator& rot) { return -rot.Yaw; }

	float RotGetR(const FRotator& rot)  { return  rot.Roll; }
	float RotGetNR(const FRotator& rot) { return -rot.Roll; }

	typedef float(*TLocGetter)(const FVector&  loc);
	typedef float(*TRotGetter)(const FRotator& rot);
}
#endif

UvrVrpnTrackerInputDevice::AxisMapType UvrVrpnTrackerInputDevice::String2Map(const FString& str, const AxisMapType defaultMap) const
{
	const FString mapVal = str.ToLower();

	if (mapVal == UvrStrings::cfg::data::input::MapX)
		return AxisMapType::X;
	else if (mapVal == UvrStrings::cfg::data::input::MapNX)
		return AxisMapType::NX;
	else if (mapVal == UvrStrings::cfg::data::input::MapY)
		return AxisMapType::Y;
	else if (mapVal == UvrStrings::cfg::data::input::MapNY)
		return AxisMapType::NY;
	else if (mapVal == UvrStrings::cfg::data::input::MapZ)
		return AxisMapType::Z;
	else if (mapVal == UvrStrings::cfg::data::input::MapNZ)
		return AxisMapType::NZ;
	else
	{
		UE_LOG(LogUvrInput, Warning, TEXT("Unknown mapping type: %s"), *str);
	}

	return defaultMap;
}

FVector UvrVrpnTrackerInputDevice::GetMappedLocation(const FVector& loc, const AxisMapType front, const AxisMapType right, const AxisMapType up) const
{
#ifdef UVR_USE_GENERIC_COORDINATE_SYSTEM_CONVERSION
	static TLocGetter funcs[] = { &LocGetX, &LocGetNX, &LocGetY, &LocGetNY, &LocGetZ, &LocGetNZ };
	return FVector(funcs[front](loc), funcs[right](loc), funcs[up](loc));
#else
	// Hard-coded IS-900 (X, Y, -Z) conversion
	return FVector(loc.X, loc.Y, -loc.Z);
#endif
}

FRotator UvrVrpnTrackerInputDevice::GetMappedRotation(const FRotator& rot, const AxisMapType front, const AxisMapType right, const AxisMapType up) const
{
#ifdef UVR_USE_GENERIC_COORDINATE_SYSTEM_CONVERSION
	//@todo: Generic conversion needed. We have to have a rotation matrices based math.
	static TRotGetter funcs[] = { &RotGetR, &RotGetNR, &RotGetY, &RotGetNY, &RotGetP, &RotGetNP };
	return FRotator(funcs[up](rot), funcs[right](rot), funcs[front](rot)); // PYR
#else
	// Hard-coded IS-900 (X, Y, -Z) conversion
	return FRotator(-rot.Pitch, rot.Yaw, -rot.Roll);
#endif
}

void UvrVrpnTrackerInputDevice::TransformCoordinates(SUvrVrpnTrackerChannelData &data) const
{
	UE_LOG(LogUvrInput, VeryVerbose, TEXT("TransformCoordinates old: <loc:%s> <rot:%s>"), *data.trLoc.ToString(), *data.trRot.ToString());

	// Transform location
	data.trLoc = m_OriginLoc + GetMappedLocation(data.trLoc, m_axisFront, m_axisRight, m_axisUp);
	data.trLoc *= UvrPlugin::get().GetWorld()->GetWorldSettings()->WorldToMeters;

	// Transform rotation
	data.trRot += m_OriginRot;
	data.trRot = GetMappedRotation(data.trRot, m_axisFront, m_axisRight, m_axisUp);

	UE_LOG(LogUvrInput, VeryVerbose, TEXT("TransformCoordinates new: <loc:%s> <rot:%s>"), *data.trLoc.ToString(), *data.trRot.ToString());
}

void VRPN_CALLBACK UvrVrpnTrackerInputDevice::HandleTrackerDevice(void *userData, vrpn_TRACKERCB const tr)
{
	auto pDev = reinterpret_cast<UvrVrpnTrackerInputDevice*>(userData);
	
	const FVector loc(tr.pos[0], tr.pos[1], tr.pos[2]);
	const FQuat quat(tr.quat[0], tr.quat[1], tr.quat[2], tr.quat[3]);

	const SUvrVrpnTrackerChannelData data{ loc, FRotator(quat) };
	auto pItem = &pDev->m_data.Add(tr.sensor, data);

	pDev->m_dirtyMap.Add(static_cast<int32>(tr.sensor), true);

	UE_LOG(LogUvrInput, VeryVerbose, TEXT("Tracker %s:%d {loc %s} {rot %s}"), *pDev->GetId(), tr.sensor, *pItem->trLoc.ToString(), *pItem->trRot.ToString());
}
