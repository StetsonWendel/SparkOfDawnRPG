// Copyright Epic Games, Inc. All Rights Reserved.

#include "SparkOfDawnRPGGameMode.h"
#include "SparkOfDawnRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASparkOfDawnRPGGameMode::ASparkOfDawnRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
