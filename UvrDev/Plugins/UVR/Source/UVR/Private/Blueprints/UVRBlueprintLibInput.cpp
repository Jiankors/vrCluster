// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UVRBlueprintLibInput.h"

#include "IUvrPlugin.h"
#include "Input/IUvrInputManager.h"


UUVRBlueprintLibInput::UUVRBlueprintLibInput(class FObjectInitializer const & ObjectInitializer) :
	Super(ObjectInitializer)
{

}


int32 UUVRBlueprintLibInput::UvrGetAxisDeviceAmount()
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		pMgr->GetAxisDeviceAmount();

	return 0;
}

int32 UUVRBlueprintLibInput::UvrGetButtonDeviceAmount()
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		pMgr->GetButtonDeviceAmount();

	return 0;
}

int32 UUVRBlueprintLibInput::UvrGetTrackerDeviceAmount()
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		pMgr->GetTrackerDeviceAmount();

	return 0;
}

TArray<FString> UUVRBlueprintLibInput::UvrGetAxisDeviceIds()
{
	TArray<FString> result;
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		pMgr->GetAxisDeviceIds(result);

	return result;
}

TArray<FString> UUVRBlueprintLibInput::UvrGetButtonDeviceIds()
{
	TArray<FString> result;
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		pMgr->GetButtonDeviceIds(result);

	return result;
}

TArray<FString> UUVRBlueprintLibInput::UvrGetTrackerDeviceIds()
{
	TArray<FString> result;
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		pMgr->GetTrackerDeviceIds(result);

	return result;
}

bool UUVRBlueprintLibInput::UvrGetButtonState(const FString& DeviceId, uint8 DeviceChannel)
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		return pMgr->GetButtonState(DeviceId, DeviceChannel);

	return false;
}

bool UUVRBlueprintLibInput::UvrIsButtonPressed(const FString& DeviceId, uint8 DeviceChannel)
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		return pMgr->IsButtonPressed(DeviceId, DeviceChannel);

	return false;
}

bool UUVRBlueprintLibInput::UvrIsButtonReleased(const FString& DeviceId, uint8 DeviceChannel)
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		return pMgr->IsButtonReleased(DeviceId, DeviceChannel);

	return false;
}

bool UUVRBlueprintLibInput::UvrWasButtonPressed(const FString& DeviceId, uint8 DeviceChannel)
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		return pMgr->WasButtonPressed(DeviceId, DeviceChannel);

	return false;
}

bool UUVRBlueprintLibInput::UvrWasButtonReleased(const FString& DeviceId, uint8 DeviceChannel)
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		return pMgr->WasButtonReleased(DeviceId, DeviceChannel);

	return false;
}

float UUVRBlueprintLibInput::UvrGetAxis(const FString& DeviceId, uint8 DeviceChannel)
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		return pMgr->GetAxis(DeviceId, DeviceChannel);

	return 0.f;
}

FVector UUVRBlueprintLibInput::UvrGetTrackerLocation(const FString& DeviceId, uint8 DeviceChannel)
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		return pMgr->GetTrackerLocation(DeviceId, DeviceChannel);

	return FVector::ZeroVector;
}

FRotator UUVRBlueprintLibInput::UvrGetTrackerRotation(const FString& DeviceId, uint8 DeviceChannel)
{
	IUvrInputManager* const pMgr = IUvrPlugin::Get().GetInputMgr();
	if (pMgr)
		return pMgr->GetTrackerRotation(DeviceId, DeviceChannel);

	return FRotator::ZeroRotator;
}


