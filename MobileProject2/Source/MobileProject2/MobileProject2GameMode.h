// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MobileProject2GameMode.generated.h"


UCLASS(minimalapi)
class AMobileProject2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMobileProject2GameMode();

protected:
	virtual void BeginPlay() override;
};



