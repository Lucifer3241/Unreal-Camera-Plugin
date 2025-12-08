#include "FreeRoamCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraTypeProfile.h"

void UFreeRoamCameraMode::AttachCamera(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	//if (CameraPawn->CurrentCameraType == ECameraType::FreeRoam)
	//{
	//	//already in this mode with same actor
	//	return;
	//}

	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	if (!SpringArm) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;
	CameraPawn->CurrentCameraType = ECameraType::FreeRoam;

	FVector CameraLocation = Camera->GetComponentLocation() + (-Camera->GetForwardVector() * 20.0f);
	FRotator CameraRotation = Camera->GetComponentRotation();

	Camera->AttachToComponent(CameraPawn->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CameraPawn->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CameraPawn->SetActorLocation(Camera->GetComponentLocation());

	AController* Controller = CameraPawn->GetController();
	if (Controller)
	{
		Controller->SetControlRotation(CameraRotation);
	}
	CameraPawn->SetActorLocation(CameraLocation);
}

void UFreeRoamCameraMode::CustomBehavior(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;
	
	//Custom behavior for Free Roam Camera Mode can be added here
	CameraPawn->bUseControllerRotationPitch = true;
	CameraPawn->bUseControllerRotationYaw = true;

	CameraPawn->SetCollisionEnabled(true);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Free Roam"));
		//print CameraPawn current actor name
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Current Actor: %s"), *CameraPawn->GetCurrentActor()->GetName()));
	}
}