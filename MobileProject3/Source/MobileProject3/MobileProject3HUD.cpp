// Fill out your copyright notice in the Description page of Project Settings.

#include "MobileProject3HUD.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"

//#if PLATFORM_ANDROID
//#include "Android/AndroidJNI.h"
//#include "Android/AndroidApplication.h"
//#endif

void AMobileProject3HUD::BeginPlay()
{
	Super::BeginPlay();

	InitMobileLibrary();
}

void AMobileProject3HUD::InitMobileLibrary()
{
#if PLATFORM_ANDROID
	PhotoLibrary = new AndroidPhotoLibrary();
	//PhotoLibrary = MakeUnique<AndroidPhotoLibrary>();
#endif
}

void AMobileProject3HUD::OpenMobileGallery()
{
	if (PhotoLibrary)
	{
		PhotoLibrary->OnImageSelected.BindUObject(this, &AMobileProject3HUD::OnPhotoSelected);
		PhotoLibrary->OpenGallery();
	}
}

void AMobileProject3HUD::OnPhotoSelected(TArray<uint8>& ImageBytes)
{
	auto Length = ImageBytes.Num();

	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			UTexture2D* ImportedTexture = LoadImageFromBytes(ImageBytes);
			BP_OnPhotoSelected(ImportedTexture);
		});
}

UTexture2D* AMobileProject3HUD::LoadImageFromBytes(const TArray<uint8>& ImageBytes)
{
	auto& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(ImageBytes.GetData(), ImageBytes.Num());
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageBytes.GetData(), ImageBytes.Num()))
	{
		TArray<uint8> UncompressedBGRA;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			FName UniqueName = MakeUniqueObjectName(nullptr, UTexture2D::StaticClass());
			UTexture2D* NewTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), EPixelFormat::PF_B8G8R8A8, UniqueName);

			if (!NewTexture) return nullptr;
			if (UTexture2D* ImageTexture = Cast<UTexture2D>(NewTexture))
			{
				void* TextureData = ImageTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);//locking the data its multithreaded
				FMemory::Memmove(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
				//FMemory::Memzero((void *)PixelData.GetData(), PixelData.Num() * sizeof(uint8));
				ImageTexture->PlatformData->Mips[0].BulkData.Unlock();
				ImageTexture->UpdateResource();
			}

			return NewTexture;
		}
	}

	return nullptr;
}