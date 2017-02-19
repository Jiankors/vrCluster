// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UVRBlueprintLibGame.h"

#include "IUvrPlugin.h"
#include "Input/IUvrInputManager.h"


UUVRBlueprintLibGame::UUVRBlueprintLibGame(class FObjectInitializer const & ObjectInitializer) :
	Super(ObjectInitializer)
{

}


//////////////////////////////////////////////////////////////////////////
// Root
AUvrRoot* UUVRBlueprintLibGame::UvrGetRoot()
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetRoot();

	return nullptr;
}


//////////////////////////////////////////////////////////////////////////
// Screens
UUvrScreenComponent* UUVRBlueprintLibGame::UvrGetActiveScreen()
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetActiveScreen();

	return nullptr;
}

UUvrScreenComponent* UUVRBlueprintLibGame::UvrGetScreenById(const FString& id)
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetScreenById(id);

	return nullptr;
}

TArray<UUvrScreenComponent*> UUVRBlueprintLibGame::UvrGetAllScreens()
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetAllScreens();

	return TArray<UUvrScreenComponent*>();
}

int32 UUVRBlueprintLibGame::UvrGetScreensAmount()
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetScreensAmount();

	return 0;
}


//////////////////////////////////////////////////////////////////////////
// Cameras


//////////////////////////////////////////////////////////////////////////
// Nodes
UUvrSceneComponent* UUVRBlueprintLibGame::UvrGetNodeById(const FString& id)
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetNodeById(id);

	return nullptr;
}

TArray<UUvrSceneComponent*> UUVRBlueprintLibGame::UvrGetAllNodes()
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetAllNodes();

	return TArray<UUvrSceneComponent*>();
}


//////////////////////////////////////////////////////////////////////////
// Navigation
USceneComponent* UUVRBlueprintLibGame::UvrGetTranslationDirectionComponent()
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetTranslationDirectionComponent();

	return nullptr;
}

void UUVRBlueprintLibGame::UvrSetTranslationDirectionComponent(USceneComponent* const pComp)
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		pMgr->SetTranslationDirectionComponent(pComp);
}

void UUVRBlueprintLibGame::UvrSetTranslationDirectionComponentId(const FString& id)
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		pMgr->SetTranslationDirectionComponent(id);
}

USceneComponent* UUVRBlueprintLibGame::UvrGetRotateAroundComponent()
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		return pMgr->GetRotateAroundComponent();

	return nullptr;
}

void UUVRBlueprintLibGame::UvrSetRotateAroundComponent(USceneComponent* const pComp)
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		pMgr->SetRotateAroundComponent(pComp);
}

void UUVRBlueprintLibGame::UvrSetRotateAroundComponentId(const FString& id)
{
	auto* const pMgr = IUvrPlugin::Get().GetGameMgr();
	if (pMgr)
		pMgr->SetRotateAroundComponent(id);
}
