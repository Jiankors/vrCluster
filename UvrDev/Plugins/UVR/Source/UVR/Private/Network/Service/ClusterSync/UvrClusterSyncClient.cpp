// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrClusterSyncClient.h"

#include "Network/UvrMessage.h"
#include "UvrClusterSyncMsg.h"


UvrClusterSyncClient::UvrClusterSyncClient() :
	UvrClient(FString("CLN_CS"))
{
}

UvrClusterSyncClient::UvrClusterSyncClient(const FString& name) :
	UvrClient(name)
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrClusterSyncProtocol
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrClusterSyncClient::WaitForGameStart()
{
	static TSharedPtr<UvrMessage> request(new UvrMessage(UvrClusterSyncMsg::WaitForGameStart::name, UvrClusterSyncMsg::TypeRequest, UvrClusterSyncMsg::ProtocolName));
	TSharedPtr<UvrMessage> response;

	{
		FScopeLock lock(&GetSyncObj());
		SendMsg(request);
		response = RecvMsg();
	}

	if (!response.IsValid())
	{
		UE_LOG(LogUvrNetworkMsg, Warning, TEXT("No response"));
		return;
	}
}

void UvrClusterSyncClient::WaitForFrameStart()
{
	static const TSharedPtr<UvrMessage> request(new UvrMessage(UvrClusterSyncMsg::WaitForFrameStart::name, UvrClusterSyncMsg::TypeRequest, UvrClusterSyncMsg::ProtocolName));
	TSharedPtr<UvrMessage> response = SendRecvMsg(request);
}

void UvrClusterSyncClient::WaitForFrameEnd()
{
	static const TSharedPtr<UvrMessage> request(new UvrMessage(UvrClusterSyncMsg::WaitForFrameEnd::name, UvrClusterSyncMsg::TypeRequest, UvrClusterSyncMsg::ProtocolName));
	TSharedPtr<UvrMessage> response = SendRecvMsg(request);
}

void UvrClusterSyncClient::WaitForTickEnd()
{
	static const TSharedPtr<UvrMessage> request(new UvrMessage(UvrClusterSyncMsg::WaitForTickEnd::name, UvrClusterSyncMsg::TypeRequest, UvrClusterSyncMsg::ProtocolName));
	TSharedPtr<UvrMessage> response = SendRecvMsg(request);
}

void UvrClusterSyncClient::GetDeltaTime(float& deltaTime)
{
	static const TSharedPtr<UvrMessage> request(new UvrMessage(UvrClusterSyncMsg::GetDeltaTime::name, UvrClusterSyncMsg::TypeRequest, UvrClusterSyncMsg::ProtocolName));
	TSharedPtr<UvrMessage> response = SendRecvMsg(request);

	if (!response.IsValid())
		return;

	// Extract sync data from response message
	if (response->GetArg(UvrClusterSyncMsg::GetDeltaTime::argDeltaTime, deltaTime) == false)
		UE_LOG(LogUvrNetworkMsg, Error, TEXT("Coulnd't extract an argument: %s"), UvrClusterSyncMsg::GetDeltaTime::argDeltaTime);
}

void UvrClusterSyncClient::GetSyncData(UvrMessage::DataType& data)
{
	static const TSharedPtr<UvrMessage> request(new UvrMessage(UvrClusterSyncMsg::GetSyncData::name, UvrClusterSyncMsg::TypeRequest, UvrClusterSyncMsg::ProtocolName));
	TSharedPtr<UvrMessage> response = SendRecvMsg(request);

	if (!response.IsValid())
		return;

	// Extract sync data from response message
	data = response->GetArgs();
}

void UvrClusterSyncClient::GetInputData(UvrMessage::DataType& data)
{
	static const TSharedPtr<UvrMessage> request(new UvrMessage(UvrClusterSyncMsg::GetInputData::name, UvrClusterSyncMsg::TypeRequest, UvrClusterSyncMsg::ProtocolName));
	TSharedPtr<UvrMessage> response = SendRecvMsg(request);

	if (!response.IsValid())
		return;

	// Extract sync data from response message
	data = response->GetArgs();
}

