// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrSwapSyncService.h"

#include "UvrSwapSyncMsg.h"
#include "UvrPlugin.h"


UvrSwapSyncService::UvrSwapSyncService(const FString& addr, const int32 port) :
	UvrService(FString("SRV_SS"), addr, port),
	m_barrierSwap(UvrPlugin::get().ClusterMgr->GetNodesAmount(), FString("SwapSync_barrier"), UvrConstants::net::BarrierWaitTimeout)
{
}

UvrSwapSyncService::~UvrSwapSyncService()
{
	Shutdown();
}


bool UvrSwapSyncService::Start()
{
	m_barrierSwap.Activate();

	return UvrServer::Start();
}

void UvrSwapSyncService::Shutdown()
{
	m_barrierSwap.Deactivate();
	return UvrServer::Shutdown();
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrSessionListener
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrSwapSyncService::NotifySessionOpen(UvrSession* pSession)
{
	UvrService::NotifySessionOpen(pSession);
}

void UvrSwapSyncService::NotifySessionClose(UvrSession* pSession)
{
	// Unblock waiting threads to allow current Tick() finish
	m_barrierSwap.Deactivate();

	UvrService::NotifySessionClose(pSession);
}

UvrMessage::Ptr UvrSwapSyncService::ProcessMessage(UvrMessage::Ptr msg)
{
	// Check the pointer
	if (msg.IsValid() == false)
	{
		UE_LOG(LogUvrNetworkMsg, Error, TEXT("%s - Couldn't process the message"), *GetName());
		return nullptr;
	}

	UE_LOG(LogUvrNetwork, Verbose, TEXT("%s - Processing message %s"), *GetName(), *msg->ToString());

	// Check protocol and type
	if (msg->GetProtocol() != UvrSwapSyncMsg::ProtocolName || msg->GetType() != UvrSwapSyncMsg::TypeRequest)
	{
		UE_LOG(LogUvrNetworkMsg, Error, TEXT("%s - Unsupported message type: %s"), *GetName(), *msg->ToString());
		return nullptr;
	}

	// Initialize response message
	UvrMessage::Ptr response = UvrMessage::Ptr(new UvrMessage(msg->GetName(), UvrSwapSyncMsg::TypeResponse, msg->GetProtocol()));

	// Dispatch the message
	if (msg->GetName() == UvrSwapSyncMsg::WaitForSwapSync::name)
	{
		double tTime = 0.f;
		double bTime = 0.f;

		WaitForSwapSync(&tTime, &bTime);

		response->SetArg(FString(UvrSwapSyncMsg::WaitForSwapSync::argThreadTime),  tTime);
		response->SetArg(FString(UvrSwapSyncMsg::WaitForSwapSync::argBarrierTime), bTime);

		return response;
	}

	// Being here means that we have no appropriate dispatch logic for this message
	UE_LOG(LogUvrNetworkMsg, Warning, TEXT("%s - A dispatcher for this message hasn't been implemented yet <%s>"), *GetName(), *msg->ToString());
	return nullptr;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrSwapSyncProtocol
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrSwapSyncService::WaitForSwapSync(double* pThreadWaitTime, double* pBarrierWaitTime)
{
	if (m_barrierSwap.Wait(pThreadWaitTime, pBarrierWaitTime) != UvrBarrier::WaitResult::Ok)
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, FString("Error on swap barrier. Exit required."));
}
