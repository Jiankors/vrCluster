// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UVRBlueprintLibCluster.h"

#include "IUvrPlugin.h"
#include "IUvrClusterManager.h"


UUVRBlueprintLibCluster::UUVRBlueprintLibCluster(class FObjectInitializer const & ObjectInitializer) :
	Super(ObjectInitializer)
{

}

bool UUVRBlueprintLibCluster::UvrIsMaster()
{
	IUvrClusterManager* const pMgr = IUvrPlugin::Get().GetClusterMgr();
	if (pMgr)
		return pMgr->IsMaster();

	return false;
}

bool UUVRBlueprintLibCluster::UvrIsSlave()
{
	return !UUVRBlueprintLibCluster::UvrIsMaster();
}

bool UUVRBlueprintLibCluster::UvrIsCluster()
{
	IUvrClusterManager* const pMgr = IUvrPlugin::Get().GetClusterMgr();
	if (pMgr)
		return pMgr->IsCluster();

	return false;
}

bool UUVRBlueprintLibCluster::UvrIsStandalone()
{
	return !UUVRBlueprintLibCluster::UvrIsCluster();
}

FString UUVRBlueprintLibCluster::UvrGetNodeId()
{
	IUvrClusterManager* const pMgr = IUvrPlugin::Get().GetClusterMgr();
	if (pMgr)
		return pMgr->GetNodeId();

	return FString();
}

int32 UUVRBlueprintLibCluster::UvrGetNodesAmount()
{
	IUvrClusterManager* const pMgr = IUvrPlugin::Get().GetClusterMgr();
	if (pMgr)
		return pMgr->GetNodesAmount();

	return 0;
}
