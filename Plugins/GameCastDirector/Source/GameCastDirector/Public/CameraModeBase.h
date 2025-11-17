#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CameraModeBase.generated.h"

class ACameraDirectorPawn;

UCLASS(Abstract, Blueprintable, EditInlineNew)
class GAMECASTDIRECTOR_API UCameraModeBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void EnterMode(ACameraDirectorPawn* CameraPawn) PURE_VIRTUAL(UCameraModeBase::EnterMode, );
};