#pragma once

#include "CoreMinimal.h"
#include "CameraTypeBase.h"
#include "SpectatorCameraMode.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMECASTDIRECTOR_API USpectatorCameraMode : public UCameraTypeBase
{
	GENERATED_BODY()

public:
	//Function to enter into Spectator Camera Mode
	virtual void EnterMode(ACameraDirectorPawn* CameraPawn) override;
};