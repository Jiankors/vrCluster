// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrInputManager.h"

#include "UvrPlugin.h"

#include "Devices/VRPN/Analog/UvrVrpnAnalogInputDevice.h"
#include "Devices/VRPN/Button/UvrVrpnButtonInputDevice.h"
#include "Devices/VRPN/Tracker/UvrVrpnTrackerInputDevice.h"



UvrInputManager::UvrInputManager()
{
	UE_LOG(LogUvrInput, Verbose, TEXT("UvrInputManager .ctor"));
}

UvrInputManager::~UvrInputManager()
{
	UE_LOG(LogUvrInput, Verbose, TEXT("UvrInputManager .dtor"));
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrManager
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrInputManager::Init()
{
	return true;
}

void UvrInputManager::Release()
{
}

bool UvrInputManager::StartSession(const FString& configPath)
{
	if (!InitDevices())
	{
		UE_LOG(LogUvrInput, Error, TEXT("Couldn't initialize input devices"));
		return false;
	}

	return true;
}

void UvrInputManager::EndSession()
{
	ReleaseDevices();
}

bool UvrInputManager::StartGame(UWorld* pWorld)
{
	return true;
}

void UvrInputManager::EndGame()
{
}

void UvrInputManager::PreTick(float DeltaSeconds)
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrInputManager
//////////////////////////////////////////////////////////////////////////////////////////////
// Basic functionality (device amount)
uint32 UvrInputManager::GetAxisDeviceAmount() const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetDeviceAmount_impl<EUvrInputDevice::VrpnAnalog>();
}

uint32 UvrInputManager::GetButtonDeviceAmount() const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetDeviceAmount_impl<EUvrInputDevice::VrpnButton>();
}

uint32 UvrInputManager::GetTrackerDeviceAmount() const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetDeviceAmount_impl<EUvrInputDevice::VrpnTracker>();
}

// Access to the device lists
bool UvrInputManager::GetAxisDeviceIds(TArray<FString>& ids) const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetDeviceIds_impl<EUvrInputDevice::VrpnAnalog>(ids);
}

bool UvrInputManager::GetButtonDeviceIds(TArray<FString>& ids) const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetDeviceIds_impl<EUvrInputDevice::VrpnButton>(ids);
}

bool UvrInputManager::GetTrackerDeviceIds(TArray<FString>& ids) const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetDeviceIds_impl<EUvrInputDevice::VrpnTracker>(ids);
}

// Simple input access
bool UvrInputManager::GetButtonState(const FString& devId, const uint8 btn) const
{
	SUvrVrpnButtonChannelData data;
	if (GetButtonData(devId, btn, data))
		return data.btnStateNew;

	return false;
}

bool UvrInputManager::IsButtonPressed(const FString& devId, const uint8 btn) const
{
	return GetButtonState(devId, btn) == true;
}

bool UvrInputManager::IsButtonReleased(const FString& devId, const uint8 btn) const
{
	return GetButtonState(devId, btn) == false;
}

bool UvrInputManager::WasButtonPressed(const FString& devId, const uint8 btn) const
{
	SUvrVrpnButtonChannelData data;
	if (GetButtonData(devId, btn, data))
		return data.btnStateOld == false && data.btnStateNew == true;

	return false;
}

bool UvrInputManager::WasButtonReleased(const FString& devId, const uint8 btn) const
{
	SUvrVrpnButtonChannelData data;
	if (GetButtonData(devId, btn, data))
		return data.btnStateOld == true && data.btnStateNew == false;

	return false;
}

float UvrInputManager::GetAxis(const FString& devId, const uint8 axis) const
{
	SUvrVrpnAnalogChannelData data;
	if (GetAxisData(devId, axis, data))
		return data.axisValue;

	return 0.f;
}

FVector UvrInputManager::GetTrackerLocation(const FString& devId, const uint8 tr) const
{
	SUvrVrpnTrackerChannelData data;
	if (GetTrackerData(devId, tr, data))
		return data.trLoc;

	return FVector::ZeroVector;
}

FRotator UvrInputManager::GetTrackerRotation(const FString& devId, const uint8 tr) const
{
	SUvrVrpnTrackerChannelData data;
	if (GetTrackerData(devId, tr, data))
		return data.trRot;

	return FRotator::ZeroRotator;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrInputManager
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrInputManager::Update()
{
	// Perform input update on master only. Slaves' state will be replicated later.
	if (UvrPlugin::get().ClusterMgr->IsMaster())
	{
		UE_LOG(LogUvrInput, Verbose, TEXT("Input update started"));
		{
			FScopeLock ScopeLock(&m_Lock);

			// Pre-Update
			UE_LOG(LogUvrInput, Verbose, TEXT("Input pre-update..."));
			for (auto classIt = m_devices.CreateIterator(); classIt; ++classIt)
			{
				for (auto devIt = classIt->Value.CreateConstIterator(); devIt; ++devIt)
				{
					devIt->Value->PreUpdate();
				}
			}

			// Update
			UE_LOG(LogUvrInput, Verbose, TEXT("Input update..."));
			for (auto classIt = m_devices.CreateIterator(); classIt; ++classIt)
			{
				for (auto devIt = classIt->Value.CreateConstIterator(); devIt; ++devIt)
				{
					devIt->Value->Update();
				}
			}

			// Post-Update
			for (auto classIt = m_devices.CreateIterator(); classIt; ++classIt)
			{
				for (auto devIt = classIt->Value.CreateConstIterator(); devIt; ++devIt)
				{
					devIt->Value->PostUpdate();
				}
			}
		}
		UE_LOG(LogUvrInput, Verbose, TEXT("Input update finished"));
	
		// Update input data cache for slave nodes
		UpdateInputDataCache();
	}
}

void UvrInputManager::ExportInputData(UvrMessage::DataType& data) const
{
	// Get data from cache
	data = m_packedTransferData;
}

void UvrInputManager::ImportInputData(const UvrMessage::DataType& data)
{
	FScopeLock ScopeLock(&m_Lock);

	for (auto rec : data)
	{
		FString strClassId;
		FString strDevId;
		if (rec.Key.Split(FString(SerializationDeviceTypeNameDelimiter), &strClassId, &strDevId))
		{
			UE_LOG(LogUvrInput, VeryVerbose, TEXT("Deserializing input device: <%s, %s>"), *rec.Key, *rec.Value);

			int classId = FCString::Atoi(*strClassId);
			if (m_devices.Contains(classId))
			{
				if (m_devices[classId].Contains(strDevId))
				{
					m_devices[classId][strDevId]->DeserializeFromString(rec.Value);
				}
			}
		}
	}
}


bool UvrInputManager::GetAxisData(const FString& devId, const uint8 channel, SUvrVrpnAnalogChannelData&  data) const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetChannelData_impl<EUvrInputDevice::VrpnAnalog>(devId, channel, data);
}

