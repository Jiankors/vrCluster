// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrNodeCtrlBase.h"


UvrNodeCtrlBase::UvrNodeCtrlBase(const FString& ctrlName, const FString& nodeName) :
	m_ctrlName(ctrlName),
	m_nodeName(nodeName)
{
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrNodeController
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrNodeCtrlBase::Initialize()
{
	if (!InitializeStereo())
	{
		UE_LOG(LogUvrCluster, Error, TEXT("Stereo initialization failed"));
		return false;
	}

	if (!InitializeServers())
	{
		UE_LOG(LogUvrCluster, Error, TEXT("Servers initialization failed"));
		return false;
	}

	if (!InitializeClients())
	{
		UE_LOG(LogUvrCluster, Error, TEXT("Clients initialization failed"));
		return false;
	}

	if (!StartServers())
	{
		UE_LOG(LogUvrCluster, Error, TEXT("An error occurred during servers start"));
		return false;
	}

	if (!StartClients())
	{
		UE_LOG(LogUvrCluster, Error, TEXT("An error occurred during clients start"));
		return false;
	}

	return true;
}

void UvrNodeCtrlBase::Release()
{
	StopServers();
	StopClients();
}
