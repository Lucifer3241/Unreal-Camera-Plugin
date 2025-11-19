#pragma once

#include "CoreMinimal.h"
#include "CameraModeBase.h"
#include "FirstPersonCameraMode.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMECASTDIRECTOR_API UFirstPersonCameraMode : public UCameraModeBase
{
	GENERATED_BODY()

public:
	// Function to enter into First Person Camera Mode
	virtual void EnterMode(ACameraDirectorPawn* CameraPawn) override;
};