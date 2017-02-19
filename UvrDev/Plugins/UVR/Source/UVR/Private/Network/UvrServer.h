// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Networking.h"
#include "UvrSession.h"

#include "IUvrSessionListener.h"
#include "UvrTcpListener.h"

class UvrServer : public IUvrSessionListener
{
public:
	UvrServer(const FString& name, const FString& addr, const int32 port);
	virtual ~UvrServer();

public:
	// Start server
	virtual bool Start();
	// Stop server
	virtual void Shutdown();

	// Returns current server state
	bool IsRunning();

	// Server name
	inline const FString& GetName() const
	{ return m_name; }

	// Server addr
	inline const FString& GetAddr() const
	{ return m_addr; }

	// Server port
	inline const int32& GetPort() const
	{ return m_port; }

protected:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// IUvrSessionListener
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void NotifySessionOpen(UvrSession* pSession) override;
	virtual void NotifySessionClose(UvrSession* pSession) override;
	virtual UvrMessage::Ptr ProcessMessage(UvrMessage::Ptr msg) = 0;

protected:
	// Ask concrete server implementation if connection is allowed
	virtual bool IsConnectionAllowed(FSocket* pSock, const FIPv4Endpoint& ep)
	{ return true; }

private:
	// Handles incoming connections
	bool ConnectionHandler(FSocket* pSock, const FIPv4Endpoint& ep);

private:
	// Server data
	const FString m_name;
	const FString m_addr;
	const int32   m_port;

	// Simple server state
	bool m_isRunning = false;
	// Socket listener
	UvrTcpListener m_listener;
	// Sync access
	FCriticalSection m_cs;

	// Active sessions
	TArray<TUniquePtr<UvrSession>> m_sessions;
};

