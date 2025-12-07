#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Camera/CameraComponent.h"
#include "CameraTypeBase.generated.h"

class ACameraDirectorPawn;

UCLASS(Abstract, Blueprintable, EditInlineNew)
class GAMECASTDIRECTOR_API UCameraTypeBase : public UObject
{
	GENERATED_BODY()

public:
	//Function to enter camera mode - pure virtual
	virtual void EnterMode(ACameraDirectorPawn* CameraPawn) PURE_VIRTUAL(UCameraTypeBase::EnterMode, );
};