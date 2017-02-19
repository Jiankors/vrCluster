// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrHUD.h"

#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

#include "UvrPlugin.h"


float AUvrHUD::ms_Threshold = 0.f;
float AUvrHUD::ms_Delay = 0.f;
float AUvrHUD::ms_Render = 0.f;
int AUvrHUD::ms_policy = 0;

AUvrHUD::AUvrHUD()
{
}


void AUvrHUD::DrawHUD()
{
	Super::DrawHUD();

#if 0
	{
		// find center of the Canvas
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		if(GEngine)
		{
			const FString strNodeId = UvrPlugin::get().ClusterMgr->GetNodeId();
			const FText txtNodeId = FText::FromString(strNodeId);
			FCanvasTextItem textItem(FVector2D(Center.X, Center.Y), txtNodeId, GEngine->GetLargeFont(), FLinearColor(0.85f, 1.0f, 0.85f, 0.3f));
			textItem.Scale.Set(3.0f, 3.0f);
			Canvas->DrawItem(textItem);
		}
	}
#endif

#if 0
	const FVector2D pos(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	if (GEngine)
	{
		FString str;

		if (ms_policy == 1 || ms_policy == 2 || ms_policy == 3)
		{
			if (ms_policy == 1)
			{
				str = FString::Printf(TEXT("Policy: %d\nDelay: %.3f ms"), ms_policy, ms_Delay * 1000.f);
			}
			else if (ms_policy == 2)
			{
				str = FString::Printf(TEXT("Policy: %d\nDelay: %.3f ms"), ms_policy, ms_Delay * 1000.f);
			}
			else if (ms_policy == 3)
			{
				str = FString::Printf(TEXT("Policy: %d\nDelay: %.3f ms"), ms_policy, ms_Delay * 1000.f);
			}

			const FText txt = FText::FromString(str);

			FCanvasTextItem it(FVector2D(pos.X, pos.Y), txt, GEngine->GetLargeFont(), FLinearColor(1.f, 1.0f, 1.f, 1.f));
			it.Scale.Set(1.25f, 1.25f);
			Canvas->DrawItem(it);
		}
	}
#endif
}

