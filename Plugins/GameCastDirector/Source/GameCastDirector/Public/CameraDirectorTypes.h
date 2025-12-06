#pragma once

#include "CoreMinimal.h"
#include "CameraDirectorTypes.generated.h"

UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	None UMETA(DisplayName = "None"),
	FirstPerson UMETA(DisplayName = "First Person"),
	ThirdPerson UMETA(DisplayName = "Third Person"),
	Spectator UMETA(DisplayName = "Spectator"),
	FreeRoam UMETA(DisplayName = "Free Roam")
};