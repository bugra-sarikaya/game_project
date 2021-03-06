// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "GameMapsSettings.h"

#include "game_instance.generated.h"

UCLASS()
class GAME_PROJECT_API Ugame_instance : public UGameInstance {
	GENERATED_BODY()
public:
	Ugame_instance();
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;
	UPROPERTY() FName next_level_name = "level_arena";
	UPROPERTY() FString current_level_name;
	UPROPERTY() FString options = "?Game=/Script/game_project.game_mode_base_level_main_menu";
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_base_level_arena_class;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_base_level_main_menu_class;
	UPROPERTY() UGameUserSettings* game_user_settings;
	UPROPERTY() UWorld* world;
};
