// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once


#if PLATFORM_WINDOWS
#include <windows.h>
#include <wingdi.h>
//#include <EGL/egl.h>
//#include <GL/glext.h>
//#include <GL/wglext.h>

#include "../../OpenGLDrv/Private/OpenGLDrvPrivate.h"
#include "../../OpenGLDrv/Public/OpenGLDrv.h"
#include "../../OpenGLDrv/Public/OpenGLResources.h"
#include "OpenGLResources.h"

extern PFNWGLSWAPINTERVALEXTPROC      uvr_wglSwapIntervalEXT_ProcAddress;

extern PFNWGLJOINSWAPGROUPNVPROC      uvr_wglJoinSwapGroupNV_ProcAddress;
extern PFNWGLBINDSWAPBARRIERNVPROC    uvr_wglBindSwapBarrierNV_ProcAddress;
extern PFNWGLQUERYSWAPGROUPNVPROC     uvr_wglQuerySwapGroupNV_ProcAddress;
extern PFNWGLQUERYMAXSWAPGROUPSNVPROC uvr_wglQueryMaxSwapGroupsNV_ProcAddress;
extern PFNWGLQUERYFRAMECOUNTNVPROC    uvr_wglQueryFrameCountNV_ProcAddress;
extern PFNWGLRESETFRAMECOUNTNVPROC    uvr_wglResetFrameCountNV_ProcAddress;


void UvrInitCapabilitiesForGL();

// This is redeclaration of WINDOWS specific FPlatformOpenGLContext
// which is declared in private OpenGLWindows.cpp file.
//@note: Keep it synced with original type (Engine\Source\Runtime\OpenGLDrv\Private\Windows\OpenGLWindows.cpp)
struct FPlatformOpenGLContext
{
	HWND WindowHandle;
	HDC DeviceContext;
	HGLRC OpenGLContext;
	bool bReleaseWindowOnDestroy;
	int32 SyncInterval;
	GLuint	ViewportFramebuffer;
	GLuint	VertexArrayObject;	// one has to be generated and set for each context (OpenGL 3.2 Core requirements)
	GLuint	BackBufferResource;
	GLenum	BackBufferTarget;
};
#endif



#if PLATFORM_LINUX
// This is redeclaration of LINUX specific FPlatformOpenGLContext
// which is declared in private OpenGLWindows.cpp file.
//@note: Keep it synced with original type (Engine\Source\Runtime\OpenGLDrv\Private\Linux\OpenGLLinux.cpp)
struct FPlatformOpenGLContext
{
	SDL_HWindow    hWnd;
	SDL_HGLContext hGLContext; // this is a (void*) pointer

	bool bReleaseWindowOnDestroy;
	int32 SyncInterval;
	GLuint	ViewportFramebuffer;
	GLuint	VertexArrayObject;	// one has to be generated and set for each context (OpenGL 3.2 Core requirements)
};

//@note: Place here any linux targeted device implementations
#endif

