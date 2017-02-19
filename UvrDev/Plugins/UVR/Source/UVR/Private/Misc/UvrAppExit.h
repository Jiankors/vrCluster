// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

class UvrAppExit
{
public:
	enum class ExitType
	{
		// Kills current process. No resource cleaning performed.
		KillImmediately,
		// UE4 based soft exit (game thread). Full resource cleaning.
		NormalSoft,
		// UE4 game termination. Error window and dump file should appear after exit.
		NormalForce
	};

public:
	static void ExitApplication(ExitType exitType, const FString& strMsg);

private:
	static auto ExitTypeToStr(ExitType type);

private:
	static FCriticalSection ms_lock;
};
