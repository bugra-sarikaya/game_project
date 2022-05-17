// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "GameFramework/GameUserSettings.h"

#include "hud_main_menu.generated.h"


UCLASS()
class GAME_PROJECT_API Ahud_main_menu : public AHUD
{
	GENERATED_BODY()
public:
	Ahud_main_menu();
	virtual void DrawHUD() override;
	virtual void NotifyHitBoxClick(FName hit_box_name) override;
	virtual void NotifyHitBoxBeginCursorOver(FName hit_box_name) override;
	virtual void NotifyHitBoxEndCursorOver(FName hit_box_name) override;
	UPROPERTY() UWorld* world;
	UPROPERTY() UFont* font_25;
	UPROPERTY() UGameUserSettings* game_user_settings;
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() UTexture* button_normal_texture_asset;
	UPROPERTY() UTexture* button_light_texture_asset;
	UPROPERTY() UTexture* button_current_start_texture_asset;
	UPROPERTY() UTexture* button_current_quit_texture_asset;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_base_level_arena_class;
	UPROPERTY() FIntPoint screen_resolution;
	UPROPERTY() FVector2D canvas_scenter;
	UPROPERTY() FVector2D button_start_center;
	UPROPERTY() FVector2D button_quit_center;
	UPROPERTY() FVector2D scale;
	UPROPERTY() FVector2D button_start_position;
	UPROPERTY() FVector2D button_quit_position;
	UPROPERTY() FVector2D text_start_position;
	UPROPERTY() FVector2D text_quit_position;
	UPROPERTY() FName hit_box_start_button_name = "hit_box_button_start";
	UPROPERTY() FName hit_box_quit_button_name = "hit_box_button_quit";
	UPROPERTY() FName next_level_name = "level_arena";
	UPROPERTY() FString string_start = "START";
	UPROPERTY() FString string_quit = "QUIT";
	UPROPERTY() FString current_level_name;
	UPROPERTY() FString options = "?Game=/Script/game_project.game_mode_base_level_arena";
	UPROPERTY() float button_gap = 160.0f;
	UPROPERTY() float text_start_out_width;
	UPROPERTY() float text_start_out_height;
	UPROPERTY() float text_quit_out_width;
	UPROPERTY() float text_quit_out_height;
};
