#include "CameraMomentRecorder.h"
#include "CameraDirectorPawn.h"
#include "CameraTypeProfile.h"
#include "CameraDirectorTypes.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

void UCameraMomentRecorder::RecordMoment(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;

	FCameraBookmark NewMoment;
	NewMoment.Location = Camera->GetComponentLocation();
	NewMoment.Rotation = Camera->GetComponentRotation();

	NewMoment.CameraType = ECameraType::Spectator;

	//Get current profile name
	UCameraTypeProfile* CurrentProfile = CameraPawn->GetCameraTypeProfile(NewMoment.CameraType);
	if(!CurrentProfile)
	{
		NewMoment.ProfileName = "Default";
	}
	else
	{
		NewMoment.ProfileName = CurrentProfile->GetName();
	}

	NewMoment.TimeStamp = CameraPawn->GetWorld()->GetTimeSeconds();
	
	RecordedMoments.Add(NewMoment);
	OnMomentRecorded.Broadcast(NewMoment);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Recorded Camera Moment"));
	}
}

void UCameraMomentRecorder::GoToMoment(ACameraDirectorPawn* CameraPawn, int32 Index)
{
	if (!CameraPawn) return;
	
	if (!RecordedMoments.IsValidIndex(Index)) return;

	UCameraComponent* Camera = CameraPawn->GetCameraComponent();
	if (!Camera) return;
	
	const FCameraBookmark& Moment = RecordedMoments[Index];

	//Switch camera type
	//CameraPawn->ApplyCameraMode(Moment.CameraType);
	CameraPawn->SetCameraLockedToMoments(true);

	//Wait a frame to ensure camera mode is applied
	FTimerHandle TimerHandle;
	CameraPawn->GetWorldTimerManager().SetTimer(TimerHandle, [Camera, Moment]()
	{
		//Set location and rotation
		Camera->SetWorldLocation(Moment.Location);
		Camera->SetWorldRotation(Moment.Rotation);

	}, 0.02f, false);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Went to Camera Moment"));
	}
}

void UCameraMomentRecorder::GoToNextHotPoint(ACameraDirectorPawn* CameraPawn)
{
	if (!CameraPawn) return;
	if (RecordedMoments.Num() == 0) return;

	//Get the index of the next hot point, wrapping around if at the end
	CurrentHotPointIndex = (CurrentHotPointIndex + 1) % RecordedMoments.Num();
	GoToMoment(CameraPawn, CurrentHotPointIndex);
}

void UCameraMomentRecorder::GoToPreviousHotPoint(ACameraDirectorPawn* CameraPawn)
{
	if(!CameraPawn) return;
	if (RecordedMoments.Num() == 0) return;

	//Get the index of the previous hot point, wrapping around if at the start
	CurrentHotPointIndex = (CurrentHotPointIndex - 1 + RecordedMoments.Num()) % RecordedMoments.Num();
	GoToMoment(CameraPawn, CurrentHotPointIndex);
}
