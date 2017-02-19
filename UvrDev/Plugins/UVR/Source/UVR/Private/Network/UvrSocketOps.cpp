// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrSocketOps.h"


UvrSocketOps::UvrSocketOps(FSocket* pSock) :
	m_pSocket(pSock)
{
	m_buffer.Reserve(UvrConstants::net::MessageBufferSize);
}


UvrSocketOps::~UvrSocketOps()
{
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(m_pSocket);
}

UvrMessage::Ptr UvrSocketOps::RecvMsg()
{
	FScopeLock lock(&GetSyncObj());

	if (!IsOpen())
	{
		UE_LOG(LogUvrNetwork, Error, TEXT("%s - not connected"), *GetName());
		return nullptr;
	}

	// Read message header
	if (!RecvChunk(sizeof(UvrMessageHeader), m_buffer, FString("header-chunk")))
		return nullptr;

	// Ok. Now we can extract header data
	UvrMessageHeader msgHeader;
	FMemory::Memcpy(&msgHeader, m_buffer.GetData(), sizeof(UvrMessageHeader));

	UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("%s - message header received: %s"), *GetName(), *msgHeader.ToString());
	check(msgHeader.length > 0);

	// Read message body
	if (!RecvChunk(msgHeader.length, m_buffer, FString("body-chunk")))
		return nullptr;

	UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("%s - message body received"), *GetName());

	UvrMessage::Ptr msg(new UvrMessage());
	FMemoryReader ar = FMemoryReader(m_buffer, false);

	// Deserialize message from buffer
	if (!msg->Deserialize(ar))
	{
		UE_LOG(LogUvrNetworkMsg, Error, TEXT("%s couldn't deserialize a message"), *GetName());
		return nullptr;
	}

	// Succeeded
	UE_LOG(LogUvrNetworkMsg, Verbose, TEXT("%s - received a message: %s"), *GetName(), *msg->ToString());
	return msg;
}

bool UvrSocketOps::RecvChunk(int32 chunkSize, TArray<uint8>& chunkBuffer, const FString& chunkName)
{
	int32 bytesReadAll = 0;
	int32 bytesReadNow = 0;
	int32 bytesReadLeft = 0;
	const int32 bytesAll = chunkSize;
	chunkBuffer.Empty(UvrConstants::net::MessageBufferSize);

	// Receive message header at first
	while (bytesReadAll < bytesAll)
	{
		// Read data
		bytesReadLeft = bytesAll - bytesReadAll;
		if (!m_pSocket->Recv(chunkBuffer.GetData(), bytesReadLeft, bytesReadNow))
		{
			UE_LOG(LogUvrNetwork, Warning, TEXT("%s - %s recv failed - socket error. Cluster integrity disturbed."), *GetName(), *chunkName);
			return false;
		}

		// Check amount of read data
		if (bytesReadNow <= 0 || bytesReadNow > bytesReadLeft)
		{
			UE_LOG(LogUvrNetwork, Error, TEXT("%s - %s recv failed - read wrong amount of bytes: %d"), *GetName(), *chunkName, bytesReadNow);
			return false;
		}

		bytesReadAll += bytesReadNow;
		UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("%s - %s received %d bytes, left %d bytes"), *GetName(), *chunkName, bytesReadNow, bytesAll - bytesReadAll);

		// Convergence check
		if (bytesReadAll > bytesAll)
		{
			UE_LOG(LogUvrNetwork, Error, TEXT("%s - %s convergence fail: overall received %d of %d"), *GetName(), *chunkName, bytesReadAll, bytesAll);
			return false;
		}
	}

	// Update array length (amount of bytes as array elements)
	chunkBuffer.SetNumUninitialized(bytesReadAll);

	// Operation succeeded
	return true;
}

bool UvrSocketOps::SendMsg(const UvrMessage::Ptr& msg)
{
	FScopeLock lock(&GetSyncObj());

	UE_LOG(LogUvrNetwork, Verbose, TEXT("%s - sending message: %s"), *GetName(), *msg->ToString());

	if (!IsOpen())
	{
		UE_LOG(LogUvrNetwork, Error, TEXT("%s not connected"), *GetName());
		return false;
	}

	// Prepare output buffer
	m_buffer.Empty(UvrConstants::net::MessageBufferSize);
	m_buffer.AddZeroed(sizeof(UvrMessageHeader));
	FMemoryWriter memoryWriter(m_buffer);

	// Reserve space for message header
	memoryWriter.Seek(sizeof(UvrMessageHeader));

	// Serialize the message
	if (!msg->Serialize(memoryWriter))
	{
		UE_LOG(LogUvrNetworkMsg, Error, TEXT("%s couldn't serialize a message"), *GetName());
		return false;
	}

	// Check bounds
	const int32 msgLength = m_buffer.Num();
	if (msgLength > UvrConstants::net::SocketBufferSize)
	{
		UE_LOG(LogUvrNetworkMsg, Error, TEXT("Outgoing message length exceeds buffer limit: length=%d > limit=%d"), msgLength, UvrConstants::net::SocketBufferSize);
		return false;
	}

	// Initialize message header
	UvrMessageHeader msgHeader;
	msgHeader.length = static_cast<int16>(msgLength & 0x7FFF) - sizeof(UvrMessageHeader);
	UE_LOG(LogUvrNetworkMsg, Verbose, TEXT("Outgoing message body length %d"), msgHeader.length);

	// Fill packet header with message data length
	FMemory::Memcpy(m_buffer.GetData(), &msgHeader, sizeof(UvrMessageHeader));

	int32 bytesWriteAll  = 0;
	int32 bytesWriteNow  = 0;
	int32 bytesWriteLeft = 0;

	while (bytesWriteAll < msgLength)
	{
		bytesWriteLeft = msgLength - bytesWriteAll;

		// Send data
		if (!m_pSocket->Send(m_buffer.GetData() + bytesWriteAll, bytesWriteLeft, bytesWriteNow))
		{
			UE_LOG(LogUvrNetwork, Error, TEXT("%s - couldn't send a message (length=%d)"), *GetName(), msgLength);
			return false;
		}

		// Check amount of sent bytes
		if (bytesWriteNow <= 0 || bytesWriteNow > bytesWriteLeft)
		{
			UE_LOG(LogUvrNetwork, Error, TEXT("%s - sent wrong amount of bytes: %d of %d left"), *GetName(), bytesWriteNow, bytesWriteLeft);
			return false;
		}

		bytesWriteAll += bytesWriteNow;
		UE_LOG(LogUvrNetwork, VeryVerbose, TEXT("%s - sent %d bytes, left %d bytes"), *GetName(), bytesWriteNow, msgLength - bytesWriteAll);

		// Convergence check
		if (bytesWriteAll > msgLength)
		{
			UE_LOG(LogUvrNetwork, Error, TEXT("%s - convergence failed: overall sent %d of %d"), *GetName(), bytesWriteAll, msgLength);
			return false;
		}
	}

	UE_LOG(LogUvrNetwork, Verbose, TEXT("%s - message sent"), *GetName());

	return true;
}

