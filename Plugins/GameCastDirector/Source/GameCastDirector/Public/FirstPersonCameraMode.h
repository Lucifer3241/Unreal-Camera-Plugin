#pragma once

#include "CoreMinimal.h"
#include "CameraTypeBase.h"
#include "FirstPersonCameraMode.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMECASTDIRECTOR_API UFirstPersonCameraMode : public UCameraTypeBase
{
	GENERATED_BODY()

public:
	// Function to enter into First Person Camera Mode
	virtual void EnterMode(ACameraDirectorPawn* CameraPawn) override;
};