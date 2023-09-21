// Copyright Epic Games, Inc. All Rights Reserved.

#include "LocalMultiplayerGameMode.h"
#include "LocalMultiplayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALocalMultiplayerGameMode::ALocalMultiplayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
