// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrService.h"

#include "UvrPlugin.h"


UvrService::UvrService(const FString& name, const FString& addr, const int32 port) :
	UvrServer(name, addr, port)
{
}

bool UvrService::IsClusterIP(const FIPv4Endpoint& ep)
{
	TArray<SUvrConfigClusterNode> nodes = UvrPlugin::get().ConfigMgr->GetClusterNodes();
	const FString addr = ep.Address.ToString();
	
	return nullptr != nodes.FindByPredicate([addr](const SUvrConfigClusterNode& node)
	{
		return addr == node.Addr;
	});
}

bool UvrService::IsConnectionAllowed(FSocket* pSock, const FIPv4Endpoint& ep)
{
	// By default any UVR service must be within a cluster
	return UvrService::IsClusterIP(ep);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrSessionListener
//////////////////////////////////////////////////////////////////////////////////////////////
void UvrService::NotifySessionOpen(UvrSession* pSession)
{
	UvrServer::NotifySessionOpen(pSession);
}

void UvrService::NotifySessionClose(UvrSession* pSession)
{
	UvrAppExit::ExitApplication(UvrAppExit::ExitType::NormalSoft, GetName() + FString(" - Connection interrupted. Application exit requested."));
	UvrServer::NotifySessionClose(pSession);
}

