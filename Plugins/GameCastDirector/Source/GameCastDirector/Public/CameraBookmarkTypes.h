#pragma once

#include "CoreMinimal.h"
#include "CameraDirectorTypes.h"
#include "CameraBookmarkTypes.generated.h"

USTRUCT(BlueprintType)
struct GAMECASTDIRECTOR_API FCameraBookmark
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Bookmark")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Bookmark")
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Bookmark")
	ECameraType CameraType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Bookmark")
	FString ProfileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Bookmark")
	float TimeStamp = 0.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBookmarkCreated, const FCameraBookmark&, Bookmark);