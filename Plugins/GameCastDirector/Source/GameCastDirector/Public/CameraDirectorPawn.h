// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraDirectorTypes.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CameraDirectorPawn.generated.h"

class UCameraTypeBase;
class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;
class UCameraTypeProfile;
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;
class UCameraMomentRecorder;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UCapsuleComponent* CollisionCapsule;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Camera Start Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")

	ECameraType StartCameraType = ECameraType::ThirdPerson;

	// Camera mode property
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	ECameraType CurrentCameraType = ECameraType::None;

	// Actor reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")

	AActor* TargetActor;

	// TargetActors class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TSubclassOf<AActor> TargetActorClass;

	// TargetActor Camera ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FName PerspectiveModeCameraName;

	// Third Person Spring Arm Length
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ThirdPersonSpringArmLength = 300.0f;

	// Camera Modes Map
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "CameraTypes")
	TMap<ECameraType, UCameraTypeBase*> CameraTypes;

	// Function to set camera mode
	//UFUNCTION(BlueprintCallable, Category = "Camera")
	//void SetCameraMode(ECameraMode NewCameraMode);

	//Function to Enable collision
	UFUNCTION(BlueprintCallable, Category = "Collision")
	void SetCollisionEnabled(bool bEnabled);

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

	UFUNCTION(BlueprintCallable, Category = "CameraMode")
	void ApplyCameraMode(ECameraType Type);

protected:

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

	//store old actor
	AActor* OldActor = nullptr;

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
	FORCEINLINE AActor* GetOldActor() { return OldActor; };

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Profiles")
	TMap<ECameraType, UCameraTypeProfile*> CameraTypeProfiles;

	UCameraTypeProfile* GetCameraTypeProfile(ECameraType Type) const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|Render")
	USceneCaptureComponent2D* SceneCaptureComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Render")
	UTextureRenderTarget2D* RenderTarget;

public:

	FORCEINLINE USceneCaptureComponent2D* GetSceneCaptureComponent() { return SceneCaptureComponent; };
	FORCEINLINE UTextureRenderTarget2D* GetRenderTarget() { return RenderTarget; };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera|Recording")
	UCameraMomentRecorder* MomentRecorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Recording")
	bool bCameraLockedToMoments = false;

public:

	UFUNCTION(BlueprintCallable, Category = "Camera|Recording")
	void RecordCameraMoment();

	UFUNCTION(BlueprintCallable, Category = "Camera|Recording")
	void GotoCameraMoment(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Camera|Recording")
	void GotoNextCameraHotPoint();

	UFUNCTION(BlueprintCallable, Category = "Camera|Recording")
	void GotoPreviousCameraHotPoint();

	UFUNCTION(BlueprintCallable, Category = "Camera|Recording")
	void SetCameraLockedToMoments(bool bLocked);
};
