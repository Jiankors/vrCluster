// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Networking.h"


class UvrTcpListener
	: public FRunnable
{
public:
	DECLARE_DELEGATE_RetVal_TwoParams(bool, TOnConnectionAcceptedDelegate, FSocket*, const FIPv4Endpoint&)

public:
	UvrTcpListener(const FString& name);
	~UvrTcpListener();

public:

	bool StartListening(const FString& addr, const int32 port);
	bool StartListening(const FIPv4Endpoint& ep);
	void StopListening();

	bool IsActive() const;

	inline TOnConnectionAcceptedDelegate& OnConnectionAccepted()
	{ return m_OnConnectionAccepted; }

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// FRunnable
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

private:
	// Creates server socket
	FSocket* CreateSocket(const FString& name, const FString& addr, const int32 port, const int32 bufSize = UvrConstants::net::SocketBufferSize);
	
private:
	// Socket name
	FString m_name;
	// Listening socket
	FSocket* m_pSock = nullptr;
	// Listening endpoint
	FIPv4Endpoint m_Endpoint;
	// Holds the thread object
	FRunnableThread* m_pThread;
	// Sync access
	FCriticalSection m_cs;
	// Listening state
	bool m_bIsListening = false;

private:
	// Holds a delegate to be invoked when an incoming connection has been accepted.
	TOnConnectionAcceptedDelegate m_OnConnectionAccepted;
};
