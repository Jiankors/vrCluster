// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Engine.h"
#include "StereoRendering.h"
#include "IUvrStereoDevice.h"

#include "Render/Devices/UvrViewportArea.h"


class UvrDeviceBase :
	public  IStereoRendering,
	public  IUvrStereoDevice,
	public  FRHICustomPresent,
	private UvrNoncopyable,
	private UvrNonmoveable
{
public:
	UvrDeviceBase();
	virtual ~UvrDeviceBase();

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IStereoRendering
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool IsStereoEnabled() const override;
	virtual bool IsStereoEnabledOnNextFrame() const override; // { return IsStereoEnabled(); }
	virtual bool EnableStereo(bool stereo = true) override;
	//virtual void AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const override;
	virtual void CalculateStereoViewOffset(const enum EStereoscopicPass StereoPassType, const FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation) override;
	virtual FMatrix GetStereoProjectionMatrix(const enum EStereoscopicPass StereoPassType, const float FOV) const override;
	virtual void InitCanvasFromView(class FSceneView* InView, class UCanvas* Canvas) override;
	virtual void UpdateViewport(bool bUseSeparateRenderTarget, const class FViewport& InViewport, class SViewport* ViewportWidget) override; // {}
	//virtual void CalculateRenderTargetSize(const class FViewport& InViewport, uint32& InOutSizeX, uint32& InOutSizeY) override; // {}
	//virtual bool NeedReAllocateViewportRenderTarget(const class FViewport& Viewport) override; // { return false; }
	//virtual bool ShouldUseSeparateRenderTarget() const override; // { return false; }
	virtual FRHICustomPresent* GetCustomPresent() override; // { return nullptr; }
	//virtual FVector2D GetTextSafeRegionBounds() const override; // { return FVector2D(0.75f, 0.75f); }
	virtual void GetEyeRenderParams_RenderThread(const struct FRenderingCompositePassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const override; // {}
	//virtual void GetTimewarpMatrices_RenderThread(const struct FRenderingCompositePassContext& Context, FMatrix& EyeRotationStart, FMatrix& EyeRotationEnd) const override; // {}
	//virtual void RenderTexture_RenderThread(class FRHICommandListImmediate& RHICmdList, class FRHITexture2D* BackBuffer, class FRHITexture2D* SrcTexture) const override; // {}
	//virtual void GetOrthoProjection(int32 RTWidth, int32 RTHeight, float OrthoDistance, FMatrix OrthoProjection[2]) const override; // has default implementation in the interface
	//virtual void SetScreenPercentage(float InScreenPercentage) override; // {}
	//virtual float GetScreenPercentage() const override; // { return 0.0f; }
	virtual void SetClippingPlanes(float NCP, float FCP) override; // {}
	//virtual uint32 GetNumberOfBufferedFrames() const override; // { return 1; }
	//virtual bool AllocateRenderTargetTexture(uint32 Index, uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 Flags, uint32 TargetableTextureFlags, FTexture2DRHIRef& OutTargetableTexture, FTexture2DRHIRef& OutShaderResourceTexture, uint32 NumSamples = 1) override; // { return false; }
	//virtual void UseImplicitHmdPosition(bool bInImplicitHmdPosition) override; // { bImplicitHmdPosition = bInImplicitHmdPosition; }

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// FRHICustomPresent
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void OnBackBufferResize() override;
	virtual bool Present(int32& InOutSyncInterval) override;
	//virtual void OnAcquireThreadOwnership() override; // {}
	//virtual void OnReleaseThreadOwnership() override; // {}

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrStereoDevice
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SetViewportArea(const FIntPoint& loc, const FIntPoint& size) override;
	virtual void SetDesktopStereoParams(float FOV) override;
	virtual void SetDesktopStereoParams(const FVector2D& screenSize, const FIntPoint& screenRes, float screenDist) override;
	virtual void SetInterpupillaryDistance(float dist) override;
	virtual float GetInterpupillaryDistance() const override;
	virtual void SetEyesSwap(bool swap) override;
	virtual bool GetEyesSwap() const override;
	virtual bool ToggleEyesSwap() override;
	virtual void SetOutputFlip(bool flipH, bool flipV) override;
	virtual void GetOutputFlip(bool& flipH, bool& flipV) const override;
	virtual void SetSwapSyncPolicy(EUvrSwapSyncPolicy policy) override;
	virtual EUvrSwapSyncPolicy GetSwapSyncPolicy() const override;

protected:
	// Implements buffer swap synchronization mechanism
	virtual void WaitForBufferSwapSync(int32& InOutSyncInterval);
	// Retrieves the projections screen data for current frame
	void UpdateProjectionScreenDataForThisFrame();

	// Custom projection screen geometry (hw - half-width, hh - half-height of projection screen)
	// Left bottom corner (from camera point view)
	virtual FVector GetPorjectionScreenGeometryLBC(const enum EStereoscopicPass StereoPassType, const float& hw, const float& hh) const
	{ return FVector(0.f, -hw, -hh);}
	
	// Right bottom corner (from camera point view)
	virtual FVector GetPorjectionScreenGeometryRBC(const enum EStereoscopicPass StereoPassType, const float& hw, const float& hh) const
	{ return FVector(0.f, hw, -hh);}

	// Left top corner (from camera point view)
	virtual FVector GetPorjectionScreenGeometryLTC(const enum EStereoscopicPass StereoPassType, const float& hw, const float& hh) const
	{ return FVector(0.f, -hw, hh);}

protected:
	void exec_BarrierWait();

protected:
	// Viewport and back buffer size
	FIntPoint m_backBuffSize = { 0, 0 };
	FIntPoint m_viewportSize = { 0, 0 };

	// Stereo parameters
	float m_eyeDist      = 0.064f; // meters
	bool  m_eyeSwap      = false;
	FVector  m_eyeLoc[2] = { FVector::ZeroVector, FVector::ZeroVector };
	FRotator m_eyeRot[2] = { FRotator::ZeroRotator, FRotator::ZeroRotator };

	// Viewport area settings
	UvrViewportArea m_viewportArea;

	// Render config
	bool m_flipH = false;
	bool m_flipV = false;

	// Projection screen data
	FVector   m_projLoc;
	FRotator  m_projRot;
	FVector2D m_projSize;

	// Swap sync policy
	EUvrSwapSyncPolicy m_swapSyncPolicy = EUvrSwapSyncPolicy::None;
};
