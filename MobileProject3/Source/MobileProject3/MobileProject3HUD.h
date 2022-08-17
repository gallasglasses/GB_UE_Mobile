// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AndroidPhotoLibrary.h"
#include "PhotoLibrary.h"
#include "MobileProject3HUD.generated.h"

class IPhotoLibrary;
/**
 *
 */
UCLASS()
class MOBILEPROJECT3_API AMobileProject3HUD : public AHUD
{
	GENERATED_BODY()

private:
	class IPhotoLibrary* PhotoLibrary;
	//TUniquePtr<AndroidPhotoLibrary> PhotoLibrary;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void BP_OnPhotoSelected(UTexture2D* SelectedPhoto);

	void InitMobileLibrary();

	UFUNCTION(BlueprintCallable)
	void OpenMobileGallery();

	void OnPhotoSelected(TArray<uint8>& ImageBytes);

	UTexture2D* LoadImageFromBytes(const TArray<uint8>& ImageBytes);
};