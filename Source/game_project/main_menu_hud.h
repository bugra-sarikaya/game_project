// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"

#include "main_menu_hud.generated.h"

/**
 * 
 */
UCLASS()
class GAME_PROJECT_API Amain_menu_hud : public AHUD
{
	GENERATED_BODY()
public:
	Amain_menu_hud();
	virtual void DrawHUD() override;
	virtual void NotifyHitBoxClick(FName hit_box_name) override;
	UPROPERTY() UWorld* world;
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() UTexture* start_button_texture_asset;
	UPROPERTY() UTexture* quit_button_texture_asset;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_base_level_arena_class;
};
