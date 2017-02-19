// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrBarrier.h"

#include <chrono>


UvrBarrier::UvrBarrier(uint32 threadsAmount, const FString& name, uint32 timeout) :
	m_name(name),
	m_amount(threadsAmount),
	m_left(threadsAmount),
	m_iteration(0),
	m_timeout(timeout)
{
	UE_LOG(LogUvrNetwork, Log, TEXT("Initialized barrier %s with timeout %u for threads count: %u"), *m_name, m_timeout, m_amount);
}

UvrBarrier::UvrBarrier(uint32 threadsAmount, uint32 timeout) :
	UvrBarrier(threadsAmount, FString("noname_barrier"), timeout)
{
}


UvrBarrier::~UvrBarrier()
{
	// Free currently blocked threads
	Deactivate();
}

UvrBarrier::WaitResult UvrBarrier::Wait(double* pThreadWaitTime /*= nullptr*/, double* pBarrierWaitTime /*= nullptr*/)
{
	if (m_bEnabled == false)
	{
		UE_LOG(LogUvrNetwork, Verbose, TEXT("%s barrier is not active"), *m_name);
		return WaitResult::NotActive;
	}

	const double threadWaitTimeStart = FPlatformTime::Seconds();

	{
		std::unique_lock<std::mutex> lock{ m_mutex };

		auto curIter = m_iteration;

		if (m_left == m_amount)
		{
			m_waitTimeStart = FPlatformTime::Seconds();
			UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("%s barrier start time: %lf"), *m_name, m_waitTimeStart);
		}

		// Check if all threads are in front of the barrier
		if (--m_left == 0)
		{
			UE_LOG(LogUvrNetwork, Verbose, TEXT("%s barrier trigger!"), *m_name);
			++m_iteration;
			m_left = m_amount;

			m_waitTimeFinish = FPlatformTime::Seconds();
			UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("%s barrier finish time: %lf"), *m_name, m_waitTimeFinish);

			m_waitTimeOverall = m_waitTimeFinish - m_waitTimeStart;
			UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("%s barrier overall wait time: %lf"), *m_name, m_waitTimeOverall);

			// This is the last node. Unblock the barrier.
			m_cv.notify_all();
		}
		else
		{
			UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("%s barrier waiting, %u threads left"), *m_name, m_left);
			// Not all of threads have came here. Wait.
			if (!m_cv.wait_for(lock, std::chrono::milliseconds(m_timeout), [this, curIter] { return curIter != m_iteration || m_bEnabled == false; }))
			{
				//@todo: no timeout result if barrier has been disabled
				UE_LOG(LogUvrNetwork, Warning, TEXT("%s barrier waiting timeout"), *m_name);
				return WaitResult::Timeout;
			}
		}
	}

	const double threadWaitTimeFinish = FPlatformTime::Seconds();

	if (pBarrierWaitTime)
		*pBarrierWaitTime = m_waitTimeOverall;

	if (pThreadWaitTime)
		*pThreadWaitTime = threadWaitTimeFinish - threadWaitTimeStart;

	// Go ahead
	return WaitResult::Ok;
}

void UvrBarrier::Activate()
{
	std::unique_lock<std::mutex> lock{ m_mutex };

	m_iteration = 0;
	m_left = m_amount;
	m_bEnabled = true;
	m_cv.notify_all();
}

void UvrBarrier::Deactivate()
{
	std::unique_lock<std::mutex> lock{ m_mutex };

	m_bEnabled = false;
	m_cv.notify_all();
}

