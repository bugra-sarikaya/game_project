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

#include "hud_ending.generated.h"

class Agame_state_base;

UCLASS()
class GAME_PROJECT_API Ahud_ending : public AHUD {
	GENERATED_BODY()
public:
	Ahud_ending();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void DrawHUD() override;
	virtual void NotifyHitBoxClick(FName hit_box_name) override;
	virtual void NotifyHitBoxBeginCursorOver(FName hit_box_name) override;
	virtual void NotifyHitBoxEndCursorOver(FName hit_box_name) override;
	UFUNCTION() void restart_level();
	UFUNCTION() void quit_game();
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() AGameStateBase* game_state_base_pure;
	UPROPERTY() Agame_state_base* game_state_base;
	UPROPERTY() FIntPoint screen_resolution;
	UPROPERTY() FName hit_box_restart_button_name = "hit_box_button_restart";
	UPROPERTY() FName hit_box_quit_button_name = "hit_box_button_quit";
	UPROPERTY() FName next_level_name = "level_arena";
	UFUNCTION() FString calculate_time(float time);
	UPROPERTY() FString string_current_score = "Your Score: ";
	UPROPERTY() FString string_game_over = "GAME OVER";
	UPROPERTY() FString string_high_score = "High Score: ";
	UPROPERTY() FString string_restart = "RESTART";
	UPROPERTY() FString string_quit = "QUIT";
	UPROPERTY() FString options = "?Game=/Script/game_project.game_mode_base_level_arena";
	UPROPERTY() FVector2D button_restart_center;
	UPROPERTY() FVector2D button_restart_position;
	UPROPERTY() FVector2D button_quit_center;
	UPROPERTY() FVector2D button_quit_position;
	UPROPERTY() FVector2D canvas_scenter;
	UPROPERTY() FVector2D scale;
	UPROPERTY() FVector2D text_current_score_position;
	UPROPERTY() FVector2D text_game_over_position;
	UPROPERTY() FVector2D text_high_score_position;
	UPROPERTY() FVector2D text_restart_position;
	UPROPERTY() FVector2D text_quit_position;
	UPROPERTY() UAudioComponent* audio_component_click_button;
	UPROPERTY() UAudioComponent* audio_component_cursor_over_button;
	UPROPERTY() UAudioComponent* audio_component_ending_menu;
	UPROPERTY() UFont* font_25;
	UPROPERTY() UFont* font_50;
	UPROPERTY() UGameUserSettings* game_user_settings;
	UPROPERTY() USceneComponent* scene_component;
	UPROPERTY() USoundCue* sound_cue_asset_ending_menu;
	UPROPERTY() USoundBase* sound_asset_click_button;
	UPROPERTY() USoundBase* sound_asset_cursor_over_button;
	UPROPERTY() UTexture* button_current_restart_texture_asset;
	UPROPERTY() UTexture* button_current_quit_texture_asset;
	UPROPERTY() UTexture* button_light_texture_asset;
	UPROPERTY() UTexture* button_normal_texture_asset;
	UPROPERTY() UWorld* world;
	UPROPERTY() float duration_clicked_sound;
	UPROPERTY() float gap_buttons = 70.0f;
	UPROPERTY() float gap_initial = 200.0f;
	UPROPERTY() float gap_second = 200.0f;
	UPROPERTY() float gap_scores = 50.0f;
	UPROPERTY() float gap_third = 200.0f;
	UPROPERTY() float mouse_x;
	UPROPERTY() float mouse_y;
	UPROPERTY() float text_current_score_out_height;
	UPROPERTY() float text_current_score_out_width;
	UPROPERTY() float text_game_over_out_height;
	UPROPERTY() float text_game_over_out_width;
	UPROPERTY() float text_high_score_out_height;
	UPROPERTY() float text_high_score_out_width;
	UPROPERTY() float text_restart_out_height;
	UPROPERTY() float text_restart_out_width;
	UPROPERTY() float text_quit_out_height;
	UPROPERTY() float text_quit_out_width;
	UPROPERTY() float volume_multiplier_ending_menu = 0.23f;
	UPROPERTY() bool clicked = false;
};
