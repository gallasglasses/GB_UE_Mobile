// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobileProject2GameMode.h"
#include "MobileProject2Character.h"
#include "UObject/ConstructorHelpers.h"

#if PLATFORM_ANDROID
#include <MobileProject2/PugiXML/src/pugixml.hpp>
#endif


AMobileProject2GameMode::AMobileProject2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMobileProject2GameMode::BeginPlay()
{
	Super::BeginPlay();

#if PLATFORM_ANDROID

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("tree.xml");

#endif

}
