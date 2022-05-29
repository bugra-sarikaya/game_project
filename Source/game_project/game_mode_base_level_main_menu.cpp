// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "game_mode_base_level_main_menu.h"

Agame_mode_base_level_main_menu::Agame_mode_base_level_main_menu() {
    PrimaryActorTick.bCanEverTick = false;
    hud_class = LoadClass<AHUD>(world, TEXT("/Script/game_project.hud_main_menu"));
    check(hud_class != nullptr);
    HUDClass = hud_class;
    world = GetWorld();
}
void Agame_mode_base_level_main_menu::BeginPlay() {
    Super::BeginPlay();
}
void Agame_mode_base_level_main_menu::StartPlay() {
	Super::StartPlay();
}
void Agame_mode_base_level_main_menu::Tick(float delta_time) {
    Super::Tick(delta_time);
}
