// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_projectGameModeBase.h"
Agame_projectGameModeBase::Agame_projectGameModeBase() {
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FClassFinder<APawn> pawn_class(TEXT("/Script/game_project.paper_player"));
    if (pawn_class.Class != NULL) DefaultPawnClass = pawn_class.Class;
    static ConstructorHelpers::FClassFinder<AHUD> hud_class(TEXT("/Script/game_project.combat_hud"));
    if (hud_class.Class != NULL) HUDClass = hud_class.Class;
}
void Agame_projectGameModeBase::StartPlay() {
	Super::StartPlay();
}
void Agame_projectGameModeBase::BeginPlay() {
    Super::BeginPlay();
    FString level_name = GetWorld()->GetMapName();
    level_name.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    //GetWorld()->ServerTravel(level_name, false);

}
void Agame_projectGameModeBase::Tick(float delta_time) {
    Super::Tick(delta_time);
    //FString level_name = GetWorld()->GetMapName();
    //FString(GetWorld()->GetMapName()).RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    //level_name.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    //UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(level_name));
    //if (level_name == TEXT("test_map")) {

        //UE_LOG(LogTemp, Warning, TEXT("LOL"), );
    //}

}
