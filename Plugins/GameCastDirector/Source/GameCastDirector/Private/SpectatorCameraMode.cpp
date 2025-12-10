#include "SpectatorCameraMode.h"
#include "CameraDirectorPawn.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraMomentRecorder.h"

void USpectatorCameraMode::AttachCamera(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	UCameraMomentRecorder* MomentRecorder = CameraPawn->GetMomentRecorder();
	if (!MomentRecorder) return;

	if(MomentRecorder->GetRecordedMomentCount() == 0)
	{
		//No moments recorded, cannot enter Spectator mode
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Spectator Camera Mode requires recorded moments."));
		}
		return;
	}

	//Lock camera to recorded moments and go to the first moment
	//CameraPawn->SetCameraLockedToMoments(true);
	MomentRecorder->GoToNextHotPoint(CameraPawn);
}

void USpectatorCameraMode::CustomBehavior(ACameraDirectorPawn* CameraPawn)
{

}
