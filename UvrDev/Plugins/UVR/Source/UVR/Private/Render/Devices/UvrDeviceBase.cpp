// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrDeviceBase.h"

#include "UvrPlugin.h"
#include "UvrScreenComponent.h"

#include "RHIStaticStates.h"

#include <utility>



UvrDeviceBase::UvrDeviceBase() :
	FRHICustomPresent(nullptr)
{
	UE_LOG(LogUvrRender, VeryVerbose, TEXT(".ctor UvrDeviceBase"));
}

UvrDeviceBase::~UvrDeviceBase()
{
	UE_LOG(LogUvrRender, VeryVerbose, TEXT(".dtor UvrDeviceBase"));
}

void UvrDeviceBase::WaitForBufferSwapSync(int32& InOutSyncInterval)
{
	// Perform SW synchronization
	UE_LOG(LogUvrRender, Verbose, TEXT("Waiting for swap sync..."));

	// Policies below are available for any render device type
	switch (m_swapSyncPolicy)
	{
	case EUvrSwapSyncPolicy::None:
	{
		exec_BarrierWait();
		InOutSyncInterval = 0;
		break;
	}

	default:
	{
		UE_LOG(LogUvrRender, Warning, TEXT("Swap sync policy drop: %d"), (int)m_swapSyncPolicy);
		InOutSyncInterval = 0;
		break;
	}
	}
}

void UvrDeviceBase::UpdateProjectionScreenDataForThisFrame()
{
	UE_LOG(LogUvrRender, VeryVerbose, TEXT("UpdateProjectionScreenDataForThisFrame"));
	check(IsInGameThread());

	// Store transformations of active projection screen
	auto pScreen = UvrPlugin::get().GameMgr->GetActiveScreen();
	if (pScreen)
	{
		m_projLoc  = pScreen->GetComponentLocation();
		m_projRot  = pScreen->GetComponentRotation();
		m_projSize = pScreen->GetScreenSize();
	}
}

void UvrDeviceBase::exec_BarrierWait()
{
	double tTime = 0.f;
	double bTime = 0.f;

	auto* const controller = UvrPlugin::get().ClusterMgr->GetController();
	if (controller)
		controller->WaitForSwapSync(&tTime, &bTime);

	UE_LOG(LogUvrRender, Verbose, TEXT("Render barrier wait: t=%lf b=%lf"), tTime, bTime);
}

//////////////////////////////////////////////////////////////////////////////////////////////
// IStereoRendering
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrDeviceBase::IsStereoEnabled() const
{
	//UE_LOG(LogUvrRender, Verbose, TEXT("IsStereoEnabled"));
	return true;
}

bool UvrDeviceBase::IsStereoEnabledOnNextFrame() const
{
	//UE_LOG(LogUvrRender, Verbose, TEXT("IsStereoEnabledOnNextFrame"));
	return true;
}

bool UvrDeviceBase::EnableStereo(bool stereo /*= true*/)
{
	//UE_LOG(LogUvrRender, Verbose, TEXT("EnableStereo"));
	return true;
}

void UvrDeviceBase::CalculateStereoViewOffset(const enum EStereoscopicPass StereoPassType, const FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation)
{
	//UE_LOG(LogUvrRender, Verbose, TEXT("CalculateStereoViewOffset"));
	
	check(IsInGameThread());
	check(WorldToMeters > 0.f);

	UE_LOG(LogUvrRender, VeryVerbose, TEXT("OLD ViewLoc: %s, ViewRot: %s"), *ViewLocation.ToString(), *ViewRotation.ToString());

	// Make a little hack with view rotation according to off-axis projection matrix calculation.
	// View vector must be orthogonal to the projection plane.
	const_cast<FRotator&>(ViewRotation) = m_projRot;

	const float EyeDist = m_eyeDist * WorldToMeters;
	const float EyeOffset = EyeDist / 2.f;
	const float PassOffset = (StereoPassType == EStereoscopicPass::eSSP_LEFT_EYE ? -EyeOffset : EyeOffset);
	const float PassOffsetSwap = (m_eyeSwap == true ? -PassOffset : PassOffset);
	ViewLocation += ViewRotation.Quaternion().RotateVector(FVector(0, PassOffsetSwap, 0));

	const int eyeIdx = (StereoPassType == EStereoscopicPass::eSSP_LEFT_EYE ? 0 : 1);
	m_eyeLoc[eyeIdx] = ViewLocation;
	m_eyeRot[eyeIdx] = ViewRotation;

	UE_LOG(LogUvrRender, VeryVerbose, TEXT("NEW ViewLoc: %s, ViewRot: %s"), *ViewLocation.ToString(), *ViewRotation.ToString());
}


