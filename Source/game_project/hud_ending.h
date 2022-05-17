// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "GameFramework/GameUserSettings.h"

#include "hud_ending.generated.h"


UCLASS()
class GAME_PROJECT_API Ahud_ending : public AHUD
{
	GENERATED_BODY()
public:
	Ahud_ending();
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
	UPROPERTY() UTexture* button_current_restart_texture_asset;
	UPROPERTY() UTexture* button_current_quit_texture_asset;
	UPROPERTY() AGameModeBase* game_mode_base_current;
	UPROPERTY() FIntPoint screen_resolution;
	UPROPERTY() FVector2D canvas_scenter;
	UPROPERTY() FVector2D button_restart_center;
	UPROPERTY() FVector2D button_quit_center;
	UPROPERTY() FVector2D scale;
	UPROPERTY() FVector2D button_restart_position;
	UPROPERTY() FVector2D button_quit_position;
	UPROPERTY() FVector2D text_restart_position;
	UPROPERTY() FVector2D text_quit_position;
	UPROPERTY() FName hit_box_restart_button_name = "hit_box_button_restart";
	UPROPERTY() FName hit_box_quit_button_name = "hit_box_button_quit";
	UPROPERTY() FName next_level_name = "level_arena";
	UPROPERTY() FString string_restart = "RESTART";
	UPROPERTY() FString string_quit = "QUIT";
	UPROPERTY() FString current_level_name;
	UPROPERTY() FString options = "?Game=/Script/game_project.game_mode_base_level_arena";
	UPROPERTY() float button_gap = 160.0f;
	UPROPERTY() float text_restart_out_width;
	UPROPERTY() float text_restart_out_height;
	UPROPERTY() float text_quit_out_width;
	UPROPERTY() float text_quit_out_height;
};
