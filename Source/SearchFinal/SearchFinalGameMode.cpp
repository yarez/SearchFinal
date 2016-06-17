// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SearchFinal.h"
#include "SearchFinalGameMode.h"
#include "SearchFinalHUD.h"
#include "SearchFinalCharacter.h"

ASearchFinalGameMode::ASearchFinalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASearchFinalHUD::StaticClass();
}
