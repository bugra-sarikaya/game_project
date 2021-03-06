// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

#include "hud_main_menu.generated.h"

UCLASS()
class GAME_PROJECT_API Ahud_main_menu : public AHUD{
	GENERATED_BODY()
public:
	Ahud_main_menu();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void DrawHUD() override;
	virtual void NotifyHitBoxClick(FName hit_box_name) override;
	virtual void NotifyHitBoxBeginCursorOver(FName hit_box_name) override;
	virtual void NotifyHitBoxEndCursorOver(FName hit_box_name) override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;
	UFUNCTION() void start_level();
	UFUNCTION() void quit_game();
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() FIntPoint screen_resolution;
	UPROPERTY() FName hit_box_start_button_name = "hit_box_button_start";
	UPROPERTY() FName hit_box_quit_button_name = "hit_box_button_quit";
	UPROPERTY() FName next_level_name = "level_arena";
	UPROPERTY() FString options = "?Game=/Script/game_project.game_mode_base_level_arena";
	UPROPERTY() FString string_start = "START";
	UPROPERTY() FString string_quit = "QUIT";
	UPROPERTY() FVector2D button_start_center;
	UPROPERTY() FVector2D button_start_position;
	UPROPERTY() FVector2D button_quit_center;
	UPROPERTY() FVector2D button_quit_position;
	UPROPERTY() FVector2D canvas_scenter;
	UPROPERTY() FVector2D scale;
	UPROPERTY() FVector2D text_start_position;
	UPROPERTY() FVector2D text_quit_position;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_base_level_arena_class;
	UPROPERTY() UAudioComponent* audio_component_click_button;
	UPROPERTY() UAudioComponent* audio_component_cursor_over_button;
	UPROPERTY() UAudioComponent* audio_component_main_menu;
	UPROPERTY() UFont* font_25;
	UPROPERTY() UGameUserSettings* game_user_settings;
	UPROPERTY() USceneComponent* scene_component;
	UPROPERTY() USoundCue* sound_cue_asset_main_menu;
	UPROPERTY() USoundBase* sound_asset_click_button_sound;
	UPROPERTY() USoundBase* sound_asset_cursor_over_button;
	UPROPERTY() UTexture* button_current_start_texture_asset;
	UPROPERTY() UTexture* button_current_quit_texture_asset;
	UPROPERTY() UTexture* button_light_texture_asset;
	UPROPERTY() UTexture* button_normal_texture_asset;
	UPROPERTY() UWorld* world;
	UPROPERTY() float duration_clicked_sound;
	UPROPERTY() float gap_buttons = 70.0f;
	UPROPERTY() float gap_initial = 375.0f;
	UPROPERTY() float mouse_x;
	UPROPERTY() float mouse_y;
	UPROPERTY() float text_start_out_width;
	UPROPERTY() float text_start_out_height;
	UPROPERTY() float text_quit_out_width;
	UPROPERTY() float text_quit_out_height;
	UPROPERTY() float volume_multiplier_main_menu = 0.20f;
	UPROPERTY() bool clicked = false;
};
