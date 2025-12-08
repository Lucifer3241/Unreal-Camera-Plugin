#include "CameraTypeBase.h"
#include "CameraDirectorPawn.h"
#include "CameraTypeProfile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

void UCameraTypeBase::CameraTypeLifecycle(ACameraDirectorPawn* CameraPawn)
{
	if(!CameraPawn) return;

	//Apply camera settings from profile
	ApplyCameraSettingsFromProfile(CameraPawn);

	//Attach camera
	AttachCamera(CameraPawn);

	//Custom behavior
	CustomBehavior(CameraPawn);
}

void UCameraTypeBase::ApplyCameraSettingsFromProfile(ACameraDirectorPawn* CameraPawn)
{
	if(!CameraPawn) return;
	UCameraTypeProfile* CameraProfile = CameraPawn->GetCameraTypeProfile(CameraPawn->CurrentCameraType);
	
	if(!CameraProfile) return;
	USpringArmComponent* SpringArm = CameraPawn->GetSpringArmComponent();
	
	if(SpringArm)
	{
		SpringArm->TargetArmLength = CameraProfile->TargetArmLength;
		SpringArm->bUsePawnControlRotation = CameraProfile->bUsePawnControlRotation;
		SpringArm->bDoCollisionTest = CameraProfile->bEnableCollision;
	}
	
	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if(Camera)
	{
		Camera->FieldOfView = CameraProfile->FieldOfView;
	}

	CameraPawn->SetAllowLook(CameraProfile->bAllowLook);
	CameraPawn->SetAllowMovement(CameraProfile->bAllowMovement);
}