FMatrix UvrDeviceBase::GetStereoProjectionMatrix(const enum EStereoscopicPass StereoPassType, const float FOV) const
{
	//UE_LOG(LogUvrRender, Verbose, TEXT("GetStereoProjectionMatrix"));
	
	// Don't expect to be here
	check(StereoPassType != EStereoscopicPass::eSSP_FULL);
	
	const float n = GNearClippingPlane;
	const float f = 100000.f;

	// Half-size
	const float hw = m_projSize.X / 2.f;
	const float hh = m_projSize.Y / 2.f;

	// Screen corners
	const FVector pa = m_projLoc + m_projRot.Quaternion().RotateVector(GetPorjectionScreenGeometryLBC(StereoPassType, hw, hh)); // left bottom corner
	const FVector pb = m_projLoc + m_projRot.Quaternion().RotateVector(GetPorjectionScreenGeometryRBC(StereoPassType, hw, hh)); // right bottom corner
	const FVector pc = m_projLoc + m_projRot.Quaternion().RotateVector(GetPorjectionScreenGeometryLTC(StereoPassType, hw, hh)); // left top corner

	// Screen vectors
	FVector vr = pb - pa; // lb->rb normilized vector, right axis of projection screen
	vr.Normalize();
	FVector vu = pc - pa; // lb->lt normilized vector, up axis of projection screen
	vu.Normalize();
	FVector vn = -FVector::CrossProduct(vr, vu); // Projection plane normal. Use minus because of left-handed coordinate system
	vn.Normalize();

	const int eyeIdx = (StereoPassType == EStereoscopicPass::eSSP_LEFT_EYE ? 0 : 1);
	const FVector pe = m_eyeLoc[eyeIdx];
	const FVector va = pa - pe; // camera -> lb
	const FVector vb = pb - pe; // camera -> rb
	const FVector vc = pc - pe; // camera -> lt

	const float d = -FVector::DotProduct(va, vn); // distance from eye to screen
	const float ndifd = n / d;
	const float l = FVector::DotProduct(vr, va) * ndifd; // distance to left screen edge
	const float r = FVector::DotProduct(vr, vb) * ndifd; // distance to right screen edge
	const float b = FVector::DotProduct(vu, va) * ndifd; // distance to bottom screen edge
	const float t = FVector::DotProduct(vu, vc) * ndifd; // distance to top screen edge

	const float mx = 2.f * n / (r - l);
	const float my = 2.f * n / (t - b);
	const float ma = -(r + l) / (r - l);
	const float mb = -(t + b) / (t - b);
	const float mc = f / (f - n);
	const float md = -(f * n) / (f - n);
	const float me = 1.f;

	// Normal LHS
	const FMatrix pm = FMatrix(
		FPlane(mx, 0, 0, 0),
		FPlane(0, my, 0, 0),
		FPlane(ma, mb, mc, me),
		FPlane(0, 0, md, 0));

	// Invert Z-axis (UE4 uses Z-inverted LHS)
	const FMatrix flipZ = FMatrix(
		FPlane(1, 0,  0, 0),
		FPlane(0, 1,  0, 0),
		FPlane(0, 0, -1, 0),
		FPlane(0, 0,  1, 1));

	const FMatrix result(pm * flipZ);

	return result;
}

void UvrDeviceBase::InitCanvasFromView(class FSceneView* InView, class UCanvas* Canvas)
{
	//UE_LOG(LogUvrRender, Verbose, TEXT("InitCanvasFromView"));
}

void UvrDeviceBase::UpdateViewport(bool bUseSeparateRenderTarget, const class FViewport& InViewport, class SViewport* ViewportWidget)
{
	//UE_LOG(LogUvrRender, Verbose, TEXT("UpdateViewport"));
	check(IsInGameThread());

	// Update projection screen data
	UpdateProjectionScreenDataForThisFrame();

	// Save current dimensions
	m_viewportSize = InViewport.GetSizeXY();
	m_backBuffSize = InViewport.GetRenderTargetTextureSizeXY();

	// If no custom area specified the full viewport area will be used
	if (m_viewportArea.IsValid() == false)
	{
		m_viewportArea.SetLocation(FIntPoint::ZeroValue);
		m_viewportArea.SetSize(InViewport.GetSizeXY());
	}

	// Set up references
	FRHICustomPresent::ViewportRHI = InViewport.GetViewportRHI().GetReference();
	FRHICustomPresent::ViewportRHI->SetCustomPresent(this);
}

FRHICustomPresent* UvrDeviceBase::GetCustomPresent()
{
	//UE_LOG(LogUvrRender, Verbose, TEXT("GetCustomPresent"));
	return this;
}

void UvrDeviceBase::GetEyeRenderParams_RenderThread(const struct FRenderingCompositePassContext& Context, FVector2D& EyeToSrcUVScaleValue, FVector2D& EyeToSrcUVOffsetValue) const
{
	check(IsInRenderingThread());

}

