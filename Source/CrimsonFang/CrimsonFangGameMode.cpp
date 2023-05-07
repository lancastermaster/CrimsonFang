// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrimsonFangGameMode.h"
#include "CrimsonFangCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACrimsonFangGameMode::ACrimsonFangGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
