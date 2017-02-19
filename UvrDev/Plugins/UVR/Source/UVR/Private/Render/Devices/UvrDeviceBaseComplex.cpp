// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrDeviceBaseComplex.h"

#include "UvrPlugin.h"
#include "UvrHUD.h"

#include <cmath>



UvrDeviceBaseComplex::UvrDeviceBaseComplex(int32 swapInterval) :
	UvrDeviceBase(),
	m_swapInterval(swapInterval)
{
#if PLATFORM_WINDOWS
	UvrInitCapabilitiesForGL();
#endif

	if (UvrPlugin::get().ConfigMgr)
		m_configCustom = UvrPlugin::get().ConfigMgr->GetConfigCustom();

	if (m_configCustom.Args.Contains(FString("swap_int")))
	{
		m_swapInterval = FCString::Atoi(*m_configCustom.Args[FString("swap_int")]);
		UE_LOG(LogUvrRender, Verbose, TEXT("Custom swap interval: %d"), m_swapInterval);
	}

	UE_LOG(LogUvrRender, Verbose, TEXT("Use swap interval: %d"), m_swapInterval);
}


UvrDeviceBaseComplex::~UvrDeviceBaseComplex()
{
	//@todo: release barrier/group for nvswaplock
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IStereoRendering
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrDeviceBaseComplex::NeedReAllocateViewportRenderTarget(const class FViewport& Viewport)
{
	//UE_LOG(LogUvrRender, Log, TEXT("UvrDeviceMonoscopic::NeedReAllocateViewportRenderTarget"));
	check(IsInGameThread());

	const FIntPoint rtSize = Viewport.GetRenderTargetTextureSizeXY();
	uint32 newSizeX = rtSize.X;
	uint32 newSizeY = rtSize.Y;

	// Perform size calculation
	CalculateRenderTargetSize(Viewport, newSizeX, newSizeY);

	// Render target need to be re-allocated if its current size is invalid
	if (newSizeX != rtSize.X || newSizeY != rtSize.Y)
		return true;

	// No need to re-allocate
	return false;
}

void UvrDeviceBaseComplex::UpdateViewport(bool bUseSeparateRenderTarget, const class FViewport& InViewport, class SViewport* ViewportWidget)
{
	// Perform base update
	UvrDeviceBase::UpdateViewport(bUseSeparateRenderTarget, InViewport, ViewportWidget);

#if 0
	auto& inputMgr = UvrPlugin::get().InputMgr;
	if (inputMgr.IsValid())
	{
		if (inputMgr && inputMgr->WasButtonPressed(FString("WandButtons"), 1))
		{
			FScopeLock lock(&m_lock);
			m_delay = FMath::Clamp(m_delay - m_delayStep, 0.f, 1.f);
			UE_LOG(LogUvrRender, Log, TEXT("delay update: %lf"), m_delay);
		}
		else if (inputMgr && inputMgr->WasButtonPressed(FString("WandButtons"), 0))
		{
			FScopeLock lock(&m_lock);
			m_delay += m_delayStep;
			UE_LOG(LogUvrRender, Log, TEXT("delay update: %lf"), m_delay);
		}
	}

	AUvrHUD::ms_policy = (int)m_swapSyncPolicy;
	AUvrHUD::ms_Delay = m_delay;
#endif
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrStereoDevice
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrDeviceBaseComplex::SetSwapSyncPolicy(EUvrSwapSyncPolicy policy)
{
	FScopeLock lock(&m_lock);
	UE_LOG(LogUvrRender, Log, TEXT("Swap sync policy: %d"), (int)policy);

	switch (policy)
	{
	// Policies below are supported by all child implementations
	case EUvrSwapSyncPolicy::SoftSwapSync:
	case EUvrSwapSyncPolicy::NvSwapSync:
	{
		m_swapSyncPolicy = policy;
		break;
	}

	default:
		// Forward the policy type to the upper level
		UvrDeviceBase::SetSwapSyncPolicy(policy);
		break;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrDeviceBaseComplex
//////////////////////////////////////////////////////////////////////////////////////////////
#if PLATFORM_WINDOWS
void UvrDeviceBaseComplex::SwapBuffers(FOpenGLViewport* pOglViewport, int32& InOutSyncInterval)
{
	UE_LOG(LogUvrRender, Verbose, TEXT("FRAME IDX: %d"), m_frameIdx++);

	check(pOglViewport && pOglViewport->GetGLContext() && pOglViewport->GetGLContext()->DeviceContext);

#if 1 // TEMP
	///////////////////////////////////////////////
	// This is temporary workaround. Will be removed soon.
	if (UvrPlugin::get().ConfigMgr)
		m_configCustom = UvrPlugin::get().ConfigMgr->GetConfigCustom();

	if (m_configCustom.Args.Contains(FString("swap_int")))
	{
		m_swapInterval = FCString::Atoi(*m_configCustom.Args[FString("swap_int")]);
		UE_LOG(LogUvrRender, Verbose, TEXT("New swap interval: %d"), m_swapInterval);
	}
#endif

	// Debug delay before command queue processing
	if (m_delay > (m_delayStep / 2.f))
	{
		UE_LOG(LogUvrRender, Verbose, TEXT("Debug delay, sleeping for %f sec"), m_delay);
		FPlatformProcess::Sleep(m_delay);
	}

	{
		///////////////////////////////////////////////
		// Perform swap policy
		UE_LOG(LogUvrRender, Verbose, TEXT("Exec swap policy: %d"), (int)m_swapSyncPolicy);
		switch (m_swapSyncPolicy)
		{
		case EUvrSwapSyncPolicy::None:
			internal_SwapBuffersPolicyNone(pOglViewport);
			break;

		case EUvrSwapSyncPolicy::NvSwapSync:
			internal_SwapBuffersPolicyNvSwapSync(pOglViewport);
			break;

		case EUvrSwapSyncPolicy::SoftSwapSync:
			internal_SwapBuffersPolicySoftSwapSync(pOglViewport);
			break;

		default:
			UE_LOG(LogUvrRender, Error, TEXT("Unknown swap sync policy: %d"), (int)m_swapSyncPolicy);
			break;
		}
	}

	InOutSyncInterval = m_swapInterval;
	pOglViewport->GetGLContext()->SyncInterval = InOutSyncInterval;
}
#endif

#if PLATFORM_WINDOWS
void UvrDeviceBaseComplex::internal_SwapBuffersPolicyNone(FOpenGLViewport* pOglViewport)
{
	{
		///////////////////////////////////////////////
		// Swap buffers
		const double wtB = FPlatformTime::Seconds();
		::SwapBuffers(pOglViewport->GetGLContext()->DeviceContext);
		const double wtA = FPlatformTime::Seconds();

		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP bef: %lf"), wtB);
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP aft: %lf"), wtA);
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP diff: %lf"), wtA - wtB);
	}
}

void UvrDeviceBaseComplex::internal_SwapBuffersPolicySoftSwapSync(FOpenGLViewport* pOglViewport)
{
	exec_BarrierWait();
	UpdateSwapInterval(m_swapInterval);

	{
		///////////////////////////////////////////////
		// Issue frame event
		pOglViewport->IssueFrameEvent();
	}

	{
		///////////////////////////////////////////////
		// Wait until GPU finish last frame commands
		const double wtB = FPlatformTime::Seconds();
		pOglViewport->WaitForFrameEventCompletion();
		const double wtA = FPlatformTime::Seconds();
		
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT EVENT bef: %lf"), wtB);
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT EVENT aft: %lf"), wtA);
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT EVENT diff: %lf"), wtA - wtB);
	}

	// Sync all nodes
	exec_BarrierWait();

	//// Update swap interval right before swap buffers call
	//UpdateSwapInterval(m_swapInterval);

	{
		///////////////////////////////////////////////
		// Swap buffers
		const double wtB = FPlatformTime::Seconds();
		::SwapBuffers(pOglViewport->GetGLContext()->DeviceContext);
		const double wtA = FPlatformTime::Seconds();
		
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP bef: %lf"), wtB);
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP aft: %lf"), wtA);
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP diff: %lf"), wtA - wtB);
	}
}

void UvrDeviceBaseComplex::internal_SwapBuffersPolicyNvSwapSync(FOpenGLViewport* pOglViewport)
{
	// Use barrier once during NV barriers initialization
	if (m_nvSwapInitialized == false)
	{
		// Use render barrier to guaranty that all nv barriers are initialized simultaneously
		exec_BarrierWait();
		m_nvSwapInitialized = InitializeNvidiaSwapLock();
	}

	{
		///////////////////////////////////////////////
		// Swap buffers
		const double wtB = FPlatformTime::Seconds();
		::SwapBuffers(pOglViewport->GetGLContext()->DeviceContext);
		const double wtA = FPlatformTime::Seconds();
		
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP bef: %lf"), wtB);
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP aft: %lf"), wtA);
		UE_LOG(LogUvrRender, VeryVerbose, TEXT("WAIT SWAP diff: %lf"), wtA - wtB);
	}
}
#endif


#if PLATFORM_LINUX
void UvrDeviceBaseComplex::SwapBuffers()
{
	return;
}
#endif

void UvrDeviceBaseComplex::UpdateSwapInterval(int32 swapInt) const
{
#if PLATFORM_WINDOWS
	/*
	https://www.opengl.org/registry/specs/EXT/wgl_swap_control.txt
	wglSwapIntervalEXT specifies the minimum number of video frame periods
	per buffer swap for the window associated with the current context.
	The interval takes effect when SwapBuffers or wglSwapLayerBuffer
	is first called subsequent to the wglSwapIntervalEXT call.

	The parameter <interval> specifies the minimum number of video frames
	that are displayed before a buffer swap will occur.

	A video frame period is the time required by the monitor to display a
	full frame of video data.  In the case of an interlaced monitor,
	this is typically the time required to display both the even and odd
	fields of a frame of video data.  An interval set to a value of 2
	means that the color buffers will be swapped at most every other video
	frame.

	If <interval> is set to a value of 0, buffer swaps are not synchron-
	ized to a video frame.  The <interval> value is silently clamped to
	the maximum implementation-dependent value supported before being
	stored.

	The swap interval is not part of the render context state.  It cannot
	be pushed or popped.  The current swap interval for the window
	associated with the current context can be obtained by calling
	wglGetSwapIntervalEXT.  The default swap interval is 1.
	*/

	// Perform that each frame
	if (!uvr_wglSwapIntervalEXT_ProcAddress(swapInt))
		UE_LOG(LogUvrRender, Error, TEXT("Couldn't set swap interval: %d"), swapInt);

#endif //PLATFORM_WINDOWS
}


#if PLATFORM_WINDOWS
bool UvrDeviceBaseComplex::InitializeNvidiaSwapLock()
{
	if (m_nvSwapInitialized)
		return true;

	if (!uvr_wglJoinSwapGroupNV_ProcAddress || !uvr_wglBindSwapBarrierNV_ProcAddress)
	{
		UE_LOG(LogUvrRender, Error, TEXT("Group/Barrier functions not available"));
		return false;
	}

	if (!FRHICustomPresent::ViewportRHI)
	{
		UE_LOG(LogUvrRender, Warning, TEXT("Viewport RHI hasn't been initialized yet"))
		return false;
	}

	FOpenGLViewport* pOglViewport = static_cast<FOpenGLViewport*>(FRHICustomPresent::ViewportRHI);
	check(pOglViewport);
	FPlatformOpenGLContext* const pContext = pOglViewport->GetGLContext();
	check(pContext && pContext->DeviceContext);

	GLuint maxGroups = 0;
	GLuint maxBarriers = 0;

	if (!uvr_wglQueryMaxSwapGroupsNV_ProcAddress(pContext->DeviceContext, &maxGroups, &maxBarriers))
	{
		UE_LOG(LogUvrRender, Error, TEXT("Couldn't query gr/br limits: %d"), glGetError());
		return false;
	}

	UE_LOG(LogUvrRender, Log, TEXT("max_groups=%d max_barriers=%d"), (int)maxGroups, (int)maxBarriers);

	if (!(maxGroups > 0 && maxBarriers > 0))
	{
		UE_LOG(LogUvrRender, Error, TEXT("There are no available groups or barriers"));
		return false;
	}

	if (!uvr_wglJoinSwapGroupNV_ProcAddress(pContext->DeviceContext, 1))
	{
		UE_LOG(LogUvrRender, Error, TEXT("Couldn't join swap group: %d"), glGetError());
		return false;
	}
	else
	{
		UE_LOG(LogUvrRender, Log, TEXT("Successfully joined the swap group: 1"));
	}

	if (!uvr_wglBindSwapBarrierNV_ProcAddress(1, 1))
	{
		UE_LOG(LogUvrRender, Error, TEXT("Couldn't bind to swap barrier: %d"), glGetError());
		return false;
	}
	else
	{
		UE_LOG(LogUvrRender, Log, TEXT("Successfully binded to the swap barrier: 1"));
	}

	return true;
}
#endif


#if PLATFORM_LINUX
bool UvrDeviceBaseComplex::InitializeNvidiaSwapLock()
{
	return false;
}
#endif

