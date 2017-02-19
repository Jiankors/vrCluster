// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrClusterSyncService.h"

#include "UvrClusterSyncMsg.h"
#include "UvrPlugin.h"



UvrClusterSyncService::UvrClusterSyncService(const FString& addr, const int32 port) :
	UvrService(FString("SRV_CS"), addr, port),
	m_barrierGameStart  (UvrPlugin::get().ClusterMgr->GetNodesAmount(), FString("GameStart_barrier"),  UvrConstants::net::BarrierGameStartWaitTimeout),
	m_barrierFrameStart (UvrPlugin::get().ClusterMgr->GetNodesAmount(), FString("FrameStart_barrier"), UvrConstants::net::BarrierWaitTimeout),
	m_barrierFrameEnd   (UvrPlugin::get().ClusterMgr->GetNodesAmount(), FString("FrameEnd_barrier"),   UvrConstants::net::BarrierWaitTimeout),
	m_barrierTickEnd    (UvrPlugin::get().ClusterMgr->GetNodesAmount(), FString("TickEnd_barrier"),    UvrConstants::net::BarrierWaitTimeout)
{
}

UvrClusterSyncService::~UvrClusterSyncService()
{
	Shutdown();
}


bool UvrClusterSyncService::Start()
{
	m_barrierGameStart.Activate();
	m_barrierFrameStart.Activate();
	m_barrierFrameEnd.Activate();
	m_barrierTickEnd.Activate();

	return UvrServer::Start();
}

void UvrClusterSyncService::Shutdown()
{
	m_barrierGameStart.Deactivate();
	m_barrierFrameStart.Deactivate();
	m_barrierFrameEnd.Deactivate();
	m_barrierTickEnd.Deactivate();

	return UvrServer::Shutdown();
}

//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrSessionListener
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrClusterSyncService::NotifySessionOpen(UvrSession* pSession)
{
	UvrService::NotifySessionOpen(pSession);
}

void UvrClusterSyncService::NotifySessionClose(UvrSession* pSession)
{
	// Unblock waiting threads to allow current Tick() finish
	m_barrierGameStart.Deactivate();
	m_barrierFrameStart.Deactivate();
	m_barrierFrameEnd.Deactivate();
	m_barrierTickEnd.Deactivate();

	UvrService::NotifySessionClose(pSession);
}

UvrMessage::Ptr UvrClusterSyncService::ProcessMessage(UvrMessage::Ptr msg)
{
	// Check the pointer
	if (msg.IsValid() == false)
	{
		UE_LOG(LogUvrNetworkMsg, Error, TEXT("%s - Couldn't process the message"), *GetName());
		return nullptr;
	}

	UE_LOG(LogUvrNetwork, Verbose, TEXT("%s - Processing message %s"), *GetName(), *msg->ToString());

	// Check protocol and type
	if (msg->GetProtocol() != UvrClusterSyncMsg::ProtocolName || msg->GetType() != UvrClusterSyncMsg::TypeRequest)
	{
		UE_LOG(LogUvrNetworkMsg, Error, TEXT("%s - Unsupported message type: %s"), *GetName(), *msg->ToString());
		return nullptr;
	}

	// Initialize response message
	UvrMessage::Ptr response = UvrMessage::Ptr(new UvrMessage(msg->GetName(), UvrClusterSyncMsg::TypeResponse, msg->GetProtocol()));

	// Dispatch the message
	const FString msgName = msg->GetName();
	if (msgName == UvrClusterSyncMsg::WaitForGameStart::name)
	{
		WaitForGameStart();
		return response;
	}
	else if (msgName == UvrClusterSyncMsg::WaitForFrameStart::name)
	{
		WaitForFrameStart();
		return response;
	}
	else if (msgName == UvrClusterSyncMsg::WaitForFrameEnd::name)
	{
		WaitForFrameEnd();
		return response;
	}
	else if (msgName == UvrClusterSyncMsg::WaitForTickEnd::name)
	{
		WaitForTickEnd();
		return response;
	}
	else if (msgName == UvrClusterSyncMsg::GetDeltaTime::name)
	{
		float deltaTime = 0.0f;
		GetDeltaTime(deltaTime);
		response->SetArg(UvrClusterSyncMsg::GetDeltaTime::argDeltaTime, deltaTime);
		return response;
	}
	else if (msgName == UvrClusterSyncMsg::GetSyncData::name)
	{
		UvrMessage::DataType data;
		GetSyncData(data);

		response->SetArgs(data);
		return response;
	}
	else if (msgName == UvrClusterSyncMsg::GetInputData::name)
	{
		UvrMessage::DataType data;
		GetInputData(data);

		response->SetArgs(data);
		return response;
	}

	// Being here means that we have no appropriate dispatch logic for this message
	UE_LOG(LogUvrNetworkMsg, Warning, TEXT("%s - A dispatcher for this message hasn't been implemented yet <%s>"), *GetName(), *msg->ToString());
	return nullptr;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrClusterSyncProtocol
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrClusterSyncService::WaitForGameStart()
{
	if (m_barrierGameStart.Wait() != UvrBarrier::WaitResult::Ok)
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, FString("Error on game start barrier. Exit required."));
}

void UvrClusterSyncService::WaitForFrameStart()
{
	if (m_barrierFrameStart.Wait() != UvrBarrier::WaitResult::Ok)
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, FString("Error on frame start barrier. Exit required."));
}

void UvrClusterSyncService::WaitForFrameEnd()
{
	if (m_barrierFrameEnd.Wait() != UvrBarrier::WaitResult::Ok)
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, FString("Error on frame end barrier. Exit required."));
}

void UvrClusterSyncService::WaitForTickEnd()
{
	if (m_barrierTickEnd.Wait() != UvrBarrier::WaitResult::Ok)
		UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, FString("Error on tick end barrier. Exit required."));
}

void UvrClusterSyncService::GetDeltaTime(float& deltaTime)
{
	deltaTime = UvrPlugin::get().ClusterMgr->GetDeltaTime();
}

void UvrClusterSyncService::GetSyncData(UvrMessage::DataType& data)
{
	UvrPlugin::get().ClusterMgr->ExportSyncData(data);
}

void UvrClusterSyncService::GetInputData(UvrMessage::DataType& data)
{
	UvrPlugin::get().InputMgr->ExportInputData(data);
}
