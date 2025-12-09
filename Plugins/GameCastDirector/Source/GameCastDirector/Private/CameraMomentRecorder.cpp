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

	NewMoment.CameraType = CameraPawn->CurrentCameraType;

	//Get current profile name
	UCameraTypeProfile* CurrentProfile = CameraPawn->GetCameraTypeProfile(CameraPawn->CurrentCameraType);
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
	
	const FCameraBookmark& Moment = RecordedMoments[Index];

	//Switch camera type
	CameraPawn->ApplyCameraMode(Moment.CameraType);

	//Wait a frame to ensure camera mode is applied
	FTimerHandle TimerHandle;
	CameraPawn->GetWorldTimerManager().SetTimer(TimerHandle, [CameraPawn, Moment]()
	{
		//Set location and rotation
		CameraPawn->SetActorLocation(Moment.Location);
		CameraPawn->SetActorRotation(Moment.Rotation);

	}, 0.02f, false);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Went to Camera Moment"));
	}
}
