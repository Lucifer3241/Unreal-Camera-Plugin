#include "SpectatorCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"

void USpectatorCameraMode::EnterMode(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Spectator"));
	CameraPawn->Camera->AttachToComponent(CameraPawn->SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CameraPawn->SpringArm->TargetArmLength = 600.0f;
	CameraPawn->SpringArm->bUsePawnControlRotation = true;
	CameraPawn->bUseControllerRotationYaw = false;
	
	//Allow both movement and look in spectator mode
	CameraPawn->bAllowLook = true;
	CameraPawn->bAllowMovement = false;

	//Set CameraPawn location and rotation to match CurrentActor
	if (CameraPawn->CurrentActor)
	{
		CameraPawn->SetActorLocation(CameraPawn->CurrentActor->GetActorLocation());
		CameraPawn->SetActorRotation(CameraPawn->CurrentActor->GetActorRotation());
	}
}