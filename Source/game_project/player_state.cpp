// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "player_state.h"
#include "game_state_base.h"
#include "game_mode_base_level_arena.h"

Aplayer_state::Aplayer_state() {
	world = GetWorld();
	PrimaryActorTick.bCanEverTick = true;
}
void Aplayer_state::BeginPlay() {
	Super::BeginPlay();
	player_score = 0;
	player_controller = UGameplayStatics::GetPlayerController(world, 0);
	paper_player = Cast<Apaper_player>(player_controller->GetPawn());
	if (paper_player) player_time_start = paper_player->time_start;
}
void Aplayer_state::Tick(float delta_time) {
	Super::Tick(delta_time);
	paper_player = Cast<Apaper_player>(player_controller->GetPawn());
	if (paper_player) {
		player_health = paper_player->health;
		player_time_end = paper_player->time_end;
	}
	else Destroy();
	player_time = player_time_end - player_time_start;
}
void Aplayer_state::EndPlay(EEndPlayReason::Type reason) {
	Super::EndPlay(reason);
	if (reason == EEndPlayReason::Destroyed) {
		game_state_base_pure = world->GetGameState();
		game_state_base = Cast<Agame_state_base>(game_state_base_pure);
		if (game_state_base) {
			game_state_base->set_score_current(player_score);
			game_state_base->set_time_current_score(player_time);
			game_state_base->compare_scores();
		}
		game_mode_base = world->GetAuthGameMode();
		game_mode_base_level_arena = Cast<Agame_mode_base_level_arena>(game_mode_base);
		game_mode_base_level_arena->implement_hud_ending();
	}
}