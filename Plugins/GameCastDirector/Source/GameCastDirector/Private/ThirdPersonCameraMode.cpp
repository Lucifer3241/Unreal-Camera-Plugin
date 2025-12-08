#include "ThirdPersonCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraTypeProfile.h"

void UThirdPersonCameraMode::AttachCamera(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	//if (CameraPawn->GetOldActor() == CameraPawn->GetCurrentActor() && CameraPawn->CurrentCameraType == ECameraType::ThirdPerson)
	//{
	//	//already in this mode with same actor
	//	return;
	//}

	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	if (!SpringArm) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;
	CameraPawn->CurrentCameraType = ECameraType::ThirdPerson;

	AActor* CurrentActor = CameraPawn->GetCurrentActor();
	if (!CurrentActor) return;

	UCapsuleComponent* CapsuleComp = CurrentActor->FindComponentByClass<UCapsuleComponent>();
	if (CapsuleComp)
	{
		CapsuleComp->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	}

	if (USkeletalMeshComponent* SkeletalMesh = CurrentActor->FindComponentByClass<USkeletalMeshComponent>())
	{
		SkeletalMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	}

	SpringArm->AttachToComponent(CurrentActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//get controller
	AController* Controller = CameraPawn->GetController();
	if (Controller)
	{
		Controller->SetControlRotation(FRotator::ZeroRotator);
	}
}

void UThirdPersonCameraMode::CustomBehavior(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	//Custom behavior for Third Person Camera Mode can be added here
	CameraPawn->bUseControllerRotationPitch = false;
	CameraPawn->bUseControllerRotationYaw = false;

	CameraPawn->SetCollisionEnabled(false);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Third Person"));
		//print CameraPawn current actor name
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Current Actor: %s"), *CameraPawn->GetCurrentActor()->GetName()));
	}
}