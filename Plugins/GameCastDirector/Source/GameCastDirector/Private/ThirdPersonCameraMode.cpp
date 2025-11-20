#include "ThirdPersonCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void UThirdPersonCameraMode::EnterMode(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	if (!SpringArm) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Third Person"));

	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;
	CameraPawn->bUseControllerRotationYaw = true;
	
	//Don't allow movement or look in third person mode
	CameraPawn->SetAllowLook(false);
	CameraPawn->SetAllowMovement(false);

	AActor* CurrentActor = CameraPawn->GetCurrentActor();
	// Set CameraPawn location and rotation to match CurrentActor
	if (CurrentActor)
	{
		CameraPawn->SetActorLocation(CurrentActor->GetActorLocation());
		CameraPawn->SetActorRotation(CurrentActor->GetActorRotation());
	}
}