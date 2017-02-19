// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrNodeCtrlStandalone.h"

#include "UvrPlugin.h"
#include "IUvrStereoDevice.h"


UvrNodeCtrlStandalone::UvrNodeCtrlStandalone(const FString& ctrlName, const FString& nodeName) :
	UvrNodeCtrlBase(ctrlName, nodeName)
{
}


UvrNodeCtrlStandalone::~UvrNodeCtrlStandalone()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrClusterSyncProtocol
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrNodeCtrlStandalone::WaitForGameStart()
{
	// Nothing special to do here in standalone mode
}

void UvrNodeCtrlStandalone::WaitForFrameStart()
{
	// Nothing special to do here in standalone mode
}

void UvrNodeCtrlStandalone::WaitForFrameEnd()
{
	// Nothing special to do here in standalone mode
}

void UvrNodeCtrlStandalone::WaitForTickEnd()
{
	// Nothing special to do here in standalone mode
}

void UvrNodeCtrlStandalone::GetDeltaTime(float& deltaTime)
{
	// Nothing special to do here in standalone mode
}

void UvrNodeCtrlStandalone::GetSyncData(UvrMessage::DataType& data)
{
	// Nothing special to do here in standalone mode
}

void UvrNodeCtrlStandalone::GetInputData(UvrMessage::DataType& data)
{
	// Nothing special to do here in standalone mode
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrSwapSyncProtocol
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrNodeCtrlStandalone::WaitForSwapSync(double* pThreadWaitTime, double* pBarrierWaitTime)
{
	// Nothing special to do here in standalone mode
}

//////////////////////////////////////////////////////////////////////////////////////////////
// UvrNodeCtrlBase
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrNodeCtrlStandalone::InitializeStereo()
{
	//@todo: initialize stereo for standalone mode

	return UvrNodeCtrlBase::InitializeStereo();
}
