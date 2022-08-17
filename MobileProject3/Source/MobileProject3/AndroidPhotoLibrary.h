#pragma once

#include "CoreMinimal.h"
#include "PhotoLibrary.h"
#include "Delegates/Delegate.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#endif

//DECLARE_DELEGATE_OneParam(FOnImageSelectedFromGallery, TArray<uint8>& ImageBytes);
class AndroidPhotoLibrary : public IPhotoLibrary
{

public:

	virtual void OpenGallery() override;

#if PLATFORM_ANDROID
public:
	static struct _JNIEnv* ENV;

	//static FOnImageSelectedFromGallery ImageSelectedFromGalleryProxy;

#endif

	AndroidPhotoLibrary();
};