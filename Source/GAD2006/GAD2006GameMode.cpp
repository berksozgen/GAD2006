// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAD2006GameMode.h"
#include "GAD2006Character.h"
#include "UObject/ConstructorHelpers.h"

AGAD2006GameMode::AGAD2006GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
