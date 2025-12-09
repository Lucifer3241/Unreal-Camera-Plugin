#pragma once

#include "CoreMinimal.h"
#include "CameraBookmarkTypes.h"
#include "CameraMomentRecorder.generated.h"

class ACameraDirectorPawn;

UCLASS(Blueprintable)
class GAMECASTDIRECTOR_API UCameraMomentRecorder : public UObject
{
	GENERATED_BODY()

public:

	//Record a camera moment
	UFUNCTION(BlueprintCallable, Category = "Camera|MomentRecorder")
	void RecordMoment(ACameraDirectorPawn* CameraPawn);

	//Move the pawn to a recorded moment
	UFUNCTION(BlueprintCallable, Category = "Camera|MomentRecorder")
	void GoToMoment(ACameraDirectorPawn* CameraPawn, int32 Index);

protected:

	//Delegate for when a moment is recorded
	UPROPERTY(BlueprintAssignable, Category = "Camera|MomentRecorder")
	FOnBookmarkCreated OnMomentRecorded;

	//Store camera moments
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|MomentRecorder")
	TArray<FCameraBookmark> RecordedMoments;
};