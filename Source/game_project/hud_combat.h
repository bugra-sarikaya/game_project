// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

#include "hud_combat.generated.h"

class Apaper_player;
class Aplayer_state;
class FCanvasTileItem;

UCLASS()
class GAME_PROJECT_API Ahud_combat : public AHUD {
	GENERATED_BODY()
public:
	Ahud_combat();
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;
	UPROPERTY() Apaper_player* paper_player;
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() APlayerState* player_state_pure;
	UPROPERTY() Aplayer_state* player_state;
	UPROPERTY() FIntPoint screen_resolution;
	UFUNCTION() FString calculate_time(float time);
	UPROPERTY() FString string_player_health;
	UPROPERTY() FString string_player_score;
	UPROPERTY() FString string_time;
	UPROPERTY() FVector2D canvas_center;
	UPROPERTY() FVector2D stand_player_health_center;
	UPROPERTY() FVector2D crosshair_position;
	UPROPERTY() FVector2D stand_player_health_position;
	UPROPERTY() FVector2D text_player_health_position;
	UPROPERTY() FVector2D text_player_score_position;
	UPROPERTY() FVector2D text_time_position;
	UPROPERTY() FVector2D scale;
	UPROPERTY() UAudioComponent* audio_component_combat;
	UPROPERTY() UAudioComponent* audio_component_combat_heavy;
	UPROPERTY() UAudioComponent* audio_component_alert_low_health;
	UPROPERTY() UFont* font_20;
	UPROPERTY() UFont* font_30;
	UPROPERTY() UGameUserSettings* game_user_settings;
	UPROPERTY() USceneComponent* scene_component;
	UPROPERTY() USoundCue* sound_cue_asset_combat;
	UPROPERTY() USoundCue* sound_cue_asset_combat_heavy;
	UPROPERTY() USoundBase* sound_asset_alert_low_health;
	UPROPERTY() UTexture* stand_player_health_texture_asset;
	UPROPERTY() UTexture2D* crosshair_texture_asset;
	UPROPERTY() UWorld* world;
	UPROPERTY() int32 player_score;
	UPROPERTY() float player_health;
	UPROPERTY() float text_player_health_out_width;
	UPROPERTY() float text_player_health_out_height;
	UPROPERTY() float text_player_score_out_width;
	UPROPERTY() float text_player_score_out_height;
	UPROPERTY() float text_time_out_width;
	UPROPERTY() float text_time_out_height;
	UPROPERTY() float distance = 40.0f;
	UPROPERTY() float player_time;
	UPROPERTY() float volume_multiplier_combat = 0.30f;
	UPROPERTY() float volume_multiplier_combat_heavy = 0.34f;
	UPROPERTY() float volume_multiplier_alert_low_health = 0.25f;
	UPROPERTY() bool alerted = false;
};