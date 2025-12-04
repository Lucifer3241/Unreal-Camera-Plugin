// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraDirectorTypes.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CameraDirectorPawn.generated.h"

class UCameraModeBase;
class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;

UCLASS()
class GAMECASTDIRECTOR_API ACameraDirectorPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraDirectorPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyControllerChanged() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Camera mode property
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	//ECameraMode CameraMode;

	// Actor reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")

	AActor* TargetActor;

	// TargetActors class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TSubclassOf<AActor> TargetActorClass;

	// TargetActor Camera ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FName TargetCameraName;

	// Camera Modes Map
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "CameraModes")
	TMap<ECameraMode, UCameraModeBase*> CameraModes;

	// Function to set camera mode
	//UFUNCTION(BlueprintCallable, Category = "Camera")
	//void SetCameraMode(ECameraMode NewCameraMode);

	//set current actor
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCurrentActor(AActor* NewActor);

	//next target actor
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void NextActor();

	//previous target actor
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void PreviousActor();

	//copy camera settings from another CameraDirectorPawn
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void CopyCameraSettingsFrom(UCameraComponent* FromCamera, UCameraComponent* ToCamera);

protected:

	UFUNCTION(BlueprintCallable, Category = "CameraMode")
	void ApplyCameraMode(ECameraMode Mode);

	// Spring arm component for camera positioning
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;

	// Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	// Movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* MovementComponent;

	bool bAllowMovement = true;
	bool bAllowLook = true;

	// Array to hold target actors
	TArray<AActor*> TargetActors;

	// Current target actor
	AActor* CurrentActor = nullptr;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:
	FORCEINLINE void SetAllowMovement(bool bInAllowMovement) { bAllowMovement = bInAllowMovement; };
	FORCEINLINE void SetAllowLook(bool bInAllowLook) { bAllowLook = bInAllowLook; };
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArm; };
	FORCEINLINE UCameraComponent* GetCameraComponent() { return Camera; };
	FORCEINLINE AActor* GetCurrentActor() { return CurrentActor; };
};
