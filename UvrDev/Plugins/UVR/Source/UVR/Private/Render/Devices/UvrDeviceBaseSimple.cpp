// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrDeviceBaseSimple.h"

#include "RHIStaticStates.h"


bool UvrDeviceBaseSimple::Present(int32& InOutSyncInterval)
{
	// Wait for swap sync
	WaitForBufferSwapSync(InOutSyncInterval);

	return true;
}

void UvrDeviceBaseSimple::RenderTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FTexture2DRHIParamRef BackBuffer, FTexture2DRHIParamRef SrcTexture) const
{
	check(IsInRenderingThread());

	SetRenderTarget(RHICmdList, BackBuffer, FTextureRHIRef());
	const uint32 ViewportWidth = BackBuffer->GetSizeX();
	const uint32 ViewportHeight = BackBuffer->GetSizeY();
	RHICmdList.SetViewport(0, 0, 0, ViewportWidth, ViewportHeight, 1.0f);
	RHICmdList.SetBlendState(TStaticBlendState<>::GetRHI());
	RHICmdList.SetRasterizerState(TStaticRasterizerState<>::GetRHI());
	RHICmdList.SetDepthStencilState(TStaticDepthStencilState<false, CF_Always>::GetRHI());
	RHICmdList.ClearColorTexture(BackBuffer, FLinearColor::Black, FIntRect());
}
