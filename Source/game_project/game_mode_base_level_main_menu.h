// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GameFramework/HUD.h"
#include "Engine/Engine.h"

#include "game_mode_base_level_main_menu.generated.h"


UCLASS()
class GAME_PROJECT_API Agame_mode_base_level_main_menu : public AGameModeBase
{
	GENERATED_BODY()
public:
	Agame_mode_base_level_main_menu();
	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	virtual void Tick(float delta_time) override;
	UPROPERTY() TSubclassOf<AHUD> hud_class;
	UPROPERTY() UWorld* world;
};