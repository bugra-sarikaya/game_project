// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Kismet/GameplayStatics.h"

#include "game_state_base.generated.h"

class Usave_game;

UCLASS()
class GAME_PROJECT_API Agame_state_base : public AGameStateBase {
	GENERATED_BODY()
public:
	Agame_state_base();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;
	void compare_scores();
private:
	UFUNCTION() void save_game();
	UFUNCTION() void load_game();
	UPROPERTY() FString save_slot_string = "slot_0";
	UPROPERTY() TSubclassOf<Usave_game> save_game_class;
	UPROPERTY() Usave_game* load_game_instance;
	UPROPERTY() Usave_game* save_game_instance;
	UPROPERTY() UWorld* world;
	UPROPERTY() int32 score_current;
	UPROPERTY() int32 score_high;
	UPROPERTY() uint32 user_index = 0;
	UPROPERTY() float time_current_score;
	UPROPERTY() float time_high_score;
public:
	FORCEINLINE void set_score_high(int32 new_score_high) { score_high = new_score_high; }
	FORCEINLINE void set_score_current(int32 new_score_current) { score_current = new_score_current; }
	FORCEINLINE void set_time_high_score(float new_time_high_score) { time_high_score = new_time_high_score; }
	FORCEINLINE void set_time_current_score(float new_time_current_score) { time_current_score = new_time_current_score; }
	FORCEINLINE int32 get_score_high() { return score_high; }
	FORCEINLINE int32 get_score_current() { return score_current; }
	FORCEINLINE float get_time_high_score() { return time_high_score; }
	FORCEINLINE float get_time_current_score() { return time_current_score; }
};
