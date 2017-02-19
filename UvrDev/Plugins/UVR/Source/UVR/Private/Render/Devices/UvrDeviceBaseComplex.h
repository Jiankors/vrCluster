// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Render/Devices/UvrDeviceBase.h"
#include "UvrDeviceInternals.h"


class UvrDeviceBaseComplex : public UvrDeviceBase
{
public:
	UvrDeviceBaseComplex(int32 swapInterval);
	virtual ~UvrDeviceBaseComplex();

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IStereoRendering
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool NeedReAllocateViewportRenderTarget(const class FViewport& Viewport) override;

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrStereoDevice
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SetSwapSyncPolicy(EUvrSwapSyncPolicy policy) override;
	virtual void UpdateViewport(bool bUseSeparateRenderTarget, const class FViewport& InViewport, class SViewport* ViewportWidget) override;

protected:
	// Swap buffers
#if PLATFORM_WINDOWS
	void SwapBuffers(FOpenGLViewport* pOglViewport, int32& InOutSyncInterval);
#elif PLATFORM_LINUX
	void SwapBuffers();
#endif

private:
	// Set up swap interval for upcoming buffer swap
	void UpdateSwapInterval(int32 swapInt) const;
	// Joins swap groups and binds to a swap barrier
	bool InitializeNvidiaSwapLock();

#if PLATFORM_WINDOWS
	void internal_SwapBuffersPolicyNone(FOpenGLViewport* pOglViewport);
	void internal_SwapBuffersPolicySoftSwapSync(FOpenGLViewport* pOglViewport);
	void internal_SwapBuffersPolicyNvSwapSync(FOpenGLViewport* pOglViewport);
#endif

private:
	// State of nv_swap initialization
	bool m_nvSwapInitialized = false;

	float m_delay = 0.f;
	float m_delayStep = 0.001f;

	mutable FCriticalSection       m_lock;

	SUvrConfigCustom m_configCustom;
	int32 m_swapInterval;

	size_t m_frameIdx = 0;
};
