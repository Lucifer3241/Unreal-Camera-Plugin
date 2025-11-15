// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirectorPawn.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ACameraDirectorPawn::ACameraDirectorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	// Create camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


	// Default camera mode
	CameraMode = ECameraMode::ThirdPerson;

	// Create movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	bUseControllerRotationYaw = true;

}

// Called when the game starts or when spawned
void ACameraDirectorPawn::BeginPlay()
{
	Super::BeginPlay();

	SetCameraMode(CameraMode);

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

	SetCurrentActor(ActorToUse);
	
}

// Called every frame
void ACameraDirectorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void ACameraDirectorPawn::SetCameraMode(ECameraMode NewCameraMode)
{
	CameraMode = NewCameraMode;
	ApplyCameraMode(NewCameraMode);
}


void ACameraDirectorPawn::SetCurrentActor(AActor* NewActor)
{
	//if has parented to previous actor, detach

	if(CurrentActor)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Log, TEXT("CameraDirectorPawn: Detached from previous actor %s"), *CurrentActor->GetName());
	}

	CurrentActor = NewActor;
	if (CurrentActor)
	{
		AttachToComponent(CurrentActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		UE_LOG(LogTemp, Log, TEXT("CameraDirectorPawn: Set current actor to %s"), *CurrentActor->GetName());
	}
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

void ACameraDirectorPawn::ApplyCameraMode(ECameraMode Mode)
{
	switch (Mode)
	{
	case ECameraMode::FirstPerson:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: First Person"));
		Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SpringArm->TargetArmLength = 0.0f;
		SpringArm->bUsePawnControlRotation = true;
		bUseControllerRotationYaw = true;
		bAllowLook = false;
		bAllowMovement = false;
		if(CurrentActor)
		{
			SetActorLocation(CurrentActor->GetActorLocation());
			SetActorRotation(CurrentActor->GetActorRotation());
		}
		break;
	case ECameraMode::ThirdPerson:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Third Person"));
		Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SpringArm->TargetArmLength = 300.0f;
		SpringArm->bUsePawnControlRotation = true;
		bUseControllerRotationYaw = true;
		bAllowLook = false;
		bAllowMovement = false;
		if(CurrentActor)
		{
			SetActorLocation(CurrentActor->GetActorLocation());
			SetActorRotation(CurrentActor->GetActorRotation());
		}
		break;
	case ECameraMode::Spectator:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Spectator"));
		Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SpringArm->TargetArmLength = 600.0f;
		SpringArm->bUsePawnControlRotation = true;
		bUseControllerRotationYaw = false;
		bAllowLook = true;
		bAllowMovement = false;
		if(CurrentActor)
		{
			SetActorLocation(CurrentActor->GetActorLocation());
			SetActorRotation(CurrentActor->GetActorRotation());
		}
		break;
	case ECameraMode::FreeRoam:
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Free Roam"));
		Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SpringArm->bUsePawnControlRotation = false;
		//SpringArm->TargetArmLength = 0.0f;
		bUseControllerRotationYaw = true;
		bUseControllerRotationPitch = true;
		bAllowLook = true;
		bAllowMovement = true;
		break;
	default:
		break;
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
