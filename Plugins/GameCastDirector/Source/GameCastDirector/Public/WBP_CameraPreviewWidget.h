#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_CameraPreviewWidget.generated.h"

class UImage;
class UButton;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class ACameraPreviewActor;

UCLASS()
class GAMECASTDIRECTOR_API UWBP_CameraPreviewWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    // Master material for thumbnails + main preview
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
    UMaterialInterface* PreviewMaterial;

    // -------- Main Center Preview Image --------
    UPROPERTY(meta = (BindWidget))
    UImage* MainPreviewImage;

    // -------- Buttons --------
    UPROPERTY(meta = (BindWidget)) UButton* CamButton01;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton02;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton03;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton04;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton05;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton06;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton07;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton08;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton09;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton10;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton11;
    UPROPERTY(meta = (BindWidget)) UButton* CamButton12;

    // -------- Thumbnail Images --------
    UPROPERTY(meta = (BindWidget)) UImage* Cam01;
    UPROPERTY(meta = (BindWidget)) UImage* Cam02;
    UPROPERTY(meta = (BindWidget)) UImage* Cam03;
    UPROPERTY(meta = (BindWidget)) UImage* Cam04;
    UPROPERTY(meta = (BindWidget)) UImage* Cam05;
    UPROPERTY(meta = (BindWidget)) UImage* Cam06;
    UPROPERTY(meta = (BindWidget)) UImage* Cam07;
    UPROPERTY(meta = (BindWidget)) UImage* Cam08;
    UPROPERTY(meta = (BindWidget)) UImage* Cam09;
    UPROPERTY(meta = (BindWidget)) UImage* Cam10;
    UPROPERTY(meta = (BindWidget)) UImage* Cam11;
    UPROPERTY(meta = (BindWidget)) UImage* Cam12;

public:

    // Setup function called from GameMode / DirectorPawn
    UFUNCTION(BlueprintCallable)
    void BindPreviewCameras(const TArray<ACameraPreviewActor*>& PreviewActors);

    // Called when selecting a preview (index 0–11)
    UFUNCTION()
    void SelectPreview(int Index);

    // Let DirectorPawn get the RT for the selected feed
    UFUNCTION(BlueprintCallable)
    UTextureRenderTarget2D* GetSelectedRenderTarget() const;

protected:
    virtual void NativeConstruct() override;

private:

    // ---- Wrapper Click Functions (required by UMG) ----
    UFUNCTION() void ClickCam01();
    UFUNCTION() void ClickCam02();
    UFUNCTION() void ClickCam03();
    UFUNCTION() void ClickCam04();
    UFUNCTION() void ClickCam05();
    UFUNCTION() void ClickCam06();
    UFUNCTION() void ClickCam07();
    UFUNCTION() void ClickCam08();
    UFUNCTION() void ClickCam09();
    UFUNCTION() void ClickCam10();
    UFUNCTION() void ClickCam11();
    UFUNCTION() void ClickCam12();

private:

    UMaterialInstanceDynamic* ThumbnailMID[12];
    UMaterialInstanceDynamic* MainMID;

    TArray<ACameraPreviewActor*> StoredPreviewActors;

    int32 SelectedIndex = 0;
};
