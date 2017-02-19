// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrDeviceDebug.h"


void UvrDeviceDebug::AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const
{
	const int rHeight = SizeY / 4;

	if (StereoPass == EStereoscopicPass::eSSP_LEFT_EYE)
	{
		SizeY -= rHeight;
	}
	else
	{
		Y = SizeY - rHeight;
		SizeY = rHeight;
	}
}
