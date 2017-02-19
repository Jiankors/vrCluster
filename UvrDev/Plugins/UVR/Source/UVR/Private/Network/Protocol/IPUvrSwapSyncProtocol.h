// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

class IPUvrSwapSyncProtocol
{
public:
	// Swap sync barrier
	virtual void WaitForSwapSync(double* pThreadWaitTime, double* pBarrierWaitTime) = 0;
	// 
};

