// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_mode_base_level_main_menu.h"

Agame_mode_base_level_main_menu::Agame_mode_base_level_main_menu() {
    PrimaryActorTick.bCanEverTick = true;
    hud_class = LoadClass<AHUD>(world, TEXT("/Script/game_project.main_menu_hud"));
    check(hud_class != nullptr);
    //static ConstructorHelpers::FClassFinder<APawn> pawn_class(TEXT("/Script/game_project.paper_player"));
    //if (pawn_class.Class != NULL) DefaultPawnClass = pawn_class.Class;
    //static ConstructorHelpers::FClassFinder<AHUD> hud_class(TEXT("/Script/game_project.combat_hud"));
    //if (hud_class.Class != NULL) HUDClass = hud_class.Class;
    HUDClass = hud_class;
    world = GetWorld();
}
void Agame_mode_base_level_main_menu::BeginPlay() {
    Super::BeginPlay();
    //FString level_name = GetWorld()->GetMapName();
    //level_name.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    //GetWorld()->ServerTravel(level_name, false);
    

}
void Agame_mode_base_level_main_menu::StartPlay() {
	Super::StartPlay();
}
void Agame_mode_base_level_main_menu::Tick(float delta_time) {
    Super::Tick(delta_time);
    //FString level_name = GetWorld()->GetMapName();
    //FString(GetWorld()->GetMapName()).RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    //level_name.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    //UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(level_name));
    //if (level_name == TEXT("test_map")) {

        //UE_LOG(LogTemp, Warning, TEXT("LOL"), );
    //}

}