void UvrDeviceBase::SetClippingPlanes(float NCP, float FCP)
{
	UE_LOG(LogUvrRender, Log, TEXT("SetClippingPlanes: NCP=%f FCP=%f"), NCP, FCP);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// FRHICustomPresent
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrDeviceBase::OnBackBufferResize()
{
	UE_LOG(LogUvrRender, Verbose, TEXT("OnBackBufferResize"));

	//@todo: see comment below
	// if we are in the middle of rendering: prevent from calling EndFrame
	//if (RenderContext.IsValid())
	//{
	//	RenderContext->bFrameBegun = false;
	//}
}

bool UvrDeviceBase::Present(int32& InOutSyncInterval)
{
	UE_LOG(LogUvrRender, Warning, TEXT("Present - default handler implementation. Check stereo device instantiation."));

	// Default behavior
	// Return false to force clean screen. This will indicate that something is going wrong
	// or particular stereo device hasn't been implemented appropriately yet.
	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrStereoDevice
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrDeviceBase::SetViewportArea(const FIntPoint& loc, const FIntPoint& size)
{
	UE_LOG(LogUvrRender, Log, TEXT("SetViewportArea: loc=%s size=%s"), *loc.ToString(), *size.ToString());

	m_viewportArea.SetLocation(loc);
	m_viewportArea.SetSize(size);
}

void UvrDeviceBase::SetDesktopStereoParams(float FOV)
{
	UE_LOG(LogUvrRender, Log, TEXT("SetDesktopStereoParams: FOV=%f"), FOV);
	//@todo
}

void UvrDeviceBase::SetDesktopStereoParams(const FVector2D& screenSize, const FIntPoint& screenRes, float screenDist)
{
	UE_LOG(LogUvrRender, Log, TEXT("SetDesktopStereoParams"));

	FVector2D size = screenSize;
	float dist = screenDist;

	//@todo:
}

void UvrDeviceBase::SetInterpupillaryDistance(float dist)
{
	UE_LOG(LogUvrRender, Log, TEXT("SetInterpupillaryDistance: %f"), dist);
	m_eyeDist = dist;
}

float UvrDeviceBase::GetInterpupillaryDistance() const
{
	UE_LOG(LogUvrRender, Verbose, TEXT("GetInterpupillaryDistance: %f"), m_eyeDist);
	return m_eyeDist;
}

void UvrDeviceBase::SetEyesSwap(bool swap)
{
	UE_LOG(LogUvrRender, Log, TEXT("SetEyesSwap: %s"), UvrHelpers::str::BoolToStr(swap));
	m_eyeSwap = swap;
}

bool UvrDeviceBase::GetEyesSwap() const
{
	UE_LOG(LogUvrRender, Verbose, TEXT("GetEyesSwap: %s"), UvrHelpers::str::BoolToStr(m_eyeSwap));
	return m_eyeSwap;
}

bool UvrDeviceBase::ToggleEyesSwap()
{
	m_eyeSwap = !m_eyeSwap;

	UE_LOG(LogUvrRender, Log, TEXT("ToggleEyesSwap: swap=%s"), UvrHelpers::str::BoolToStr(m_eyeSwap));
	return m_eyeSwap;
}

void UvrDeviceBase::SetOutputFlip(bool flipH, bool flipV)
{
	UE_LOG(LogUvrRender, Log, TEXT("SetOutputFlip: horizontal=%s vertical=%s"), UvrHelpers::str::BoolToStr(flipH), UvrHelpers::str::BoolToStr(flipV));
	
	m_flipH = flipH;
	m_flipV = flipV;
}

void UvrDeviceBase::GetOutputFlip(bool& flipH, bool& flipV) const
{
	UE_LOG(LogUvrRender, Verbose, TEXT("GetOutputFlip: horizontal=%s vertical=%s"), UvrHelpers::str::BoolToStr(m_flipH), UvrHelpers::str::BoolToStr(m_flipV));

	flipH = m_flipH;
	flipV = m_flipV;
}

void UvrDeviceBase::SetSwapSyncPolicy(EUvrSwapSyncPolicy policy)
{
	UE_LOG(LogUvrRender, Log, TEXT("Swap sync policy: %d"), (int)policy);
	
	// Since not all our devices are opengl compatible in terms of implementation
	// we have to perform some wrapping logic for the policies.
	switch (policy)
	{
	// Policies below are available for any render device type
	case EUvrSwapSyncPolicy::None:
		m_swapSyncPolicy = policy;
		break;

	default:
		UE_LOG(LogUvrRender, Error, TEXT("Unsupported policy type: %d"), (int)policy);
		m_swapSyncPolicy = EUvrSwapSyncPolicy::None;
		break;
	}
}

EUvrSwapSyncPolicy UvrDeviceBase::GetSwapSyncPolicy() const
{
	UE_LOG(LogUvrRender, Verbose, TEXT("GetSwapSyncPolicy: policy=%d"), (int)m_swapSyncPolicy);
	return m_swapSyncPolicy;
}

