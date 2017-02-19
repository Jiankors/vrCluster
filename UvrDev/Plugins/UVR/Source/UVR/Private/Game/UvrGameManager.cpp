// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrGameManager.h"

#include "UvrPlugin.h"


UvrGameManager::UvrGameManager()
{
	UE_LOG(LogUvrGame, Verbose, TEXT("UvrGameManager .ctor"));
}

UvrGameManager::~UvrGameManager()
{
	UE_LOG(LogUvrGame, Verbose, TEXT("UvrGameManager .dtor"));
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IPUvrManager
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrGameManager::Init()
{
	return true;
}

void UvrGameManager::Release()
{
}

bool UvrGameManager::StartSession(const FString& configPath)
{
	return true;
}

void UvrGameManager::EndSession()
{
}

bool UvrGameManager::StartGame(UWorld* pWorld)
{
	FScopeLock lock(&m_sync);
	check(pWorld);

	m_pWorld = pWorld;

	if (!InitializeUvrActor())
	{
		UE_LOG(LogUvrGame, Error, TEXT("Couldn't initialize UVR hierarchy"));
		return false;
	}

	return true;
}

void UvrGameManager::EndGame()
{
	FScopeLock lock(&m_sync);

	m_pWorld = nullptr;
	m_pRoot = nullptr;
	m_pScreen = nullptr;
	m_pCamera = nullptr;

	// Clean containers. We store only pointers so there is no need to do any additional
	// operations. All components will be destroyed by the engine.
	m_screens.Reset();
	m_cameras.Reset();
	m_nodes.Reset();
}


//////////////////////////////////////////////////////////////////////////////////////////////
// IUvrGameManager
//////////////////////////////////////////////////////////////////////////////////////////////
AUvrRoot* UvrGameManager::GetRoot() const
{
	FScopeLock lock(&m_sync);
	return m_pRoot;
}

UUvrScreenComponent* UvrGameManager::GetActiveScreen() const
{
	FScopeLock lock(&m_sync);
	return m_pScreen;
}

UUvrScreenComponent* UvrGameManager::GetScreenById(const FString& id) const
{
	FScopeLock lock(&m_sync);
	return GetItem<UUvrScreenComponent>(m_screens, id, FString("GetScreenById"));
}

TArray<UUvrScreenComponent*> UvrGameManager::GetAllScreens() const
{
	FScopeLock lock(&m_sync);
	return GetMapValues<UUvrScreenComponent>(m_screens);
}

int32 UvrGameManager::GetScreensAmount() const
{
	FScopeLock lock(&m_sync);
	return m_screens.Num();
}

UUvrCameraComponent* UvrGameManager::GetActiveCamera() const
{
	FScopeLock lock(&m_sync);
	return m_pCamera;
}

UUvrCameraComponent* UvrGameManager::GetCameraById(const FString& id) const
{
	FScopeLock lock(&m_sync);
	return GetItem<UUvrCameraComponent>(m_cameras, id, FString("GetCameraById"));
}

TArray<UUvrCameraComponent*> UvrGameManager::GetAllCameras() const
{
	FScopeLock lock(&m_sync);
	return GetMapValues<UUvrCameraComponent>(m_cameras);
}

int32 UvrGameManager::GetCamerasAmount() const
{
	FScopeLock lock(&m_sync);
	return m_cameras.Num();
}

void UvrGameManager::SetActiveCamera(int32 idx)
{
	check(idx < UvrPlugin::get().ConfigMgr->GetCamerasAmount());

	SUvrConfigCamera cam;
	if (!UvrPlugin::get().ConfigMgr->GetCamera(idx, cam))
	{
		UE_LOG(LogUvrGame, Error, TEXT("Camera not found (idx=%d)"), idx);
		return;
	}

	return SetActiveCamera(cam.Id);
}

void UvrGameManager::SetActiveCamera(const FString& id)
{
	FScopeLock lock(&m_sync);

	if (!m_cameras.Contains(id))
	{
		UE_LOG(LogUvrGame, Error, TEXT("Couldn't switch camera. No such node id: %s"), *id);
		return;
	}

	m_pCamera = m_cameras[id];
	m_pRoot->GetCameraComponent()->AttachToComponent(m_pCamera, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	m_pRoot->GetCameraComponent()->SetRelativeLocation(FVector::ZeroVector);
	m_pRoot->GetCameraComponent()->SetRelativeRotation(FRotator::ZeroRotator);

	// Update 'rotate around' component
	SetRotateAroundComponent(m_pCamera);

	UE_LOG(LogUvrGame, Log, TEXT("Camera %s activated"), *m_pCamera->UvrGetId());
}

UUvrSceneComponent* UvrGameManager::GetNodeById(const FString& id) const
{
	FScopeLock lock(&m_sync);
	return GetItem<UUvrSceneComponent>(m_nodes, id, FString("GetNodeById"));
}

TArray<UUvrSceneComponent*> UvrGameManager::GetAllNodes() const
{
	FScopeLock lock(&m_sync);
	return GetMapValues<UUvrSceneComponent>(m_nodes);
}

USceneComponent* UvrGameManager::GetTranslationDirectionComponent() const
{
	FScopeLock lock(&m_sync);
	check(m_pRoot);

	UE_LOG(LogUvrGame, Verbose, TEXT("GetTranslationDirectionComponent: %s"), (m_pRoot->TranslationDirection ? *m_pRoot->TranslationDirection->GetName() : TEXT("nullptr")));
	return m_pRoot->TranslationDirection;
}

void UvrGameManager::SetTranslationDirectionComponent(USceneComponent* const pComp)
{
	FScopeLock lock(&m_sync);
	check(m_pRoot);

	UE_LOG(LogUvrGame, Log, TEXT("New translation direction component set: %s"), (pComp ? *pComp->GetName() : TEXT("nullptr")));
	m_pRoot->TranslationDirection = pComp;
}

void UvrGameManager::SetTranslationDirectionComponent(const FString& id)
{
	FScopeLock lock(&m_sync);
	check(m_pRoot);

	UE_LOG(LogUvrGame, Log, TEXT("New translation direction node id requested: %s"), *id);
	SetTranslationDirectionComponent(GetNodeById(id));
}

USceneComponent* UvrGameManager::GetRotateAroundComponent() const
{
	FScopeLock lock(&m_sync);
	check(m_pRoot);

	UE_LOG(LogUvrGame, Verbose, TEXT("GetRotateAroundComponent: %s"), (m_pRoot->RotationAround ? *m_pRoot->RotationAround->GetName() : TEXT("nullptr")));
	return m_pRoot->RotationAround;
}

void UvrGameManager::SetRotateAroundComponent(USceneComponent* const pComp)
{
	FScopeLock lock(&m_sync);
	check(m_pRoot);
	
	UE_LOG(LogUvrGame, Log, TEXT("New rotate around component set: %s"), (pComp ? *pComp->GetName() : TEXT("nullptr")));
	m_pRoot->RotationAround = pComp;
}

void UvrGameManager::SetRotateAroundComponent(const FString& id)
{
	FScopeLock lock(&m_sync);
	check(m_pRoot);

	UE_LOG(LogUvrGame, Log, TEXT("New rotate around node id requested: %s"), *id);
	m_pRoot->RotationAround = GetNodeById(id);
}


//////////////////////////////////////////////////////////////////////////////////////////////
// UvrGameManager
//////////////////////////////////////////////////////////////////////////////////////////////
bool UvrGameManager::InitializeUvrActor()
{
	check(m_pWorld);

	auto pController = UGameplayStatics::GetPlayerController(m_pWorld, 0);
	check(pController);
	
	m_pRoot = StaticCast<AUvrRoot*>(pController->GetPawn());
	check(m_pRoot);

	if (!(CreateCameras() && CreateScreens() && CreateNodes()))
	{
		UE_LOG(LogUvrGame, Error, TEXT("An error occurred during UVR root initialization"));
		return false;
	}

	// Let UVR nodes initialize ourselves
	for (auto it = m_nodes.CreateIterator(); it; ++it)
	{
		if (it->Value->UvrApplySettings() == false)
			UE_LOG(LogUvrGame, Warning, TEXT("Coulnd't initialize UVR node: ID=%s"), *it->Key);
	}

	// Set the first camera active by default
	SetActiveCamera(m_pCamera->UvrGetId());

	// Check if default camera was specified in command line arguments
	FString camId;
	if (FParse::Value(FCommandLine::Get(), UvrStrings::args::Camera, camId))
	{
		UvrHelpers::str::DustCommandLineValue(camId);
		UE_LOG(LogUvrGame, Log, TEXT("Default camera from command line arguments: %s"), *camId);
		if(m_cameras.Contains(camId))
			SetActiveCamera(camId);
	}

	return true;
}

bool UvrGameManager::CreateScreens()
{
	// Get local screen settings
	SUvrConfigScreen localScreen;
	if (UvrPlugin::get().ConfigMgr->GetLocalScreen(localScreen) == false)
	{
		UE_LOG(LogUvrGame, Error, TEXT("Couldn't get projection screen settings"), );
		return false;
	}

	// Create screens
	const TArray<SUvrConfigScreen> screens = UvrPlugin::get().ConfigMgr->GetScreens();
	for (const auto& screen : screens)
	{
		// Create screen
		UUvrScreenComponent* pScreen = NewObject<UUvrScreenComponent>(m_pRoot, FName(*screen.Id), RF_Transient);
		check(pScreen);

		pScreen->AttachToComponent(m_pRoot->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		pScreen->RegisterComponent();

		// Pass settings
		pScreen->UvrSetSettings(&screen);

		// Is this active screen (for this node)?
		if (screen.Id == localScreen.Id)
			m_pScreen = pScreen;

		// Store the screen
		m_screens.Add(screen.Id, pScreen);
		m_nodes.Add(screen.Id, pScreen);
	}

	// Check if local screen was found
	check(m_pScreen);
	if (!m_pScreen)
	{
		UE_LOG(LogUvrGame, Error, TEXT("Local screen not found"));
		return false;
	}

	return true;
}

bool UvrGameManager::CreateNodes()
{
	// Create other nodes
	const TArray<SUvrConfigSceneNode> nodes = UvrPlugin::get().ConfigMgr->GetSceneNodes();
	for (const auto& node : nodes)
	{
		UUvrSceneComponent* pNode = NewObject<UUvrSceneComponent>(m_pRoot, FName(*node.Id), RF_Transient);
		check(pNode);

		pNode->AttachToComponent(m_pRoot->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		pNode->RegisterComponent();

		pNode->UvrSetSettings(&node);
		m_nodes.Add(node.Id, pNode);
	}

	return true;
}

bool UvrGameManager::CreateCameras()
{
	const TArray<SUvrConfigCamera> cams = UvrPlugin::get().ConfigMgr->GetCameras();
	for (const auto& cam : cams)
	{
		UUvrCameraComponent* pCam = NewObject<UUvrCameraComponent>(m_pRoot, FName(*cam.Id), RF_Transient);
		check(pCam);

		pCam->AttachToComponent(m_pRoot->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		pCam->RegisterComponent();

		pCam->UvrSetSettings(&cam);
		
		m_cameras.Add(cam.Id, pCam);
		m_nodes.Add(cam.Id, pCam);

		if (m_pCamera == nullptr)
			m_pCamera = pCam;
	}

	// At least one camera must be set up
	if (!m_pCamera)
	{
		UE_LOG(LogUvrGame, Warning, TEXT("No camera found"));
		return false;
	}

	return m_cameras.Num() > 0;
}
