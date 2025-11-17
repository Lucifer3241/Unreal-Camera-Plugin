#include "ThirdPersonCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"

void UThirdPersonCameraMode::EnterMode(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Third Person"));

	CameraPawn->Camera->AttachToComponent(CameraPawn->SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CameraPawn->SpringArm->TargetArmLength = 300.0f;
	CameraPawn->SpringArm->bUsePawnControlRotation = true;
	CameraPawn->bUseControllerRotationYaw = true;
	CameraPawn->bAllowLook = false;
	CameraPawn->bAllowMovement = false;

	if (CameraPawn->CurrentActor)
	{
		CameraPawn->SetActorLocation(CameraPawn->CurrentActor->GetActorLocation());
		CameraPawn->SetActorRotation(CameraPawn->CurrentActor->GetActorRotation());
	}
}