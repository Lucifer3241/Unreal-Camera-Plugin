#pragma once

#include "CoreMinimal.h"
#include "CameraTypeBase.h"
#include "FreeRoamCameraMode.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMECASTDIRECTOR_API UFreeRoamCameraMode : public UCameraTypeBase
{
	GENERATED_BODY()

public:
	//Function to enter into Free Roam Camera Mode
	virtual void AttachCamera(ACameraDirectorPawn* CameraPawn) override;

	virtual void CustomBehavior(ACameraDirectorPawn* CameraPawn) override;
};