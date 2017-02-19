// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrDeviceInternals.h"


#if PLATFORM_WINDOWS

#if WITH_EDITOR
void FOpenGLEventQuery::IssueEvent()
{
	VERIFY_GL_SCOPE();
	if (Sync)
	{
		FOpenGL::DeleteSync(Sync);
		Sync = UGLsync();
	}
	Sync = FOpenGL::FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	FOpenGL::Flush();

	checkSlow(FOpenGL::IsSync(Sync));

}

void FOpenGLEventQuery::WaitForCompletion()
{
	VERIFY_GL_SCOPE();


	checkSlow(FOpenGL::IsSync(Sync));


	// Wait up to 1/2 second for sync execution
	FOpenGL::EFenceResult Status = FOpenGL::ClientWaitSync(Sync, 0, 500 * 1000 * 1000);

	if (Status != FOpenGL::FR_AlreadySignaled && Status != FOpenGL::FR_ConditionSatisfied)
	{
		//failure of some type, determine type and send diagnostic message
		if (Status == FOpenGL::FR_TimeoutExpired)
		{
			UE_LOG(LogRHI, Log, TEXT("Timed out while waiting for GPU to catch up. (500 ms)"));
		}
		else if (Status == FOpenGL::FR_WaitFailed)
		{
			UE_LOG(LogRHI, Log, TEXT("Wait on GPU failed in driver"));
		}
		else
		{
			UE_LOG(LogRHI, Log, TEXT("Unknown error while waiting on GPU"));
			check(0);
		}
	}

}
#endif


PFNWGLSWAPINTERVALEXTPROC    uvr_wglSwapIntervalEXT_ProcAddress   = nullptr;

PFNWGLJOINSWAPGROUPNVPROC      uvr_wglJoinSwapGroupNV_ProcAddress   = nullptr;
PFNWGLBINDSWAPBARRIERNVPROC    uvr_wglBindSwapBarrierNV_ProcAddress = nullptr;
PFNWGLQUERYSWAPGROUPNVPROC     uvr_wglQuerySwapGroupNV_ProcAddress = nullptr;
PFNWGLQUERYMAXSWAPGROUPSNVPROC uvr_wglQueryMaxSwapGroupsNV_ProcAddress = nullptr;
PFNWGLQUERYFRAMECOUNTNVPROC    uvr_wglQueryFrameCountNV_ProcAddress = nullptr;
PFNWGLRESETFRAMECOUNTNVPROC    uvr_wglResetFrameCountNV_ProcAddress = nullptr;


// Copy/pasted from OpenGLDrv.cpp
static void UvrGetExtensionsString(FString& ExtensionsString)
{
	GLint ExtensionCount = 0;
	ExtensionsString = TEXT("");
	if (FOpenGL::SupportsIndexedExtensions())
	{
		glGetIntegerv(GL_NUM_EXTENSIONS, &ExtensionCount);
		for (int32 ExtensionIndex = 0; ExtensionIndex < ExtensionCount; ++ExtensionIndex)
		{
			const ANSICHAR* ExtensionString = FOpenGL::GetStringIndexed(GL_EXTENSIONS, ExtensionIndex);

			ExtensionsString += TEXT(" ");
			ExtensionsString += ANSI_TO_TCHAR(ExtensionString);
		}
	}
	else
	{
		const ANSICHAR* GlGetStringOutput = (const ANSICHAR*)glGetString(GL_EXTENSIONS);
		if (GlGetStringOutput)
		{
			ExtensionsString += GlGetStringOutput;
			ExtensionsString += TEXT(" ");
		}
	}
}

// https://www.opengl.org/wiki/Load_OpenGL_Functions
static void* UvrGetGLFuncAddress(const char *name)
{
	//void *p = (void *)wglGetProcAddress(name);
	//if (p == 0 ||
	//	(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
	//	(p == (void*)-1))
	//{
	//	HMODULE module = LoadLibraryA("opengl32.dll");
	//	p = (void *)GetProcAddress(module, name);
	//}
	//return p;
	HMODULE module = LoadLibraryA("opengl32.dll");
	return (void *)GetProcAddress(module, name);
}

// Copy/pasted from OpenGLDevice.cpp
// static void InitRHICapabilitiesForGL()
void UvrInitCapabilitiesForGL()
{
	bool bWindowsSwapControlExtensionPresent = false;
	{
		FString ExtensionsString;
		UvrGetExtensionsString(ExtensionsString);

		if (ExtensionsString.Contains(TEXT("WGL_EXT_swap_control")))
		{
			bWindowsSwapControlExtensionPresent = true;
		}
	}

#pragma warning(push)
#pragma warning(disable:4191)
	if (bWindowsSwapControlExtensionPresent)
	{
		uvr_wglSwapIntervalEXT_ProcAddress = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
		//uvr_wglSwapIntervalEXT_ProcAddress = (PFNWGLSWAPINTERVALEXTPROC)UvrGetGLFuncAddress("wglSwapIntervalEXT");
		//HMODULE module = LoadLibraryA("opengl32.dll");
		//if (module != NULL)
		//{
		//	uvr_wglSwapIntervalEXT_ProcAddress = (PFNWGLSWAPINTERVALEXTPROC)(void *)::GetProcAddress(module, "wglSwapIntervalEXT");
		//	FreeLibrary(module);
		//}
	}

	uvr_wglJoinSwapGroupNV_ProcAddress      = (PFNWGLJOINSWAPGROUPNVPROC)wglGetProcAddress("wglJoinSwapGroupNV");
	uvr_wglBindSwapBarrierNV_ProcAddress    = (PFNWGLBINDSWAPBARRIERNVPROC)wglGetProcAddress("wglBindSwapBarrierNV");
	uvr_wglQuerySwapGroupNV_ProcAddress     = (PFNWGLQUERYSWAPGROUPNVPROC)wglGetProcAddress("wglQuerySwapGroupNV");
	uvr_wglQueryMaxSwapGroupsNV_ProcAddress = (PFNWGLQUERYMAXSWAPGROUPSNVPROC)wglGetProcAddress("wglQueryMaxSwapGroupsNV");
	uvr_wglQueryFrameCountNV_ProcAddress    = (PFNWGLQUERYFRAMECOUNTNVPROC)wglGetProcAddress("wglQueryFrameCountNV");
	uvr_wglResetFrameCountNV_ProcAddress    = (PFNWGLRESETFRAMECOUNTNVPROC)wglGetProcAddress("wglResetFrameCountNV");

#pragma warning(pop)
}
#endif



#if PLATFORM_LINUX
#endif

