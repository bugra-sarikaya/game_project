// Copyright Epic Games, Inc. All Rights Reserved.


#include "game_projectGameModeBase.h"

void Agame_projectGameModeBase::StartPlay() {
	Super::StartPlay();
	check(GEngine != nullptr);
	//Display a debug message for five seconds.
	//The -1 "Key" value argument prevents the message from begin updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is game_projectGameMode!"));
}