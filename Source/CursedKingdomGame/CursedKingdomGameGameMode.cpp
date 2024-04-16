// Copyright Epic Games, Inc. All Rights Reserved.

#include "CursedKingdomGameGameMode.h"
#include "CursedKingdomGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACursedKingdomGameGameMode::ACursedKingdomGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
