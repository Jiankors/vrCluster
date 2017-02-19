// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"

#include "Render/UvrRenderManager.h"
#include "Render/Devices/UvrDevices.h"

#include "UvrPlugin.h"

UvrRenderManager::UvrRenderManager()
{
	UE_LOG(LogUvrRender, Verbose, TEXT("UvrRenderManager .ctor"));
}

UvrRenderManager::~UvrRenderManager()
{
	UE_LOG(LogUvrRender, Verbose, TEXT("UvrRenderManager .dtor"));
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrManager
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrRenderManager::Init()
{
	if (!GEngine)
	{
		UE_LOG(LogUvrRender, Error, TEXT("GEngine variable not set"));
		return false;
	}

	UE_LOG(LogUvrRender, Log, TEXT("Instantiating stereo device..."));

	auto pDev = CreateStereoDevice();
	if (pDev)
	{
		// Store ptr for internal usage
		m_pDevice = static_cast<IUvrStereoDevice*>(pDev);
		// Set new device in the engine
		GEngine->StereoRenderingDevice = TSharedPtr<IStereoRendering, ESPMode::ThreadSafe>(static_cast<IStereoRendering*>(pDev));
	}

	return true;
}

void UvrRenderManager::Release()
{
	//@note: No need to release our device. It will be released in safe way by the engine.
}

bool UvrRenderManager::StartSession(const FString& configPath)
{
	return true;
}

void UvrRenderManager::EndSession()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrRenderManager
//////////////////////////////////////////////////////////////////////////////////////////////
IUvrStereoDevice* UvrRenderManager::GetStereoDevice()
{
	return m_pDevice;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrRenderManager
//////////////////////////////////////////////////////////////////////////////////////////////
UvrDeviceBase* UvrRenderManager::CreateStereoDevice()
{
	UvrDeviceBase* pDevice = nullptr;

	// No stereo in editor
	if (GIsEditor)
	{
		UE_LOG(LogUvrRender, Warning, TEXT("UVR stereo devices for editor mode are not allowed at the moment"));
		return nullptr;
	}

	// The debug stereo device is based on RHI level only. Therefore it
	// doesn't require any environment specialization
	if (FParse::Param(FCommandLine::Get(), UvrStrings::args::dev::Debug))
	{
		UE_LOG(LogUvrRender, Log, TEXT("Instantiating UVR debug stereo device..."));
		pDevice = new UvrDeviceDebug;
	}
	// Quad buffer stereo
	else if (FParse::Param(FCommandLine::Get(), UvrStrings::args::dev::QBS))
	{
		if (FParse::Param(FCommandLine::Get(), UvrStrings::args::api::GL3) ||
			FParse::Param(FCommandLine::Get(), UvrStrings::args::api::GL4))
		{
			UE_LOG(LogUvrRender, Log, TEXT("Instantiating UVR quad buffer stereo device..."));
			pDevice = new UvrDeviceQuadBufferStereo;
		}
	}
	// Side-by-side
	else if (FParse::Param(FCommandLine::Get(), UvrStrings::args::dev::SbS))
	{
		UE_LOG(LogUvrRender, Log, TEXT("Instantiating UVR side-by-side stereo device..."));
		pDevice = new UvrDeviceSideBySide;
	}
	// Top-bottom
	else if (FParse::Param(FCommandLine::Get(), UvrStrings::args::dev::TB))
	{
		UE_LOG(LogUvrRender, Log, TEXT("Instantiating UVR top-bottom stereo device..."));
		pDevice = new UvrDeviceTopBottom;
	}
	// Monoscopic
	else //if (FParse::Param(FCommandLine::Get(), UvrConstants::args::dev::Mono))
	{
		if (FParse::Param(FCommandLine::Get(), UvrStrings::args::api::GL3) ||
			FParse::Param(FCommandLine::Get(), UvrStrings::args::api::GL4))
		{
			UE_LOG(LogUvrRender, Log, TEXT("Instantiating UVR monoscopic device..."));
			pDevice = new UvrDeviceMonoscopic;
		}
	}

	return pDevice;
}
