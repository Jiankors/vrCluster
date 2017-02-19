// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Render/Devices/UvrDeviceBaseSimple.h"


//////////////////////////////////////////////////////////////////////////////////////////////
// Debug device implementation
class UvrDeviceDebug : public UvrDeviceBaseSimple
{
	virtual void AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;
};


