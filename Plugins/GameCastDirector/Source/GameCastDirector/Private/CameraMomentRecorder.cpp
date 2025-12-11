#include "CameraMomentRecorder.h"
#include "CameraDirectorPawn.h"
#include "CameraTypeProfile.h"
#include "CameraDirectorTypes.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Stats/Stats.h"

//Performance Tracking
DECLARE_STATS_GROUP(TEXT("CameraMomentRecorder"), STATGROUP_CameraMomentRecorder, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("CameraMomentRecorder|RecordMoment"), STAT_CameraMomentRecorder_RecordMoment, STATGROUP_CameraMomentRecorder);
DECLARE_CYCLE_STAT(TEXT("CameraMomentRecorder|GoToMoment"), STAT_CameraMomentRecorder_GoToMoment, STATGROUP_CameraMomentRecorder);
DECLARE_CYCLE_STAT(TEXT("CameraMomentRecorder|GoToNextHotPoint"), STAT_CameraMomentRecorder_GoToNextHotPoint, STATGROUP_CameraMomentRecorder);
DECLARE_CYCLE_STAT(TEXT("CameraMomentRecorder|GoToPreviousHotPoint"), STAT_CameraMomentRecorder_GoToPreviousHotPoint, STATGROUP_CameraMomentRecorder);

//Memory Tracking
//LLM_DECLARE_TAG(CameraMomentRecorder);
//LLM_DEFINE_TAG(CameraMomentRecorder, "CameraMomentRecorder", false);

void UCameraMomentRecorder::RecordMoment(ACameraDirectorPawn* CameraPawn)
{
	SCOPE_CYCLE_COUNTER(STAT_CameraMomentRecorder_RecordMoment);
	//LLM_SCOPE_BYTAG(CameraMomentRecorder);

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
	SCOPE_CYCLE_COUNTER(STAT_CameraMomentRecorder_GoToMoment);
	//LLM_SCOPE_BYTAG(CameraMomentRecorder);

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
	SCOPE_CYCLE_COUNTER(STAT_CameraMomentRecorder_GoToNextHotPoint);
	//LLM_SCOPE_BYTAG(CameraMomentRecorder);

	if (!CameraPawn) return;
	if (RecordedMoments.Num() == 0) return;

	//Get the index of the next hot point, wrapping around if at the end
	CurrentHotPointIndex = (CurrentHotPointIndex + 1) % RecordedMoments.Num();
	GoToMoment(CameraPawn, CurrentHotPointIndex);
}

void UCameraMomentRecorder::GoToPreviousHotPoint(ACameraDirectorPawn* CameraPawn)
{
	SCOPE_CYCLE_COUNTER(STAT_CameraMomentRecorder_GoToPreviousHotPoint);
	//LLM_SCOPE_BYTAG(CameraMomentRecorder);

	if(!CameraPawn) return;
	if (RecordedMoments.Num() == 0) return;

	//Get the index of the previous hot point, wrapping around if at the start
	CurrentHotPointIndex = (CurrentHotPointIndex - 1 + RecordedMoments.Num()) % RecordedMoments.Num();
	GoToMoment(CameraPawn, CurrentHotPointIndex);
}
