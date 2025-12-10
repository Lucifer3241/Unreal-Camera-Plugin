#include "SpectatorCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraMomentRecorder.h"

void USpectatorCameraMode::AttachCamera(ACameraDirectorPawn* CameraPawn)
{
	//if (!CameraPawn) return;

	//USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	//if (!SpringArm) return;

	//UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	//if (!Camera) return;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Mode: Spectator"));
	//Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//SpringArm->TargetArmLength = 600.0f;
	//SpringArm->bUsePawnControlRotation = true;
	//CameraPawn->bUseControllerRotationYaw = false;
	//
	////Allow look but not movement in spectator mode
	//CameraPawn->SetAllowLook(true);
	//CameraPawn->SetAllowMovement(false);

	//AActor* CurrentActor = CameraPawn->GetCurrentActor();
	//// Set CameraPawn location and rotation to match CurrentActor
	//if (CurrentActor)
	//{
	//	CameraPawn->SetActorLocation(CurrentActor->GetActorLocation());
	//	CameraPawn->SetActorRotation(CurrentActor->GetActorRotation());
	//}

	//if (!CameraPawn) return;

	//UCameraMomentRecorder* MomentRecorder = CameraPawn->GetMomentRecorder();
	//if (!MomentRecorder) return;

	//CameraPawn->SetCameraLockedToMoments(true);

	//if(MomentRecorder->GetRecordedMomentCount() == 0)
	//{
	//	//No moments recorded, cannot enter Spectator mode
	//	if (GEngine)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Spectator Camera Mode requires recorded moments."));
	//	}
	//	return;
	//}
	//MomentRecorder->GoToMoment(CameraPawn, 0);	
}

void USpectatorCameraMode::CustomBehavior(ACameraDirectorPawn* CameraPawn)
{
	//if (!CameraPawn) return;

	////Custom behavior for Spectator Camera Mode can be added here
	//UCameraMomentRecorder* MomentRecorder = CameraPawn->GetMomentRecorder();
	//if (!MomentRecorder) return;
}
