// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Network/UvrServer.h"

class UvrService : public UvrServer
{
public:
	UvrService(const FString& name, const FString& addr, const int32 port);

public:
	static bool IsClusterIP(const FIPv4Endpoint& ep);

protected:
	virtual bool IsConnectionAllowed(FSocket* pSock, const FIPv4Endpoint& ep) override;

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrSessionListener
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void NotifySessionOpen(UvrSession* pSession) override;
	virtual void NotifySessionClose(UvrSession* pSession) override;
};

