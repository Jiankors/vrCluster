// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include <condition_variable>
#include <mutex>


class UvrBarrier :
	private UvrNoncopyable,
	private UvrNonmoveable
{
public:
	explicit UvrBarrier(uint32 threadsAmount, uint32 timeout);
	explicit UvrBarrier(uint32 threadsAmount, const FString& name, uint32 timeout);
	~UvrBarrier();

public:
	enum class WaitResult
	{
		Ok,
		NotActive,
		Timeout
	};

public:
	// Wait until all threads arrive
	WaitResult Wait(double* pThreadWaitTime = nullptr, double* pBarrierWaitTime = nullptr);
	// Enable barrier
	void Activate();
	// Disable barrier (no blocking operation performed anymore)
	void Deactivate();

private:
	// Barrier name for logging
	const FString m_name;

	// Barrier state
	bool m_bEnabled = true;

	// Amount of threads to wait at the barrier
	const uint32 m_amount;
	// Frame end waiting threads amount
	uint32 m_left;
	// Iteration counter (kind of barrier sync transaction)
	size_t m_iteration;

	std::condition_variable m_cv;
	std::mutex m_mutex;

	uint32 m_timeout = 0;

	double m_waitTimeStart = 0;
	double m_waitTimeFinish = 0;
	double m_waitTimeOverall = 0;
};

