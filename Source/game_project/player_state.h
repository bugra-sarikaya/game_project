// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "Kismet/GameplayStatics.h"

#include "player_state.generated.h"

class Apaper_player;
class Agame_state_base;
class Agame_mode_base_level_arena;

UCLASS()
class GAME_PROJECT_API Aplayer_state : public APlayerState
{
	GENERATED_BODY()
public:
	Aplayer_state();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;
private:
	UPROPERTY() UWorld* world;
	UPROPERTY() int32 player_score;
	UPROPERTY() Apaper_player* paper_player;
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() AGameStateBase* game_state_base_pure;
	UPROPERTY() Agame_state_base* game_state_base;
	UPROPERTY() AGameModeBase* game_mode_base;
	UPROPERTY() Agame_mode_base_level_arena* game_mode_base_level_arena;
	UPROPERTY() float player_health;
	UPROPERTY() float player_time;
	UPROPERTY() float player_time_start;
	UPROPERTY() float player_time_end;
public:
	FORCEINLINE int32 get_player_score() { return player_score; }
	FORCEINLINE float get_player_health() { return player_health; }
	FORCEINLINE float get_player_time() { return player_time; }
	FORCEINLINE float get_player_time_start() { return player_time_start; }
	FORCEINLINE float get_player_time_end() { return player_time_end; }
	FORCEINLINE void set_player_score(int32 score) { player_score = score; }
	FORCEINLINE void set_player_health(float health) { player_health = health; }
	FORCEINLINE void set_player_time(float time) { player_time = time; }
	FORCEINLINE void set_player_time_start(float time) { player_time_start = time; }
	FORCEINLINE void set_player_time_end(float time) { player_time_end = time; }
};
