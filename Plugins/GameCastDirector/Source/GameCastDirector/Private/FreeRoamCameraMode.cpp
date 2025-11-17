#include "FreeRoamCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"

void UFreeRoamCameraMode::EnterMode(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: First Person"));
	CameraPawn->Camera->AttachToComponent(CameraPawn->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//CameraPawn->SpringArm->TargetArmLength = 0.0f;
	CameraPawn->SpringArm->bUsePawnControlRotation = false;
	CameraPawn->bUseControllerRotationYaw = true;
	CameraPawn->bUseControllerRotationPitch = true;
	CameraPawn->bAllowLook = true;
	CameraPawn->bAllowMovement = true;
}