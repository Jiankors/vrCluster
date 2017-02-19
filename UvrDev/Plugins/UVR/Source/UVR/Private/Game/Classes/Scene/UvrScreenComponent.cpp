// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrScreenComponent.h"

#include "UVR.h"


UUvrScreenComponent::UUvrScreenComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	if (GEngine && GEngine->IsEditor())
	{
		if (AUVR::ms_EditorShowProjectionScreens)
		{
			ScreenGeometryComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(*(GetName() + FString("_impl"))));
			check(ScreenGeometryComponent);

			static ConstructorHelpers::FObjectFinder<UStaticMesh> screenMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
			static ConstructorHelpers::FObjectFinder<UMaterial>   screenMat(TEXT("Material'/Engine/Engine_MI_Shaders/M_Shader_SimpleTranslucent.M_Shader_SimpleTranslucent'"));

			ScreenGeometryComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
			ScreenGeometryComponent->SetStaticMesh(screenMesh.Object);
			ScreenGeometryComponent->SetMaterial(0, screenMat.Object);
			ScreenGeometryComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}


void UUvrScreenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UUvrScreenComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

}

void UUvrScreenComponent::UvrSetSettings(const SUvrConfigSceneNode* const pConfig)
{
	auto pScreenCfg = static_cast<const SUvrConfigScreen* const>(pConfig);
	m_size = pScreenCfg->Size * GetWorld()->GetWorldSettings()->WorldToMeters;

	Super::UvrSetSettings(pConfig);
}

bool UUvrScreenComponent::UvrApplySettings()
{
	if (GEngine && GEngine->IsEditor())
	{
		if (AUVR::ms_EditorShowProjectionScreens)
		{
			const FVector2D scale = m_size / GetWorld()->GetWorldSettings()->WorldToMeters;
			ScreenGeometryComponent->RegisterComponent();
			ScreenGeometryComponent->SetRelativeScale3D(FVector(0.001f, scale.X, scale.Y));
		}
	}

	return Super::UvrApplySettings();
}
