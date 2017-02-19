// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrDeviceTopBottom.h"


void UvrDeviceTopBottom::AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const
{
	SizeY /= 2;
	if (StereoPass == EStereoscopicPass::eSSP_RIGHT_EYE)
		Y = SizeY;
}
