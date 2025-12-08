#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CameraTypeBase.generated.h"

class ACameraDirectorPawn;

UCLASS(Abstract, Blueprintable)
class GAMECASTDIRECTOR_API UCameraTypeBase : public UObject
{
	GENERATED_BODY()

public:
	//Function to enter camera mode
	virtual void CameraTypeLifecycle(ACameraDirectorPawn* CameraPawn) final;

	//Attach camera to pawn - pure virtual
	virtual void AttachCamera(ACameraDirectorPawn* CameraPawn) PURE_VIRTUAL(UCameraTypeBase::AttachCamera, ) ;

	//Custom behavior per camera mode - pure virtual
	virtual void CustomBehavior(ACameraDirectorPawn* CameraPawn) PURE_VIRTUAL(UCameraTypeBase::CustomBehavior, );

protected:
	//Apply camera settings from profile
	void ApplyCameraSettingsFromProfile(ACameraDirectorPawn* CameraPawn);

};