// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirectorPawn.h"
#include "CameraTypeBase.h"
#include "CameraTypeProfile.h"
#include "CameraMomentRecorder.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACameraDirectorPawn::ACameraDirectorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	RootComponent = CollisionCapsule;

	CollisionCapsule->InitCapsuleSize(40.f, 40.f);
	CollisionCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionCapsule->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionCapsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	CollisionCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	// Create spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	// Create camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Create movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	bUseControllerRotationYaw = true;

	//Create default scene capture component
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(Camera);

	SceneCaptureComponent->bCaptureEveryFrame = false;
	SceneCaptureComponent->bCaptureOnMovement = true;

}

void ACameraDirectorPawn::SetCollisionEnabled(bool bEnabled)
{
	if (bEnabled)
	{
		CollisionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		UE_LOG(LogTemp, Log, TEXT("Collision: ENABLED"));
	}
	else
	{
		CollisionCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UE_LOG(LogTemp, Log, TEXT("Collision: DISABLED"));
	}
}

// Called when the game starts or when spawned
void ACameraDirectorPawn::BeginPlay()
{
	Super::BeginPlay();

	//Set the input mode for the player controller
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	//SetCameraMode(CameraMode);

	// Get all actors of the specified class in the level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetActorClass, TargetActors);

	AActor* ActorToUse = nullptr;

	if(TargetActor)
	{
		ActorToUse = TargetActor;
	}
	else if (TargetActors.Num() > 0)
	{
		ActorToUse = TargetActors[0];
	}

	//Check all required modes have profiles for the actor
	for(auto& ModePair : CameraTypeProfiles)
	{
		if(!ModePair.Value)
		{
			UE_LOG(LogTemp, Warning, TEXT("CameraDirectorPawn: Camera Mode %d does not have a valid profile for Actor %s"), (uint8)ModePair.Key, *ActorToUse->GetName());
		}
	}

	if (!RenderTarget)
	{
		RenderTarget = NewObject<UTextureRenderTarget2D>(this);
		RenderTarget->InitAutoFormat(1920, 1080);
		RenderTarget->UpdateResource();
	}
	if (SceneCaptureComponent)
	{
		SceneCaptureComponent->TextureTarget = RenderTarget;
	}

	SetCurrentActor(ActorToUse);
	ApplyCameraMode(StartCameraType);
	SpawnPreviewCameras();

	MomentRecorder = NewObject<UCameraMomentRecorder>(this);	
}

// Called every frame
void ACameraDirectorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), Camera->GetComponentLocation(), 10, 8, FColor::Green);
	DrawDebugSphere(GetWorld(), SceneCaptureComponent->GetComponentLocation(), 10, 8, FColor::Red);

	SceneCaptureComponent->CaptureScene();
	//SceneCaptureComponent->AddLocalOffset(FVector(0.0001f, 0, 0));
}

// Called to bind functionality to input
void ACameraDirectorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACameraDirectorPawn::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACameraDirectorPawn::Look);

		// Camera Modes
		EnhancedInputComponent->BindAction(FirstPersonAction, ETriggerEvent::Started, this, 
			&ACameraDirectorPawn::ApplyCameraMode, ECameraType::FirstPerson);
		EnhancedInputComponent->BindAction(ThirdPersonAction, ETriggerEvent::Started, this,
			&ACameraDirectorPawn::ApplyCameraMode, ECameraType::ThirdPerson);
		EnhancedInputComponent->BindAction(SpectatorAction, ETriggerEvent::Started, this,
			&ACameraDirectorPawn::ApplyCameraMode, ECameraType::Spectator);
		EnhancedInputComponent->BindAction(FreeRoamAction, ETriggerEvent::Started, this,
			&ACameraDirectorPawn::ApplyCameraMode, ECameraType::FreeRoam);

		//Moment Recording
		EnhancedInputComponent->BindAction(RecordMomentAction, ETriggerEvent::Started, this,
			&ACameraDirectorPawn::RecordCameraMoment);
		EnhancedInputComponent->BindAction(NextMomentAction, ETriggerEvent::Started, this,
			&ACameraDirectorPawn::GotoNextCameraHotPoint);
		EnhancedInputComponent->BindAction(PreviousMomentAction, ETriggerEvent::Started, this,
			&ACameraDirectorPawn::GotoPreviousCameraHotPoint);
	}

}

void ACameraDirectorPawn::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACameraDirectorPawn::SetCurrentActor(AActor* NewActor)
{
	//if has parented to previous actor, detach
	if(CurrentActor)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Log, TEXT("CameraDirectorPawn: Detached from previous actor %s"), *CurrentActor->GetName());
	}
	OldActor = CurrentActor;

	CurrentActor = NewActor;

	//log old and new actor names
	UE_LOG(LogTemp, Log, TEXT("CameraDirectorPawn: Changed current actor from %s to %s"), 
		OldActor ? *OldActor->GetName() : TEXT("None"), 
		CurrentActor ? *CurrentActor->GetName() : TEXT("None"));

	//if (CurrentActor)
	//{
	//	ApplyCameraMode();
	//}
}

void ACameraDirectorPawn::NextActor()
{
	if (TargetActors.Num() == 0)
		return;
	int32 CurrentIndex = TargetActors.IndexOfByKey(CurrentActor);
	int32 NextIndex = (CurrentIndex + 1) % TargetActors.Num();
	SetCurrentActor(TargetActors[NextIndex]);

}

void ACameraDirectorPawn::PreviousActor()
{
	if (TargetActors.Num() == 0)
		return;
	int32 CurrentIndex = TargetActors.IndexOfByKey(CurrentActor);
	int32 PreviousIndex = (CurrentIndex - 1 + TargetActors.Num()) % TargetActors.Num();
	SetCurrentActor(TargetActors[PreviousIndex]);

}

