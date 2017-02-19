// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Networking.h"
#include "UvrMessage.h"


class UvrSocketOps
{
public:
	UvrSocketOps(FSocket* pSock);
	virtual ~UvrSocketOps();

public:
	virtual bool SendMsg(const UvrMessage::Ptr& msg);
	virtual UvrMessage::Ptr RecvMsg();

	inline FSocket* GetSocket() const
	{ return m_pSocket; }

	inline bool IsOpen() const
	{ return (m_pSocket && (m_pSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)); }

	// Provides with net unit name
	virtual FString GetName() const = 0;

protected:
	// Provides with a synchronization object for underlying operations (message send/recv)
	inline FCriticalSection& GetSyncObj() const
	{ return m_cs; }

private:
	bool RecvChunk(int32 chunkSize, TArray<uint8>& chunkBuffer, const FString& chunkName = FString("DataChunk"));

private:
	struct UvrMessageHeader
	{
		int16 length;

		FString ToString()
		{ return FString::Printf(TEXT("<length=%d>"), length); }

	};

private:
	// Socket
	FSocket* m_pSocket = nullptr;
	// Data buffer for incoming and outgoing messages
	TArray<uint8> m_buffer;
	// Access sync object
	mutable FCriticalSection m_cs;
};

