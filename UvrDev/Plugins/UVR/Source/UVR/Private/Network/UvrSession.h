// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Networking.h"
#include "UvrSocketOps.h"

#include "IUvrSessionListener.h"

class UvrSession :
	public    FRunnable,
	protected UvrSocketOps
{
public:
	UvrSession(FSocket* pSock, IUvrSessionListener* pListener, const FString& name = FString("UvrSession"));
	~UvrSession();

	virtual FString GetName() const override final
	{ return m_name; }

private:
	virtual uint32 Run() override;
	virtual void   Stop() override;

private:
	const FString        m_name;
	IUvrSessionListener* m_pListener = nullptr;
	FRunnableThread*     m_pThread = nullptr;
};

