// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrRoot.h"

#include "UvrPlugin.h"
#include "UvrSceneComponentSyncParent.h"


FName AUvrRoot::MovementComponentName(TEXT("MovementComponent0"));
FName AUvrRoot::CollisionComponentName(TEXT("CollisionComponent0"));


AUvrRoot::AUvrRoot(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	// Collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(AUvrRoot::CollisionComponentName);
	CollisionComponent->InitSphereRadius(35.0f);
	CollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->bShouldUpdatePhysicsVolume = true;
	CollisionComponent->SetCanEverAffectNavigation(true);
	CollisionComponent->bDynamicObstacle = true;

	//@todo: temporary disabled collisions
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set as root component
	RootComponent = CollisionComponent;

	// Movement (master node only)
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(AUvrRoot::MovementComponentName);
	MovementComponent->UpdatedComponent = RootComponent;

	// Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("UVR_camera"));
	CameraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->bAbsoluteLocation = false;
	CameraComponent->bAbsoluteRotation = false;

	// UVR sync
	UvrSyncParentComponent = CreateDefaultSubobject<UUvrSceneComponentSyncParent>(TEXT("UVR_root_sync"));
	UvrSyncParentComponent->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	PrimaryActorTick.bCanEverTick = true;
	bFindCameraComponentWhenViewTarget = true;
	bCanBeDamaged = false;
	bReplicates = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	bDefaultControlEnabled = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void AUvrRoot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &AUvrRoot::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight",   this, &AUvrRoot::MoveRight);
		PlayerInputComponent->BindAxis("MoveUp",      this, &AUvrRoot::MoveUp);
		PlayerInputComponent->BindAxis("TurnRate",    this, &AUvrRoot::TurnAtRate);
		PlayerInputComponent->BindAxis("LookUpRate",  this, &AUvrRoot::LookUpAtRate);
	}
}

void AUvrRoot::UpdateNavigationRelevance()
{
	if (CollisionComponent)
	{
		CollisionComponent->SetCanEverAffectNavigation(bCanAffectNavigationGeneration);
	}
}

void AUvrRoot::BeginPlay()
{
	// This make unsync along master and slaves because slaves
	// are synced only on the next frame by transform share mechanism.
#if 0
	if (UvrPlugin::get().ClusterMgr->IsMaster())
	{
		bUseControllerRotationYaw   = true;
		bUseControllerRotationPitch = true;
		bUseControllerRotationRoll  = true;
	}
	else
	{
		bUseControllerRotationYaw   = false;
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll  = false;
	}
#endif

	Super::BeginPlay();
}

void AUvrRoot::BeginDestroy()
{
	Super::BeginDestroy();
}

void AUvrRoot::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AUvrRoot::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		UE_LOG(LogUvrGame, Verbose, TEXT("AUvrRoot::MoveRight: %f"), Val);

		const USceneComponent* const pComp = (TranslationDirection ? TranslationDirection : RootComponent);
		AddMovementInput(pComp->GetRightVector(), Val);
	}
}

void AUvrRoot::MoveForward(float Val)
{
	if (Val != 0.f)
	{
		UE_LOG(LogUvrGame, Verbose, TEXT("AUvrRoot::MoveForward: %f"), Val);

		const USceneComponent* const pComp = (TranslationDirection ? TranslationDirection : RootComponent);
		AddMovementInput(pComp->GetForwardVector(), Val);
	}
}

void AUvrRoot::MoveUp(float Val)
{
	if (Val != 0.f)
	{
		UE_LOG(LogUvrGame, Verbose, TEXT("AUvrRoot::MoveUp: %f"), Val);

		const USceneComponent* const pComp = (TranslationDirection ? TranslationDirection : RootComponent);
		AddMovementInput(pComp->GetUpVector(), Val);
	}
}

void AUvrRoot::TurnAtRate(float Rate)
{
	UE_LOG(LogUvrGame, Verbose, TEXT("AUvrRoot::TurnAtRate: %f"), Rate);

	//@note: currently we ignore RotationAround component because the controller rotates the UvrRoot
	//       around the active camera. This is basically what I need by default. Any other 'rotate around'
	//       policies are out of scope and might be implemented outside of the plugin.

	if (Rate != 0.f)
	{
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
	}
}

void AUvrRoot::LookUpAtRate(float Rate)
{
	if (Rate != 0.f)
	{
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
	}
}
