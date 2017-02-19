// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrClusterNodeCtrlBase.h"

#include "UvrPlugin.h"


UvrClusterNodeCtrlBase::UvrClusterNodeCtrlBase(const FString& ctrlName, const FString& nodeName) :
	UvrNodeCtrlBase(ctrlName, nodeName)
{

}

UvrClusterNodeCtrlBase::~UvrClusterNodeCtrlBase()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrNodeController
//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrNodeCtrlBase
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrClusterNodeCtrlBase::InitializeStereo()
{
	SUvrConfigViewport vp;
	if (!UvrPlugin::get().ConfigMgr->GetLocalViewport(vp))
	{
		UE_LOG(LogUvrRender, Error, TEXT("Viewport config not found"));
		return false;
	}

	auto pDev = UvrPlugin::get().GetRenderMgr()->GetStereoDevice();
	if (pDev)
	{
		auto cfgStereo = UvrPlugin::get().ConfigMgr->GetConfigStereo();
		auto cfgGeneral = UvrPlugin::get().ConfigMgr->GetConfigGeneral();
		auto cfgRender = UvrPlugin::get().ConfigMgr->GetConfigRender();

		// Configure the device
		pDev->SetViewportArea(vp.Loc, vp.Size);
		pDev->SetEyesSwap(cfgStereo.EyeSwap);
		pDev->SetInterpupillaryDistance(cfgStereo.EyeDist);
		pDev->SetOutputFlip(vp.FlipHorizontal, vp.FlipVertical);
		pDev->SetSwapSyncPolicy((EUvrSwapSyncPolicy)cfgGeneral.SwapSyncPolicy);
	}
	else
	{
		UE_LOG(LogUvrRender, Warning, TEXT("Stereo device not found. Stereo initialization skipped."));
	}

	return UvrNodeCtrlBase::InitializeStereo();
}