bool UvrInputManager::GetButtonData(const FString& devId, const uint8 channel, SUvrVrpnButtonChannelData&  data) const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetChannelData_impl<EUvrInputDevice::VrpnButton>(devId, channel, data);
}

bool UvrInputManager::GetTrackerData(const FString& devId, const uint8 channel, SUvrVrpnTrackerChannelData& data) const
{
	FScopeLock ScopeLock(&m_Lock);
	return GetChannelData_impl<EUvrInputDevice::VrpnTracker>(devId, channel, data);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrInputManager
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrInputManager::InitDevices()
{
	FScopeLock ScopeLock(&m_Lock);

	UE_LOG(LogUvrInput, Log, TEXT("Initializing input devices..."));

	const auto cfgInputDevs = UvrPlugin::get().ConfigMgr->GetInputDevices();

	for (auto& cfgDev : cfgInputDevs)
	{
		UE_LOG(LogUvrInput, Verbose, TEXT("Creating input device: %s"), *cfgDev.ToString());

		IUvrInputDevice* pDev = nullptr;

		if (cfgDev.Type == FString(UvrStrings::cfg::data::input::DeviceAnalog).ToLower())
		{
			if (UvrPlugin::get().ClusterMgr->IsMaster())
			{
				pDev = new UvrVrpnAnalogInputDevice(cfgDev);
			}
			else
			{
				pDev = new UvrVrpnAnalogInputDataHolder(cfgDev);
			}
		}
		else if (cfgDev.Type == FString(UvrStrings::cfg::data::input::DeviceButtons).ToLower())
		{
			if (UvrPlugin::get().ClusterMgr->IsMaster())
			{
				pDev = new UvrVrpnButtonInputDevice(cfgDev);
			}
			else
			{
				pDev = new UvrVrpnButtonInputDataHolder(cfgDev);
			}
		}
		else if (cfgDev.Type == FString(UvrStrings::cfg::data::input::DeviceTracker).ToLower())
		{
			if (UvrPlugin::get().ClusterMgr->IsMaster())
			{
				pDev = new UvrVrpnTrackerInputDevice(cfgDev);
			}
			else
			{
				pDev = new UvrVrpnTrackerInputDataHolder(cfgDev);
			}
		}
		else
		{
			UE_LOG(LogUvrInput, Error, TEXT("Unsupported device type: %s"), *cfgDev.Type);
			continue;
		}

		if (pDev && pDev->Initialize())
		{
			UE_LOG(LogUvrInput, Log, TEXT("Adding device: %s"), *pDev->ToString());
			
			auto pDevMap = m_devices.Find(pDev->GetTypeId());
			if (!pDevMap)
				pDevMap = &m_devices.Add(pDev->GetTypeId());

			pDevMap->Add(cfgDev.Id, TDevice(pDev));
		}
		else
		{
			UE_LOG(LogUvrInput, Warning, TEXT("Neither data holder nor true device was instantiated for item id: %s"), *cfgDev.Id);

			// It's safe to delete nullptr so no checking performed
			delete pDev;

			//@note: Allow other devices to be initialized. User will locate the problem from logs.
			//return false;
		}
	}

	return true;
}

void UvrInputManager::ReleaseDevices()
{
	FScopeLock ScopeLock(&m_Lock);

	UE_LOG(LogUvrInput, Log, TEXT("Releasing input subsystem..."));

	UE_LOG(LogUvrInput, Log, TEXT("Releasing input devices..."));
	m_devices.Empty();
}

void UvrInputManager::UpdateInputDataCache()
{
	FScopeLock ScopeLock(&m_Lock);

	// Clear previously cached data
	m_packedTransferData.Empty(m_packedTransferData.Num() | 0x07);

	for (auto classIt = m_devices.CreateConstIterator(); classIt; ++classIt)
	{
		for (auto devIt = classIt->Value.CreateConstIterator(); devIt; ++devIt)
		{
			const FString key = FString::Printf(TEXT("%d%s%s"), classIt->Key, SerializationDeviceTypeNameDelimiter, *devIt->Key);
			const FString val = devIt->Value->SerializeToString();
			UE_LOG(LogUvrInput, VeryVerbose, TEXT("Input device %d:%s serialized: <%s, %s>"), classIt->Key, *devIt->Key, *key, *val);
			m_packedTransferData.Add(key, val);
		}
	}
}
