// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GameFramework/HUD.h"

#include "game_mode_base_default.generated.h"

/**
 * 
 */
UCLASS()
class GAME_PROJECT_API Agame_mode_base_default : public AGameModeBase
{
	GENERATED_BODY()
public:
	Agame_mode_base_default();
	virtual void BeginPlay() override;
	UPROPERTY() UWorld* world;
	UPROPERTY() FString current_level_name;
	UPROPERTY() FString level_main_menu = "level_main_menu";
	UPROPERTY() FString level_arena = "level_arena";
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_base_level_main_menu_class;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_base_level_arena_class;
	UPROPERTY() TSubclassOf<AHUD> hud_class;
};
