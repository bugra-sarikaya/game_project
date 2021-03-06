// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "game_state_base.h"
#include "save_game.h"

Agame_state_base::Agame_state_base() {
	world = GetWorld();
	PrimaryActorTick.bCanEverTick = false;
	save_game_class = LoadClass<Usave_game>(world, TEXT("/Script/game_project.save_game"));
	check(save_game_class != nullptr);
}
void Agame_state_base::BeginPlay() {
	Super::BeginPlay();
	load_game();
}
void Agame_state_base::Tick(float delta_time) {
	Super::Tick(delta_time);
}
void Agame_state_base::EndPlay(EEndPlayReason::Type reason) {
	Super::EndPlay(reason);
}
void Agame_state_base::compare_scores() {
	if (score_current > score_high) {
		score_high = score_current;
		time_high_score = time_current_score;
		save_game();
	}
	else if (score_current == score_high && time_current_score < time_high_score) {
		time_high_score = time_current_score;
		save_game();
	}
}
void Agame_state_base::save_game() {
	save_game_instance = Cast<Usave_game>(UGameplayStatics::CreateSaveGameObject(save_game_class));
	if (save_game_instance) {
		save_game_instance->set_score_high_save_game(score_high);
		save_game_instance->set_time_high_score_save_game(time_high_score);
		UGameplayStatics::SaveGameToSlot(save_game_instance, save_slot_string, user_index);
	}
}
void Agame_state_base::load_game() {
	load_game_instance = Cast<Usave_game>(UGameplayStatics::LoadGameFromSlot(save_slot_string, user_index));
	if (load_game_instance){
		score_high = load_game_instance->get_score_high_save_game();
		time_high_score = load_game_instance->get_time_high_score_save_game();
	}
}