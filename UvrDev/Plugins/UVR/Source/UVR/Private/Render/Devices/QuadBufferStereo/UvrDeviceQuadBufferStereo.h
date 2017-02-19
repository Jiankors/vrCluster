// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Render/Devices/UvrDeviceBaseComplex.h"


class UvrDeviceQuadBufferStereo : public UvrDeviceBaseComplex
{
public:
	UvrDeviceQuadBufferStereo();
	virtual ~UvrDeviceQuadBufferStereo();

protected:
	virtual void AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;
	virtual bool ShouldUseSeparateRenderTarget() const override;
	virtual void CalculateRenderTargetSize(const class FViewport& InViewport, uint32& InOutSizeX, uint32& InOutSizeY) override;
	virtual bool Present(int32& InOutSyncInterval) override;
};
