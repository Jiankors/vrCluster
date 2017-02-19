// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrDeviceQuadBufferStereo.h"

#include "Render/Devices/UvrDeviceInternals.h"

#include <utility>



UvrDeviceQuadBufferStereo::UvrDeviceQuadBufferStereo() :
	UvrDeviceBaseComplex(2)
{
}

UvrDeviceQuadBufferStereo::~UvrDeviceQuadBufferStereo()
{
}

void UvrDeviceQuadBufferStereo::CalculateRenderTargetSize(const class FViewport& InViewport, uint32& InOutSizeX, uint32& InOutSizeY)
{
	//UE_LOG(LogUvrRender, Log, TEXT("CalculateRenderTargetSize"));
	check(IsInGameThread());

	InOutSizeX = InViewport.GetSizeXY().X;
	InOutSizeY = InViewport.GetSizeXY().Y * 2;

	check(InOutSizeX > 0 && InOutSizeY > 0);
}


bool UvrDeviceQuadBufferStereo::ShouldUseSeparateRenderTarget() const
{
	//UE_LOG(LogUvrRender, Log, TEXT("ShouldUseSeparateRenderTarget"));
	return true;
}

void UvrDeviceQuadBufferStereo::AdjustViewRect(enum EStereoscopicPass StereoPass, int32& X, int32& Y, uint32& SizeX, uint32& SizeY) const
{
	//UE_LOG(LogUvrRender, Log, TEXT("AdjustViewRect"));

	// We combine images vertically because it's most likely that viewport width is greater than its height
	Y = (StereoPass == EStereoscopicPass::eSSP_RIGHT_EYE ? SizeY : 0);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// Windows implementation
//////////////////////////////////////////////////////////////////////////////////////////////
#if PLATFORM_WINDOWS
bool UvrDeviceQuadBufferStereo::Present(int32& InOutSyncInterval)
{
	UE_LOG(LogUvrRender, Verbose, TEXT("UvrDeviceQuadBufferStereo::Present"));

	const int halfSizeY = m_backBuffSize.Y / 2;
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
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	glDrawBuffer(GL_BACK_LEFT);
	glBlitFramebuffer(
		0, 0, m_backBuffSize.X, halfSizeY,
		dstX1, dstY1, dstX2, dstY2,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);

	glDrawBuffer(GL_BACK_RIGHT);
	glBlitFramebuffer(
		0, halfSizeY, m_backBuffSize.X, m_backBuffSize.Y,
		dstX1, dstY1, dstX2, dstY2,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);

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
bool UvrDeviceQuadBufferStereo::Present(int32& InOutSyncInterval)
{
	// Forward to default implementation (should be a black screen)
	return UvrDeviceBase::Present(InOutSyncInterval);
}
#endif

