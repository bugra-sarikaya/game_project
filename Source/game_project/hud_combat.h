// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "GameFramework/GameUserSettings.h"
#include "Fonts/SlateFontInfo.h"

#include "hud_combat.generated.h"

class Apaper_player;
class Aplayer_state;
class FCanvasTileItem;


UCLASS()
class GAME_PROJECT_API Ahud_combat : public AHUD
{
	GENERATED_BODY()
public:
	Ahud_combat();
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
protected:
	UFUNCTION() FString calculate_time(float time);
	UPROPERTY() UTexture2D* crosshair_texture_asset;
	UPROPERTY() UWorld* world;
	UPROPERTY() Apaper_player* paper_player;
	UPROPERTY() UGameUserSettings* game_user_settings;
	UPROPERTY() UTexture* stand_player_health_texture_asset;
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() APlayerState* player_state_pure;
	UPROPERTY() Aplayer_state* player_state;
	UPROPERTY() UFont* font_30;
	UPROPERTY() UFont* font_20;
	UPROPERTY() FVector2D canvas_center;
	UPROPERTY() FVector2D stand_player_health_center;
	UPROPERTY() FVector2D crosshair_position;
	UPROPERTY() FVector2D stand_player_health_position;
	UPROPERTY() FVector2D text_player_health_position;
	UPROPERTY() FVector2D text_player_score_position;
	UPROPERTY() FVector2D text_time_position;
	UPROPERTY() FVector2D scale;
	UPROPERTY() FString string_player_health;
	UPROPERTY() FString string_player_score;
	UPROPERTY() FString string_time;
	UPROPERTY() FIntPoint screen_resolution;
	UPROPERTY() float player_health;
	UPROPERTY() int player_score;
	UPROPERTY() float text_player_health_out_width;
	UPROPERTY() float text_player_health_out_height;
	UPROPERTY() float text_player_score_out_width;
	UPROPERTY() float text_player_score_out_height;
	UPROPERTY() float text_time_out_width;
	UPROPERTY() float text_time_out_height;
	UPROPERTY() float distance = 40.0f;
	UPROPERTY() float player_time;
};