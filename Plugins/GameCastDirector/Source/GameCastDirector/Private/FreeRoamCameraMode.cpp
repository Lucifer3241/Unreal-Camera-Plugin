#include "FreeRoamCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void UFreeRoamCameraMode::EnterMode(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	if (!SpringArm) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Free Roam"));
	Camera->AttachToComponent(CameraPawn->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	//No need to set TargetArmLength in free roam mode
	//CameraPawn->SpringArm->TargetArmLength = 0.0f;
	
	SpringArm->bUsePawnControlRotation = false;
	CameraPawn->bUseControllerRotationYaw = true;
	CameraPawn->bUseControllerRotationPitch = true;
	
	//Allow both movement and look in free roam mode
	CameraPawn->SetAllowLook(true);
	CameraPawn->SetAllowMovement(true);
}