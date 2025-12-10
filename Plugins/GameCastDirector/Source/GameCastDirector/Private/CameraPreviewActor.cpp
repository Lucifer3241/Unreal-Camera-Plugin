#include "CameraPreviewActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetMathLibrary.h"

ACameraPreviewActor::ACameraPreviewActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Scene Capture Component
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	RootComponent = SceneCapture;

	// Default settings
	SceneCapture->bCaptureEveryFrame = false;       // We manually update
	SceneCapture->bCaptureOnMovement = true;
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
}

void ACameraPreviewActor::BeginPlay()
{
	Super::BeginPlay();

	// Create unique render target
	RenderTarget = NewObject<UTextureRenderTarget2D>(this);
	RenderTarget->InitAutoFormat(TargetSize, TargetSize);
	RenderTarget->UpdateResource();

	SceneCapture->TextureTarget = RenderTarget;
}

void ACameraPreviewActor::SetLookAtActor(AActor* TargetActor)
{
	LookAtTarget = TargetActor;
}

void ACameraPreviewActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LookAtTarget)
	{
		// Smoothly rotate the preview camera to face the target
		FVector StartLocation = GetActorLocation();
		FVector TargetLocation = LookAtTarget->GetActorLocation() + Offset;

		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

		SetActorRotation(LookRotation);
	}

	// Render a frame
	if (SceneCapture)
	{
		SceneCapture->CaptureScene();
	}
}
