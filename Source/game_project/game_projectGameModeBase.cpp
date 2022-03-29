// Copyright Epic Games, Inc. All Rights Reserved.


#include "game_projectGameModeBase.h"
Agame_projectGameModeBase::Agame_projectGameModeBase() {
    static ConstructorHelpers::FClassFinder<APawn> pawn_class(TEXT("/Script/game_project.paper_player"));
    if (pawn_class.Class != NULL) DefaultPawnClass = pawn_class.Class;
    static ConstructorHelpers::FClassFinder<AHUD> hud_class(TEXT("/Script/game_project.combat_hud"));
    if (hud_class.Class != NULL) HUDClass = hud_class.Class;
}
void Agame_projectGameModeBase::StartPlay() {
	Super::StartPlay();
	check(GEngine != nullptr);
}