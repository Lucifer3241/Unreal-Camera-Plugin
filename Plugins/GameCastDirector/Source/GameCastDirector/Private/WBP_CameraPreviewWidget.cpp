#include "WBP_CameraPreviewWidget.h"
#include "CameraDirectorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CameraPreviewActor.h"
#include "Engine/TextureRenderTarget2D.h"

// --------------------
// NativeConstruct
// --------------------
void UWBP_CameraPreviewWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind buttons function wrappers
    if (CamButton01) CamButton01->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam01);
    if (CamButton02) CamButton02->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam02);
    if (CamButton03) CamButton03->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam03);
    if (CamButton04) CamButton04->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam04);
    if (CamButton05) CamButton05->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam05);
    if (CamButton06) CamButton06->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam06);
    if (CamButton07) CamButton07->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam07);
    if (CamButton08) CamButton08->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam08);
    if (CamButton09) CamButton09->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam09);
    if (CamButton10) CamButton10->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam10);
    if (CamButton11) CamButton11->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam11);
    if (CamButton12) CamButton12->OnClicked.AddDynamic(this, &UWBP_CameraPreviewWidget::ClickCam12);
}

// --------------------
// Bind Preview Actors
// --------------------
void UWBP_CameraPreviewWidget::BindPreviewCameras(const TArray<ACameraPreviewActor*>& PreviewActors)
{
    StoredPreviewActors = PreviewActors;

    UImage* Thumbs[12] =
    {
        Cam01, Cam02, Cam03, Cam04, Cam05, Cam06,
        Cam07, Cam08, Cam09, Cam10, Cam11, Cam12
    };

    for (int i = 0; i < 12; i++)
    {
        if (!Thumbs[i] || !StoredPreviewActors.IsValidIndex(i))
            continue;

        ACameraPreviewActor* Preview = StoredPreviewActors[i];
        if (!Preview || !Preview->RenderTarget)
            continue;

        // Create thumbnail MID
        ThumbnailMID[i] = UMaterialInstanceDynamic::Create(PreviewMaterial, this);
        ThumbnailMID[i]->SetTextureParameterValue("PreviewTexture", Preview->RenderTarget);

        Thumbs[i]->SetBrushFromMaterial(ThumbnailMID[i]);
    }

    // Default selection
    SelectPreview(0);
}

UTextureRenderTarget2D* UWBP_CameraPreviewWidget::GetSelectedRenderTarget() const
{
    if (!StoredPreviewActors.IsValidIndex(SelectedIndex))
        return nullptr;

    ACameraPreviewActor* Preview = StoredPreviewActors[SelectedIndex];
    return Preview ? Preview->RenderTarget : nullptr;
}


// --------------------
// Select Preview (UPDATED)
// --------------------
void UWBP_CameraPreviewWidget::SelectPreview(int Index)
{
    if (!StoredPreviewActors.IsValidIndex(Index)) return;

    SelectedIndex = Index;

    ACameraPreviewActor* Preview = StoredPreviewActors[Index];
    if (!Preview) return;

    // MAIN PREVIEW IMAGE
    if (MainMID)
    {
        MainMID->SetTextureParameterValue(TEXT("PreviewTexture"), Preview->RenderTarget);
        MainPreviewImage->SetBrushFromMaterial(MainMID);
    }

    // MOVE DIRECTOR PAWN
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    ACameraDirectorPawn* Director = Cast<ACameraDirectorPawn>(PC->GetPawn());
    if (Director)
        Director->MoveToPreviewTransform(Preview->GetActorTransform());

    // MOVE ALL PLAYER CHARACTERS TO MATCH PREVIEW LOCATION + ROTATION
    UWorld* World = GetWorld();
    if (!World) return;

    FVector  PreviewLoc = Preview->GetActorLocation();
    FRotator PreviewRot = Preview->GetActorRotation();

    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PCX = It->Get();
        if (!PCX) continue;

        APawn* P = PCX->GetPawn();
        if (!P) continue;

        // move pawn
        P->SetActorLocationAndRotation(
            PreviewLoc,
            PreviewRot,
            false,
            nullptr,
            ETeleportType::TeleportPhysics);

        // sync controller
        PCX->SetControlRotation(PreviewRot);
    }
}


// --------------------
// Click Wrappers
// --------------------
void UWBP_CameraPreviewWidget::ClickCam01() { SelectPreview(0); }
void UWBP_CameraPreviewWidget::ClickCam02() { SelectPreview(1); }
void UWBP_CameraPreviewWidget::ClickCam03() { SelectPreview(2); }
void UWBP_CameraPreviewWidget::ClickCam04() { SelectPreview(3); }
void UWBP_CameraPreviewWidget::ClickCam05() { SelectPreview(4); }
void UWBP_CameraPreviewWidget::ClickCam06() { SelectPreview(5); }
void UWBP_CameraPreviewWidget::ClickCam07() { SelectPreview(6); }
void UWBP_CameraPreviewWidget::ClickCam08() { SelectPreview(7); }
void UWBP_CameraPreviewWidget::ClickCam09() { SelectPreview(8); }
void UWBP_CameraPreviewWidget::ClickCam10() { SelectPreview(9); }
void UWBP_CameraPreviewWidget::ClickCam11() { SelectPreview(10); }
void UWBP_CameraPreviewWidget::ClickCam12() { SelectPreview(11); }