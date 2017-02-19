// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "UvrSceneComponent.h"
#include "UvrScreenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UVR_API UUvrScreenComponent : public UUvrSceneComponent
{
	GENERATED_BODY()

public:
	UUvrScreenComponent();

public:
	virtual void UvrSetSettings(const SUvrConfigSceneNode* const pConfig) override;
	virtual bool UvrApplySettings() override;

	inline FVector2D GetScreenSize() const
	{ return m_size; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector2D m_size;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* ScreenGeometryComponent = nullptr;
};
