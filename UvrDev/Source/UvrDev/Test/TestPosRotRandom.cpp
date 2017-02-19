// Fill out your copyright notice in the Description page of Project Settings.

#include "UvrDev.h"
#include "TestPosRotRandom.h"


UTestPosRotRandom::UTestPosRotRandom()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTestPosRotRandom::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTestPosRotRandom::OnTimer, 5.0f, true);
}


// Called every frame
void UTestPosRotRandom::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTestPosRotRandom::UpdateTransform()
{
	FVector newLoc;
	newLoc.X = FMath::FRandRange(+2000, +9000);
	newLoc.Y = FMath::FRandRange(-4000, +4000);
	newLoc.Z = FMath::FRandRange( +300, +2000);

	FRotator newRot;
	newRot.Yaw   = FMath::FRand() * 360.f;
	newRot.Pitch = FMath::FRand() * 360.f;
	newRot.Roll  = FMath::FRand() * 360.f;

	GetOwner()->GetRootComponent()->SetRelativeLocation(newLoc);
	GetOwner()->GetRootComponent()->SetRelativeRotation(newRot);
}

void UTestPosRotRandom::OnTimer()
{
	UpdateTransform();
}