void ACameraDirectorPawn::CopyCameraSettingsFrom(UCameraComponent* FromCamera, UCameraComponent* ToCamera)
{
	if(!FromCamera ||! ToCamera)
		return;

	//camera settings
	ToCamera->ProjectionMode = FromCamera->ProjectionMode;

	if(ToCamera->ProjectionMode == ECameraProjectionMode::Orthographic)
	{
		ToCamera->OrthoWidth = FromCamera->OrthoWidth;
		ToCamera->bAutoCalculateOrthoPlanes = FromCamera->bAutoCalculateOrthoPlanes;
		ToCamera->AutoPlaneShift = FromCamera->AutoPlaneShift;
		ToCamera->OrthoNearClipPlane = FromCamera->OrthoNearClipPlane;
		ToCamera->OrthoFarClipPlane = FromCamera->OrthoFarClipPlane;
		ToCamera->bUpdateOrthoPlanes = FromCamera->bUpdateOrthoPlanes;
		ToCamera->bUseCameraHeightAsViewTarget = FromCamera->bUseCameraHeightAsViewTarget;
	}
	else if(ToCamera->ProjectionMode == ECameraProjectionMode::Perspective)
	{
		ToCamera->FieldOfView = FromCamera->FieldOfView;
	}
	ToCamera->AspectRatio = FromCamera->AspectRatio;

	ToCamera->FirstPersonFieldOfView = FromCamera->FirstPersonFieldOfView;
	ToCamera->FirstPersonScale = FromCamera->FirstPersonScale;

	//Camera options
	ToCamera->bConstrainAspectRatio = FromCamera->bConstrainAspectRatio;
	//ToCamera->bUsePawnControlRotation = FromCamera->bUsePawnControlRotation;
	ToCamera->PostProcessBlendWeight = FromCamera->PostProcessBlendWeight;
	ToCamera->AspectRatioAxisConstraint = FromCamera->AspectRatioAxisConstraint;

	ToCamera->bOverrideAspectRatioAxisConstraint = FromCamera->bOverrideAspectRatioAxisConstraint;
	ToCamera->bLockToHmd = FromCamera->bLockToHmd;
	ToCamera->bEnableFirstPersonFieldOfView = FromCamera->bEnableFirstPersonFieldOfView;
	ToCamera->bEnableFirstPersonScale = FromCamera->bEnableFirstPersonScale;
	ToCamera->bUseFieldOfViewForLOD = FromCamera->bUseFieldOfViewForLOD;

	//Post process settings
	ToCamera->PostProcessSettings = FromCamera->PostProcessSettings;
}


void ACameraDirectorPawn::ApplyCameraMode(ECameraType Type)
{
	if (CameraTypes.Contains(Type))
	{
		CurrentCameraType = Type;
		UCameraTypeBase* CameraTypeInstance = CameraTypes[Type];
		if (CameraTypeInstance)
		{
			CameraTypeInstance->CameraTypeLifecycle(this);
		}
	}
}

void ACameraDirectorPawn::Move(const FInputActionValue& Value)
{
	if (!bAllowMovement)
		return;

	// input is a Vector2D
	FVector2D Input = Value.Get<FVector2D>();

	AddMovementInput(Camera->GetForwardVector(), Input.Y);
	AddMovementInput(Camera->GetRightVector(), Input.X);
}

void ACameraDirectorPawn::Look(const FInputActionValue& Value)
{
	if (!bAllowLook)
		return;
	// input is a Vector2D
	FVector2D LookAxis = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

UCameraTypeProfile* ACameraDirectorPawn::GetCameraTypeProfile(ECameraType Type) const
{
	if(CameraTypeProfiles.Contains(Type))
	{
		return CameraTypeProfiles[Type];
	}
	
	UE_LOG(LogTemp, Warning, TEXT("CameraDirectorPawn: No CameraTypeProfile found for mode %d"), static_cast<uint8>(Type));
	return nullptr;
}

void ACameraDirectorPawn::SpawnPreviewCameras()
{
	const int32 NumCameras = 12;

	for (int i = 0; i < NumCameras; i++)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;

		ACameraPreviewActor* Cam = GetWorld()->SpawnActor<ACameraPreviewActor>(
			PreviewCameraClass,
			FVector(0, i * 100, 300),   // space them out
			FRotator::ZeroRotator,
			Params
		);

		PreviewCameras.Add(Cam);
	}
}

void ACameraDirectorPawn::RecordCameraMoment()
{
	if (!MomentRecorder) return;
	MomentRecorder->RecordMoment(this);
}

//void ACameraDirectorPawn::GotoCameraMoment(int32 Index)
//{
//	if(!MomentRecorder) return;
//	MomentRecorder->GoToMoment(this, Index);
//}

void ACameraDirectorPawn::GotoNextCameraHotPoint()
{
	if(MomentRecorder)
	{
		MomentRecorder->GoToNextHotPoint(this);
	}
}

void ACameraDirectorPawn::GotoPreviousCameraHotPoint()
{
	if(MomentRecorder)
	{
		MomentRecorder->GoToPreviousHotPoint(this);
	}
}

void ACameraDirectorPawn::SetCameraLockedToMoments(bool bLocked)
{
	bCameraLockedToMoments = bLocked;
	
	SetAllowLook(!bLocked);
	SetAllowMovement(!bLocked);

	if (!SpringArm) return;

	SpringArm->bUsePawnControlRotation = !bLocked;
	SetCollisionEnabled(!bLocked);
}