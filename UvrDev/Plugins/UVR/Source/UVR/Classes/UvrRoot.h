// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "GameFramework/Pawn.h"
#include "UvrRoot.generated.h"


class UFloatingPawnMovement;
class USphereComponent;
class UUvrSceneComponentSyncParent;


UCLASS()
class UVR_API AUvrRoot :
	public APawn
{
	GENERATED_UCLASS_BODY()

public:
	/** Name of the MovementComponent.  Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName MovementComponentName;
	/** Name of the CollisionComponent. */
	static FName CollisionComponentName;

public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float BaseLookUpRate;

public:
		/**
	* Input callback to move forward in local space (or backward if Val is negative).
	* @param Val Amount of movement in the forward direction (or backward if negative).
	* @see APawn::AddMovementInput()
	*/
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void MoveForward(float Val);

	/**
	* Input callback to strafe right in local space (or left if Val is negative).
	* @param Val Amount of movement in the right direction (or left if negative).
	* @see APawn::AddMovementInput()
	*/
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void MoveRight(float Val);

	/**
	* Input callback to move up in world space (or down if Val is negative).
	* @param Val Amount of movement in the world up direction (or down if negative).
	* @see APawn::AddMovementInput()
	*/
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void MoveUp(float Val);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void TurnAtRate(float Rate);

	/**
	* Called via input to look up at a given rate (or down if Rate is negative).
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void LookUpAtRate(float Rate);

public:
	/** Returns CollisionComponent subobject **/
	inline USphereComponent* GetCollisionComponent() const
	{ return CollisionComponent; }

	/** Returns CameraComponent subobject **/
	inline UCameraComponent* GetCameraComponent() const
	{ return CameraComponent; }

	/** Returns PawnMovementComponent subobject **/
	virtual UPawnMovementComponent* GetMovementComponent() const override
	{ return MovementComponent; }

private:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// APawn
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SetupPlayerInputComponent(UInputComponent* InInputComponent) override;
	virtual void UpdateNavigationRelevance() override;
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;

public:
		/** Scene component. Specifies translation (UVR hierarchy navigation) direction. */
	UPROPERTY(EditAnywhere, Category = "UVR")
	uint32 bDefaultControlEnabled:1;

	/** Scene component. Specifies translation (UVR hierarchy navigation) direction. */
	UPROPERTY(EditAnywhere, Category = "UVR")
	USceneComponent* TranslationDirection;

	/** Scene component. Specifies rotation center (UVR hierarchy rotation). */
	UPROPERTY(EditAnywhere, Category = "UVR")
	USceneComponent* RotationAround;

protected:
	/** Movement component */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	/** Collision component */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	/** Camera component */
	UPROPERTY(VisibleAnywhere, Category = "UVR")
	UCameraComponent* CameraComponent;

private:
	UUvrSceneComponentSyncParent* UvrSyncParentComponent;
};
