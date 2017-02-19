// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrDeviceMonoscopic.h"

#include "Render/Devices/UvrDeviceInternals.h"

#include <utility>



UvrDeviceMonoscopic::UvrDeviceMonoscopic() :
	UvrDeviceBaseComplex(1)
{
}

UvrDeviceMonoscopic::~UvrDeviceMonoscopic()
{
}


void UvrDeviceMonoscopic::CalculateRenderTargetSize(const class FViewport& InViewport, uint32& InOutSizeX, uint32& InOutSizeY)
{
	//UE_LOG(LogUvrRender, Log, TEXT("UvrDeviceMonoscopic::CalculateRenderTargetSize"));
	check(IsInGameThread());

	InOutSizeX = InViewport.GetSizeXY().X;
	// Add one pixel height line for right eye (will be skipped on copy)
	InOutSizeY = InViewport.GetSizeXY().Y + 1;

	check(InOutSizeX > 0 && InOutSizeY > 0);
}


bool UvrDeviceMonoscopic::ShouldUseSeparateRenderTarget() const
{
	//UE_LOG(LogUvrRender, Log, TEXT("UvrDeviceMonoscopic::ShouldUseSeparateRenderTarget"));
	return true;
}

void UvrDeviceMonoscopic::AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const
{
	//UE_LOG(LogUvrRender, Log, TEXT("UvrDeviceMonoscopic::AdjustViewRect"));

	// We push right eye image to the thrash line in the bottom of render target
	if (StereoPass == EStereoscopicPass::eSSP_RIGHT_EYE)
	{
		Y = SizeY;
		SizeY = 1;
	}
}

void UvrDeviceMonoscopic::CalculateStereoViewOffset(const enum EStereoscopicPass StereoPassType, const FRotator& ViewRotation, const float WorldToMeters, FVector& ViewLocation)
{
	//UE_LOG(LogUvrRender, Log, TEXT("CalculateStereoViewOffset"));

	check(IsInGameThread());
	check(WorldToMeters > 0.f);

	// Make a little hack with view rotation according to off-axis projection matrix calculation.
	// View vector must be orthogonal to the projection plane.
	const_cast<FRotator&>(ViewRotation) = m_projRot;

	const int eyeIdx = (StereoPassType == EStereoscopicPass::eSSP_LEFT_EYE ? 0 : 1);
	m_eyeLoc[eyeIdx] = ViewLocation;
	m_eyeRot[eyeIdx] = ViewRotation;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Windows implementation
//////////////////////////////////////////////////////////////////////////////////////////////
#if PLATFORM_WINDOWS
bool UvrDeviceMonoscopic::Present(int32& InOutSyncInterval)
{
	UE_LOG(LogUvrRender, Verbose, TEXT("UvrDeviceMonoscopic::Present"));

	// Skip thrash line
	const int SizeY = m_backBuffSize.Y - 1;
	int dstX1 = m_viewportArea.GetLocation().X;
	int dstX2 = dstX1 + m_viewportArea.GetSize().X;

	// Convert to left bottom origin and flip Y
	int dstY1 = m_viewportSize.Y - m_viewportArea.GetLocation().Y;
	int dstY2 = dstY1 - m_viewportArea.GetSize().Y;

	if (m_flipH)
		std::swap(dstX1, dstX2);

	if (m_flipV)
		std::swap(dstY1, dstY2);

	FOpenGLViewport* pOglViewport = static_cast<FOpenGLViewport*>(FRHICustomPresent::ViewportRHI);
	check(pOglViewport);
	FPlatformOpenGLContext* const pContext = pOglViewport->GetGLContext();
	check(pContext && pContext->DeviceContext);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, pContext->ViewportFramebuffer);
	FOpenGL::ReadBuffer(GL_COLOR_ATTACHMENT0);

	FOpenGL::DrawBuffer(GL_BACK);
	FOpenGL::BlitFramebuffer(
		0, 0, m_backBuffSize.X, SizeY,
		dstX1, dstY1, dstX2, dstY2,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);

	glEnable(GL_FRAMEBUFFER_SRGB);

	// Perform buffers swap logic
	UvrDeviceBaseComplex::SwapBuffers(pOglViewport, InOutSyncInterval);
	REPORT_GL_END_BUFFER_EVENT_FOR_FRAME_DUMP();

	return false;
}
#endif


//////////////////////////////////////////////////////////////////////////////////////////////
// Linux implementation
//////////////////////////////////////////////////////////////////////////////////////////////
#if PLATFORM_LINUX
//@todo: Implementation for linux SDL2
bool UvrDeviceMonoscopic::Present(int32& InOutSyncInterval)
{
	// Forward to default implementation (should be a black screen)
	return UvrDeviceBase::Present(InOutSyncInterval);
}
#endif

