#include "FreeRoamCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void UFreeRoamCameraMode::EnterMode(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	if (CameraPawn->CameraMode == ECameraMode::FreeRoam)
	{
		//already in this mode with same actor
		return;
	}

	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	if (!SpringArm) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;

	FVector CameraLocation = Camera->GetComponentLocation() + (-Camera->GetForwardVector() * 20.0f);
	FRotator CameraRotation = Camera->GetComponentRotation();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Free Roam"));
	//print CameraPawn current actor name
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Current Actor: %s"), *CameraPawn->GetCurrentActor()->GetName()));
	Camera->AttachToComponent(CameraPawn->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CameraPawn->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CameraPawn->SetActorLocation(Camera->GetComponentLocation());

	AController* Controller = CameraPawn->GetController();
	if (Controller)
	{
		Controller->SetControlRotation(CameraRotation);
	}
	CameraPawn->SetActorLocation(CameraLocation);
	
	//No need to set TargetArmLength in free roam mode
	//CameraPawn->SpringArm->TargetArmLength = 0.0f;
	
	SpringArm->bUsePawnControlRotation = false;
	CameraPawn->bUseControllerRotationYaw = true;
	CameraPawn->bUseControllerRotationPitch = true;
	
	//Allow both movement and look in free roam mode
	CameraPawn->SetAllowLook(true);
	CameraPawn->SetAllowMovement(true);

	CameraPawn->CameraMode = ECameraMode::FreeRoam;
}