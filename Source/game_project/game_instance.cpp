// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "game_instance.h"

Ugame_instance::Ugame_instance() {
    game_mode_base_level_main_menu_class= LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_mode_base_level_main_menu"));
    game_mode_base_level_arena_class = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_mode_base_level_arena"));
    game_user_settings = const_cast<UGameUserSettings*>(GetDefault<UGameUserSettings>());
}
void Ugame_instance::Init() {
	Super::Init();
	world = GetWorld();
    if (game_user_settings) {
        game_user_settings->SetScreenResolution(game_user_settings->GetDesktopResolution());
        game_user_settings->SetFullscreenMode(EWindowMode::Fullscreen);
        //game_user_settings->SetDynamicResolutionEnabled(true);
        game_user_settings->SetVSyncEnabled(true);
        game_user_settings->SetAntiAliasingQuality(0);
        game_user_settings->ApplySettings(false);
    }
    current_level_name = world->GetMapName();
    current_level_name.RemoveFromStart(world->StreamingLevelsPrefix);
    next_level_name = "level_main_menu";
    options = "?Game=/Script/game_project.game_mode_base_level_main_menu";
    if (current_level_name == next_level_name.ToString()) world->GetWorldSettings()->DefaultGameMode = game_mode_base_level_main_menu_class;
    else UGameplayStatics::OpenLevel(world, next_level_name, false, options);
}
void Ugame_instance::Shutdown() {
	Super::Shutdown();
}
void Ugame_instance::StartGameInstance() {
	Super::StartGameInstance();
}