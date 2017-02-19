// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrSwapSyncClient.h"

#include "Network/UvrMessage.h"
#include "UvrSwapSyncMsg.h"


UvrSwapSyncClient::UvrSwapSyncClient() :
	UvrClient(FString("CLN_SS"))
{
}

UvrSwapSyncClient::UvrSwapSyncClient(const FString& name) :
	UvrClient(name)
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrSwapSyncProtocol
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrSwapSyncClient::WaitForSwapSync(double* pThreadWaitTime, double* pBarrierWaitTime)
{
	static const TSharedPtr<UvrMessage> request(new UvrMessage(UvrSwapSyncMsg::WaitForSwapSync::name, UvrSwapSyncMsg::TypeRequest, UvrSwapSyncMsg::ProtocolName));
	TSharedPtr<UvrMessage> response = SendRecvMsg(request);

	if (response.IsValid())
	{
		if (pThreadWaitTime)
		{
			if (!response->GetArg(FString(UvrSwapSyncMsg::WaitForSwapSync::argThreadTime), *pThreadWaitTime))
				UE_LOG(LogUvrNetwork, Error, TEXT("Argument %s not available"), UvrSwapSyncMsg::WaitForSwapSync::argThreadTime);
		}

		if (pBarrierWaitTime)
		{
			if (!response->GetArg(FString(UvrSwapSyncMsg::WaitForSwapSync::argBarrierTime), *pBarrierWaitTime))
				UE_LOG(LogUvrNetwork, Error, TEXT("Argument %s not available"), UvrSwapSyncMsg::WaitForSwapSync::argBarrierTime);
		}
	}
}

