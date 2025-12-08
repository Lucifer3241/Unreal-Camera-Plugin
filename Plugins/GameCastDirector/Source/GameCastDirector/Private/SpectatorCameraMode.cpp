#include "SpectatorCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void USpectatorCameraMode::AttachCamera(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	if (!SpringArm) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Spectator"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bUsePawnControlRotation = true;
	CameraPawn->bUseControllerRotationYaw = false;
	
	//Allow look but not movement in spectator mode
	CameraPawn->SetAllowLook(true);
	CameraPawn->SetAllowMovement(false);

	AActor* CurrentActor = CameraPawn->GetCurrentActor();
	// Set CameraPawn location and rotation to match CurrentActor
	if (CurrentActor)
	{
		CameraPawn->SetActorLocation(CurrentActor->GetActorLocation());
		CameraPawn->SetActorRotation(CurrentActor->GetActorRotation());
	}
}

void USpectatorCameraMode::CustomBehavior(ACameraDirectorPawn* CameraPawn)
{
}
