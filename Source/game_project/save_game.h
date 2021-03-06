// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "Kismet/GameplayStatics.h"

#include "save_game.generated.h"

UCLASS()
class GAME_PROJECT_API Usave_game : public USaveGame {
	GENERATED_BODY()
public:
	Usave_game();
private:
	UPROPERTY() int32 score_high_save_game;
	UPROPERTY() float time_high_score_save_game;
public:
	FORCEINLINE void set_score_high_save_game(int32 new_score_high) { score_high_save_game = new_score_high; }
	FORCEINLINE void set_time_high_score_save_game(float new_time_high_score) { time_high_score_save_game = new_time_high_score; }
	FORCEINLINE int32 get_score_high_save_game() { return score_high_save_game; }
	FORCEINLINE float get_time_high_score_save_game() { return time_high_score_save_game; }
};
