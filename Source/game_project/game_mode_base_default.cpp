// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_mode_base_default.h"

Agame_mode_base_default::Agame_mode_base_default() {
    game_mode_base_level_main_menu_class = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_mode_base_level_main_menu"));
    game_mode_base_level_arena_class = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_mode_base_level_arena"));
    hud_class = LoadClass<AHUD>(world, TEXT("/Script/game_project.hud_main_menu"));
    world = GetWorld();

}
void Agame_mode_base_default::BeginPlay() {
	Super::BeginPlay();
    current_level_name = world->GetMapName();
    current_level_name.RemoveFromStart(world->StreamingLevelsPrefix);
    if (current_level_name == level_main_menu) {
        world->GetWorldSettings()->DefaultGameMode = game_mode_base_level_main_menu_class;
        UE_LOG(LogTemp, Warning, TEXT("LOL"));

    }
    else if (current_level_name == level_arena) world->GetWorldSettings()->DefaultGameMode = game_mode_base_level_arena_class;
}