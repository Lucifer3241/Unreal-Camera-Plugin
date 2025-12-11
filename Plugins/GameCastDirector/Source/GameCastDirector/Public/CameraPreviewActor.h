#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraPreviewActor.generated.h"

class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

UCLASS()
class GAMECASTDIRECTOR_API ACameraPreviewActor : public AActor
{
	GENERATED_BODY()

public:
	ACameraPreviewActor();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	/** Scene capture component used to render the preview */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Preview Camera")
	USceneCaptureComponent2D* SceneCapture;

	/** The render target this camera writes into */
	UPROPERTY(BlueprintReadOnly, Category = "Preview Camera")
	UTextureRenderTarget2D* RenderTarget;

	/** Width/Height of the render target (configurable) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview Camera")
	int32 TargetSize = 512;

	/** Sets what this preview camera should look at */
	UFUNCTION(BlueprintCallable, Category = "Preview Camera")
	void SetLookAtActor(AActor* TargetActor);

	/** Sets transform offset when following something */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview Camera")
	FVector Offset = FVector(0.f, 0.f, 100.f);

	UFUNCTION(BlueprintCallable)
	FTransform GetPreviewTransform() const { return GetActorTransform(); }


private:
	AActor* LookAtTarget = nullptr;
};
