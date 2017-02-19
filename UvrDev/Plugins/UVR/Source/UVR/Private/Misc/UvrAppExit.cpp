// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrAppExit.h"
#include "UvrPlugin.h"

#if WITH_EDITOR
#include "UnrealEd.h"
#endif

FCriticalSection UvrAppExit::ms_lock;

auto UvrAppExit::ExitTypeToStr(ExitType type)
{
	switch (type)
	{
	case ExitType::KillImmediately:
		return TEXT("KILL");
	case ExitType::NormalSoft:
		return TEXT("UE4_soft");
	case ExitType::NormalForce:
		return TEXT("UE4_force");
	default:
		return TEXT("unknown");
	}
}

void UvrAppExit::ExitApplication(ExitType exitType, const FString& strMsg)
{
	if (GEngine && GEngine->IsEditor())
	{
#if WITH_EDITOR
		UE_LOG(LogUvrPlugin, Log, TEXT("PIE STOP: %s application quit requested: %s"), ExitTypeToStr(exitType), *strMsg);
		GUnrealEd->RequestEndPlayMap();
#endif
		return;
	}
	else
	{
		FScopeLock lock(&ms_lock);

		// We process only first call. Thus we won't have a lot of requests from different socket threads.
		// We also will know the first requester which may be useful in step-by-step problem solving.
		static bool bRequestedBefore = false;
		if (bRequestedBefore == false || exitType == ExitType::KillImmediately)
		{
			bRequestedBefore = true;
			UE_LOG(LogUvrPlugin, Log, TEXT("%s application quit requested: %s"), ExitTypeToStr(exitType), *strMsg);

			GLog->Flush();

#if 0
			if (IsInGameThread())
			{
				GLog->FlushThreadedLogs();
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
				TGuardValue<bool> GuardMainThreadBlockedOnRenderThread(GMainThreadBlockedOnRenderThread, true);
#endif
				SCOPE_CYCLE_COUNTER(STAT_PumpMessages);
				FPlatformMisc::PumpMessages(false);
			}
#endif

			switch (exitType)
			{
				case ExitType::KillImmediately:
				{
					FProcHandle hProc = FPlatformProcess::OpenProcess(FPlatformProcess::GetCurrentProcessId());
					FPlatformProcess::TerminateProc(hProc, true);
					break;
				}

				case ExitType::NormalSoft:
				{
//@todo: This is workaround for exit issue - crash on exit. Need to be checked on new UE versions.
// <ErrorMessage>Assertion failed: NumRemoved == 1 [File:D:\work\UE4.12.5.build\Engine\Source\Runtime\CoreUObject\Private\UObject\UObjectHash.cpp] [Line: 905] &nl;&nl;</ErrorMessage>
#if 1
					FProcHandle hProc = FPlatformProcess::OpenProcess(FPlatformProcess::GetCurrentProcessId());
					FPlatformProcess::TerminateProc(hProc, true);
#else
#if 1
					FPlatformMisc::RequestExit(false);
#else
					APlayerController* TargetPC = UGameplayStatics::GetPlayerController(UvrPlugin::get().GetWorld(), 0);
					if (TargetPC)
						TargetPC->ConsoleCommand("quit");
#endif
#endif
					break;
				}

				case ExitType::NormalForce:
				{
					FPlatformMisc::RequestExit(true);
					break;
				}

				default:
				{
					UE_LOG(LogUvrPlugin, Warning, TEXT("Unknown exit type requested"));
					break;
				}
			}
		}
	}
}
