// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobileProject3GameMode.h"
#include "MobileProject3Character.h"
#include "UObject/ConstructorHelpers.h"

AMobileProject3GameMode::AMobileProject3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
