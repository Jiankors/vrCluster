// Copyright 2016 Pixela Labs. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "UVR.generated.h"


UCLASS()
class UVR_API AUVR : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AUVR();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostLoad() override;

private:
	inline void UpdateUvrSettings();
#endif

private:
	UPROPERTY(EditAnywhere)
	FString UvrEditorConfigPath;

	UPROPERTY(EditAnywhere)
	FString UvrEditorNodeName;

	UPROPERTY(EditAnywhere)
	bool UvrEditorShowProjectionScreens;

public:
	static FString ms_EditorConfigPath;
	static FString ms_EditorNodeName;
	static bool ms_EditorShowProjectionScreens;
};
