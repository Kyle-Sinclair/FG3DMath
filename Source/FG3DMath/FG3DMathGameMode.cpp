// Copyright Epic Games, Inc. All Rights Reserved.

#include "FG3DMathGameMode.h"
#include "FG3DMathCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFG3DMathGameMode::AFG3DMathGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_FGMathCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
