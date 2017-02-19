// Copyright 2016 Pixela Labs. All Rights Reserved.
#include "UvrPrivatePCH.h"
#include "UvrSceneComponent.h"

#include "UvrPlugin.h"


UUvrSceneComponent::UUvrSceneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUvrSceneComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UUvrSceneComponent::BeginDestroy()
{
	Super::BeginDestroy();
}

void UUvrSceneComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Update transform if attached to a tracker
	if (!m_config.TrackerId.IsEmpty())
	{
		auto& inputMgr = UvrPlugin::get().InputMgr;
		if (inputMgr.IsValid())
		{
			auto loc = inputMgr->GetTrackerLocation(m_config.TrackerId, m_config.TrackerCh);
			auto rot = inputMgr->GetTrackerRotation(m_config.TrackerId, m_config.TrackerCh);

			UE_LOG(LogUvrGame, Verbose, TEXT("%s[%s] update from tracker %s:%d - {loc %s} {rot %s}"),
				*GetName(), *UvrGetId(), *m_config.TrackerId, m_config.TrackerCh, *loc.ToString(), *rot.ToString());

			// Update transform
			this->SetRelativeLocationAndRotation(loc, rot);
			// Force child transforms update
			UpdateChildTransforms(/*true*/);
		}
	}
}

void UUvrSceneComponent::UvrSetSettings(const SUvrConfigSceneNode* const pConfig)
{
	check(pConfig);

	//@todo: do I really need the ref here?
	auto& config = const_cast<SUvrConfigSceneNode&>(m_config);
	config = *pConfig;
	config.Loc *= GetWorld()->GetWorldSettings()->WorldToMeters;
}

bool UUvrSceneComponent::UvrApplySettings()
{
	// Take place in hierarchy
	if (!UvrGetParentId().IsEmpty())
	{
		UE_LOG(LogUvrGame, Log, TEXT("Attaching %s to %s"), *UvrGetId(), *UvrGetParentId());
		auto pComp = UvrPlugin::get().GameMgr->GetNodeById(UvrGetParentId());
		AttachToComponent(pComp, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		this->SetRelativeTransform(FTransform::Identity);
	}

	// Set up location and rotation
	this->SetRelativeLocationAndRotation(m_config.Loc, m_config.Rot);

	return true;
}
