#include "FirstPersonCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void UFirstPersonCameraMode::EnterMode(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	if (!SpringArm) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: First Person"));

	/*Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bUsePawnControlRotation = true;
	CameraPawn->bUseControllerRotationYaw = true;
	
	//Don't allow movement or look in first person mode
	CameraPawn->SetAllowLook(false);
	CameraPawn->SetAllowMovement(false);

	AActor* CurrentActor = CameraPawn->GetCurrentActor();
	// Set CameraPawn location and rotation to match CurrentActor
	if (CurrentActor)
	{
		CameraPawn->SetActorLocation(CurrentActor->GetActorLocation());
		CameraPawn->SetActorRotation(CurrentActor->GetActorRotation());
	}*/
	SpringArm->bUsePawnControlRotation = false;
	CameraPawn->bUseControllerRotationYaw = false;
	AActor* CurrentActor = CameraPawn->GetCurrentActor();
	if (CurrentActor)
	{
		UCameraComponent* CurrentActorCamera = CurrentActor->FindComponentByClass<UCameraComponent>();
		if (CurrentActorCamera)
		{
			CameraPawn->AttachToComponent(CurrentActorCamera, FAttachmentTransformRules::SnapToTargetIncludingScale);
			CameraPawn->SetActorRelativeLocation(FVector::ZeroVector);
			CameraPawn->SetActorRelativeRotation(FRotator::ZeroRotator);
			//set same camera settings
			CameraPawn->CopyCameraSettingsFrom(CurrentActorCamera, Camera);
			/*Camera->FieldOfView = CurrentActorCamera->FieldOfView;
			Camera->SetAspectRatio(CurrentActorCamera->AspectRatio);
			Camera->PostProcessSettings = CurrentActorCamera->PostProcessSettings;*/
		}
		/*CameraPawn->SetActorLocation(CurrentActor->GetActorLocation());
		CameraPawn->SetActorRotation(CurrentActor->GetActorRotation());
		CameraPawn->Controller->SetControlRotation(CurrentActor->GetActorRotation());*/
	}
	//Camera->AttachToComponent(CurrentActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpringArm->TargetArmLength = 0.0f;
}