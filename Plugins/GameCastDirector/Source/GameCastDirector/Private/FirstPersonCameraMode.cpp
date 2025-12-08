#include "FirstPersonCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraTypeProfile.h"

void UFirstPersonCameraMode::AttachCamera(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	//if(CameraPawn->GetOldActor()==CameraPawn->GetCurrentActor() && CameraPawn->CurrentCameraType == ECameraType::FirstPerson)
	//{
	//	//already in this mode with same actor
	//	return;
	//}

	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	if (!SpringArm) return;
	
	//target the camera component
	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;

	CameraPawn->CurrentCameraType = ECameraType::FirstPerson;
	Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Camera->AttachToComponent(CameraPawn->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);	

	AActor* CurrentActor = CameraPawn->GetCurrentActor();
	if (CurrentActor)
	{
		UCameraComponent* CurrentActorCamera = nullptr;
		if(CameraPawn->PerspectiveModeCameraName != NAME_None)
		{		
			CurrentActorCamera = Cast<UCameraComponent>(CurrentActor->GetDefaultSubobjectByName(CameraPawn->PerspectiveModeCameraName));
		}
		else
		{
			CurrentActorCamera = CurrentActor->FindComponentByClass<UCameraComponent>();
		}

		if (CurrentActorCamera)
		{
			CameraPawn->AttachToComponent(CurrentActorCamera, FAttachmentTransformRules::SnapToTargetIncludingScale);
			CameraPawn->SetActorRelativeLocation(FVector::ZeroVector);
			CameraPawn->SetActorRelativeRotation(FRotator::ZeroRotator);
			//set same camera settings
			CameraPawn->CopyCameraSettingsFrom(CurrentActorCamera, Camera);
		}
	}
}

void UFirstPersonCameraMode::CustomBehavior(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	//Custom behavior for first person camera mode can be added here
	CameraPawn->bUseControllerRotationPitch = false;
	CameraPawn->bUseControllerRotationYaw = false;

	CameraPawn->SetCollisionEnabled(false);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: First Person"));
		//print CameraPawn current actor name
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Current Actor: %s"), *CameraPawn->GetCurrentActor()->GetName()));
	}
}
