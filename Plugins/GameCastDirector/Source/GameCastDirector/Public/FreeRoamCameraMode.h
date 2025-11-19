#pragma once

#include "CoreMinimal.h"
#include "CameraModeBase.h"
#include "FreeRoamCameraMode.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMECASTDIRECTOR_API UFreeRoamCameraMode : public UCameraModeBase
{
	GENERATED_BODY()

public:
	//Function to enter into Free Roam Camera Mode
	virtual void EnterMode(ACameraDirectorPawn* CameraPawn) override;
};