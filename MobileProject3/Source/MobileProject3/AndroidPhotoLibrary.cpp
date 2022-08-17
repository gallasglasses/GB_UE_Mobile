#include "AndroidPhotoLibrary.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#define DECLARE_JAVA_METHOD(name) static jmethodID name;

DECLARE_JAVA_METHOD(AndroidThunkJava_OpenGallery);

//#endif

#define INIT_JAVA_METHOD(name, signature) \
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true)) { \
	name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID,	#name, signature, false); \
			check(name != NULL); \
	} else {\
			check(0); \
	}

DECLARE_DELEGATE_OneParam(FOnImageSelectedFromGallery, TArray<uint8>&);

static FOnImageSelectedFromGallery ImageSelectedFromGalleryProxy;

//#if PLATFORM_ANDROID
extern "C"
{
	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_onImageSelected(JNIEnv* jni, jclass clazz, jbyteArray imageBytes)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
			{
				if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
				{
					jbyte* dataPtr = Env->GetByteArrayElements(imageBytes, NULL);
					jsize len = Env->GetArrayLength(imageBytes);
					TArray<uint8> result((uint8*)dataPtr, (int32)len);
					/*AndroidPhotoLibrary::*/ImageSelectedFromGalleryProxy.ExecuteIfBound(result);
				}
			}
		);
	}
}
//#endif

#endif

AndroidPhotoLibrary::AndroidPhotoLibrary()
{
	#if PLATFORM_ANDROID
		ImageSelectedFromGalleryProxy = OnImageSelected;
		INIT_JAVA_METHOD(AndroidThunkJava_OpenGallery, "()V");
	#endif
}

void AndroidPhotoLibrary::OpenGallery()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_OpenGallery);
	}
#endif
}

//#if PLATFORM_ANDROID
//jmethodID AndroidPhotoLibrary::AndroidThunkJava_OpenGallery = NULL;
//#endif

//FOnImageSelectedFromGallery AndroidPhotoLibrary::ImageSelectedFromGalleryProxy;
