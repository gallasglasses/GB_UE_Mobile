#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PhotoLibrary.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UPhotoLibrary : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE_OneParam(FOnImageSelected, TArray<uint8>&);

class IPhotoLibrary
{
	GENERATED_BODY()
public:
	virtual void OpenGallery() = 0;

	FOnImageSelected OnImageSelected;
};