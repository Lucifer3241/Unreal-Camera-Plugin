#include "WBP_CameraPreviewWidget.h"
#include "CameraDirectorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CameraPreviewActor.h"
#include "Engine/TextureRenderTarget2D.h"

void UWBP_CameraPreviewWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // ---- Bind Buttons ----
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

        ThumbnailMID[i] = UMaterialInstanceDynamic::Create(PreviewMaterial, this);
        ThumbnailMID[i]->SetTextureParameterValue("PreviewTexture", Preview->RenderTarget);

        Thumbs[i]->SetBrushFromMaterial(ThumbnailMID[i]);
    }

    // Create MID for main preview
    MainMID = UMaterialInstanceDynamic::Create(PreviewMaterial, this);
    MainPreviewImage->SetBrushFromMaterial(MainMID);


    // Default main preview = Cam01
    SelectPreview(0);
}

void UWBP_CameraPreviewWidget::SelectPreview(int Index)
{
    if (!StoredPreviewActors.IsValidIndex(Index))
        return;

    SelectedIndex = Index;

    ACameraPreviewActor* Preview = StoredPreviewActors[Index];
    if (!Preview)
        return;

    // --- Get Director Pawn ---
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    ACameraDirectorPawn* Director = Cast<ACameraDirectorPawn>(PC->GetPawn());
    if (!Director) return;

    // --- MOVE DIRECTOR PAWN TO PREVIEW CAM LOCATION ---
    Director->SetActorLocation(Preview->GetActorLocation());
    Director->SetActorRotation(Preview->GetActorRotation());

    // Make the camera match
    Director->GetSpringArmComponent()->SetRelativeRotation(FRotator::ZeroRotator);
    Director->GetCameraComponent()->SetRelativeRotation(FRotator::ZeroRotator);

    // --- MAIN PREVIEW SHOULD SHOW DIRECTOR'S RENDER TARGET ---
    if (!MainMID)
    {
        MainMID = UMaterialInstanceDynamic::Create(PreviewMaterial, this);
        MainPreviewImage->SetBrushFromMaterial(MainMID);
    }

    MainMID->SetTextureParameterValue("PreviewTexture", Director->GetRenderTarget());
}



UTextureRenderTarget2D* UWBP_CameraPreviewWidget::GetSelectedRenderTarget() const
{
    if (!StoredPreviewActors.IsValidIndex(SelectedIndex))
        return nullptr;

    ACameraPreviewActor* Preview = StoredPreviewActors[SelectedIndex];
    return Preview ? Preview->RenderTarget : nullptr;
}

// ---- Wrapper Click Functions ----
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
