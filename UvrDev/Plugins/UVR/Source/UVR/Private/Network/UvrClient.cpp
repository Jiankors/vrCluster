// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrClient.h"


UvrClient::UvrClient(const FString& name) :
	UvrSocketOps(CreateSocket(name)),
	m_name(name)
{
}

UvrClient::~UvrClient()
{
	Disconnect();
}

bool UvrClient::Connect(const FString& addr, const int32 port, const int32 triesAmount, const float delay)
{
	FScopeLock lock(&GetSyncObj());

	// Generate IPv4 address
	FIPv4Address ipAddr;
	if (!FIPv4Address::Parse(addr, ipAddr))
	{
		UE_LOG(LogUvrNetwork, Error, TEXT("%s couldn't parse the address [%s:%d]"), *m_name, *addr, port);
		return false;
	}

	// Generate internet address
	TSharedRef<FInternetAddr> internetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	internetAddr->SetIp(ipAddr.Value);
	internetAddr->SetPort(port);

	// Start connection loop
	int32 tryIdx = 0;
	while(GetSocket()->Connect(*internetAddr) == false)
	{
		UE_LOG(LogUvrNetwork, Log, TEXT("%s couldn't connect to the server %s [%d]"), *m_name, *(internetAddr->ToString(true)), tryIdx++);
		if (triesAmount > 0 && tryIdx >= triesAmount)
		{
			UE_LOG(LogUvrNetwork, Error, TEXT("%s connection attempts limit reached"), *m_name);
			break;
		}

		// Sleep some time before next try
		FPlatformProcess::Sleep(delay);
	}

	return IsOpen();
}

void UvrClient::Disconnect()
{
	FScopeLock lock(&GetSyncObj());

	UE_LOG(LogUvrNetwork, Log, TEXT("%s disconnecting..."), *m_name);

	if (IsOpen())
		GetSocket()->Close();
}

FSocket* UvrClient::CreateSocket(const FString& name, const int32 bufSize)
{
	FSocket* pSock = FTcpSocketBuilder(*name).AsBlocking().WithReceiveBufferSize(bufSize).WithSendBufferSize(bufSize);
	check(pSock);
	return pSock;
}

bool UvrClient::SendMsg(const UvrMessage::Ptr& msg)
{
	const bool result = UvrSocketOps::SendMsg(msg);
	if (result == false)
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, FString("Something wrong with connection (send). The cluster is inconsistent. Exit required."));

	return result;
}

UvrMessage::Ptr UvrClient::RecvMsg()
{
	UvrMessage::Ptr response = UvrSocketOps::RecvMsg();
	if(!response.IsValid())
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, FString("Something wrong with connection (recv). The cluster is inconsistent. Exit required."));

	return response;
}

UvrMessage::Ptr UvrClient::SendRecvMsg(const UvrMessage::Ptr& msg)
{
	UvrMessage::Ptr response;

	{
		FScopeLock lock(&GetSyncObj());
		SendMsg(msg);
		response = RecvMsg();
	}

	if (!response.IsValid())
		UE_LOG(LogUvrNetworkMsg, Warning, TEXT("No response"));

	return response;
}

