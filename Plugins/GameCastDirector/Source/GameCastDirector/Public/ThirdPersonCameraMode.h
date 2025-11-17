#pragma once

#include "CoreMinimal.h"
#include "CameraModeBase.h"
#include "ThirdPersonCameraMode.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class GAMECASTDIRECTOR_API UThirdPersonCameraMode : public UCameraModeBase
{
	GENERATED_BODY()

public:
	virtual void EnterMode(ACameraDirectorPawn* CameraPawn) override;
};