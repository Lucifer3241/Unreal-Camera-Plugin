#pragma once

#include "CoreMinimal.h"
#include "CameraModeBase.h"
#include "SpectatorCameraMode.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMECASTDIRECTOR_API USpectatorCameraMode : public UCameraModeBase
{
	GENERATED_BODY()

public:
	virtual void EnterMode(ACameraDirectorPawn* CameraPawn) override;
};