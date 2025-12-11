#include "CameraPreviewActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetMathLibrary.h"

ACameraPreviewActor::ACameraPreviewActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create SceneCapture component
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	RootComponent = SceneCapture;

	SceneCapture->bCaptureEveryFrame = false;     // we manually update each tick
	SceneCapture->bCaptureOnMovement = false;
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
}

void ACameraPreviewActor::BeginPlay()
{
	Super::BeginPlay();

	// Create unique render target
	RenderTarget = NewObject<UTextureRenderTarget2D>(this);
	RenderTarget->InitAutoFormat(TargetSize, TargetSize);
	RenderTarget->ClearColor = FLinearColor::Black; // optional
	RenderTarget->UpdateResource();

	SceneCapture->TextureTarget = RenderTarget;
}

void ACameraPreviewActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Smoothly rotate to face LookAtTarget
	if (LookAtTarget)
	{
		FVector CamPos = GetActorLocation();
		FVector TargetPos = LookAtTarget->GetActorLocation() + Offset;

		FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(CamPos, TargetPos);

		SetActorRotation(LookRot);
	}

	// Render a frame
	if (SceneCapture)
	{
		SceneCapture->CaptureScene();
	}
}

void ACameraPreviewActor::SetLookAtActor(AActor* TargetActor)
{
	LookAtTarget = TargetActor;
}
