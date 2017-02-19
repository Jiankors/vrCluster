// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Render/Devices/UvrDeviceBaseComplex.h"


class UvrDeviceMonoscopic : public UvrDeviceBaseComplex
{
public:
	UvrDeviceMonoscopic();
	virtual ~UvrDeviceMonoscopic();

protected:
	virtual void AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;
	virtual bool ShouldUseSeparateRenderTarget() const override;
	virtual void CalculateRenderTargetSize(const class FViewport& InViewport, uint32& InOutSizeX, uint32& InOutSizeY) override;
	virtual void CalculateStereoViewOffset(const enum EStereoscopicPass StereoPassType, const FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation) override;
	virtual bool Present(int32& InOutSyncInterval) override;

private:
	// Custom projection screen geometry (hw - half-width, hh - half-height of projection screen)
	// Left bottom corner (from camera point view)
	virtual FVector GetPorjectionScreenGeometryLBC(const enum EStereoscopicPass StereoPassType, const float& hw, const float& hh) const override
	{ return (StereoPassType == EStereoscopicPass::eSSP_LEFT_EYE ? FVector(0.f, -hw, -hh) : FVector(0.f, -0.1f, -0.1f)); }
	
	// Right bottom corner (from camera point view)
	virtual FVector GetPorjectionScreenGeometryRBC(const enum EStereoscopicPass StereoPassType, const float& hw, const float& hh) const override
	{ return (StereoPassType == EStereoscopicPass::eSSP_LEFT_EYE ? FVector(0.f, hw, -hh) : FVector(0.f, 0.1f, -0.1f)); }

	// Left top corner (from camera point view)
	virtual FVector GetPorjectionScreenGeometryLTC(const enum EStereoscopicPass StereoPassType, const float& hw, const float& hh) const override
	{ return (StereoPassType == EStereoscopicPass::eSSP_LEFT_EYE ? FVector(0.f, -hw, hh) : FVector(0.f, -0.1f, 0.1f)); }
};
