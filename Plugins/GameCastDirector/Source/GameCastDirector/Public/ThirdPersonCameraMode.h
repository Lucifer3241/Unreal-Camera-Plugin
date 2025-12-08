#pragma once

#include "CoreMinimal.h"
#include "CameraTypeBase.h"
#include "ThirdPersonCameraMode.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMECASTDIRECTOR_API UThirdPersonCameraMode : public UCameraTypeBase
{
	GENERATED_BODY()

public:
	//Function to enter into Third Person Camera Mode
	virtual void AttachCamera(ACameraDirectorPawn* CameraPawn) override;

	virtual void CustomBehavior(ACameraDirectorPawn* CameraPawn) override;
};