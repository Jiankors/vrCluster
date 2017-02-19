// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Networking.h"
#include "UvrMessage.h"
#include "UvrSocketOps.h"


class UvrClient : protected UvrSocketOps
{
public:
	UvrClient(const FString& name);
	virtual ~UvrClient();

public:
	// Connects to a server
	bool Connect(const FString& addr, const int32 port, const int32 triesAmount = UvrConstants::net::ClientConnectTriesAmount, const float delay = UvrConstants::net::ClientConnectRetryDelay);
	// Terminates current connection
	void Disconnect();

	virtual bool SendMsg(const UvrMessage::Ptr& msg) override final;
	virtual UvrMessage::Ptr RecvMsg() override final;

	UvrMessage::Ptr SendRecvMsg(const UvrMessage::Ptr& msg);

	virtual FString GetName() const override final
	{ return m_name; }

	inline bool IsConnected() const
	{ return IsOpen(); }

protected:
	// Creates client socket
	FSocket* CreateSocket(const FString& name, const int32 bufSize = UvrConstants::net::SocketBufferSize);

private:
	// Client name
	const FString m_name;
};

