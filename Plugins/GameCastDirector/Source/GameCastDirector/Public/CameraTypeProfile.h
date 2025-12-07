#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CameraTypeProfile.generated.h"

UCLASS(BlueprintType)
class UCameraTypeProfile : public UDataAsset
{
	GENERATED_BODY()

public:

	//Spring Arm settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|SpringArm")
	float TargetArmLength = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|SpringArm")
	bool bUsePawnControlRotation = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|SpringArm")
	bool bAllowMovement = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|SpringArm")
	bool bAllowLook = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|SpringArm")
	bool bEnableCollision = true;

	//Mode specific settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|ModeSpecific")
	float FieldOfView = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|ModeSpecific")
	float CameraLagSpeed = 10.f;
};