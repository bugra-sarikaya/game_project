// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "player_state.h"

Aplayer_state::Aplayer_state() {
	world = GetWorld();
	PrimaryActorTick.bCanEverTick = true;
}
void Aplayer_state::BeginPlay() {
	Super::BeginPlay();
	player_score = 0;
}
void Aplayer_state::Tick(float delta_time) {
	Super::Tick(delta_time);
	player_time = player_time_end - player_time_start;
}