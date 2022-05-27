// Fill out your copyright notice in the Description page of Project Settings.


#include "hud_combat.h"
#include "paper_player.h"
#include "player_state.h"

Ahud_combat::Ahud_combat(){
	world = GetWorld(); 
	PrimaryActorTick.bCanEverTick = true;
	//static ConstructorHelpers::FObjectFinder<UTexture2D> crosshair_texture_object(TEXT("/Game/hud/crosshair_v1.crosshair_v1"));
	//crosshair_texture = crosshair_texture_object.Object;
	crosshair_texture_asset = LoadObject<UTexture2D>(world, TEXT("/Game/hud/crosshair_v1.crosshair_v1"));
	stand_player_health_texture_asset = LoadObject<UTexture>(world, TEXT("/Game/hud/hud_health_v1.hud_health_v1"));
	font_30 = LoadObject<UFont>(world, TEXT("/Game/fonts/PressStart2P_Font_30.PressStart2P_Font_30"));
	font_20 = LoadObject<UFont>(world, TEXT("/Game/fonts/PressStart2P_Font_20.PressStart2P_Font_20"));
	combat_sound_asset = LoadObject<USoundBase>(world, TEXT("/Game/sounds/usuper_gore.usuper_gore"));
	sound_asset_alert_low_health = LoadObject<USoundBase>(world, TEXT("/Game/sounds/alert_low_health.alert_low_health"));
	game_user_settings = const_cast<UGameUserSettings*>(GetDefault<UGameUserSettings>());
	player_controller = UGameplayStatics::GetPlayerController(world, 0);
}
void Ahud_combat::BeginPlay() {
	Super::BeginPlay();
	audio_component_combat = UGameplayStatics::SpawnSound2D(world, combat_sound_asset, volume_multiplier_value_combot_sound);
}
void Ahud_combat::Tick(float delta_time) {
	Super::Tick(delta_time);
	if (audio_component_combat && !audio_component_combat->IsActive()) audio_component_combat->Play();
}
void Ahud_combat::DrawHUD() {
	Super::DrawHUD();
	screen_resolution = game_user_settings->GetScreenResolution();
	scale = FVector2D(Canvas->ClipX / screen_resolution.X , Canvas->ClipY /screen_resolution.Y);
	canvas_center = FVector2D(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	crosshair_position = FVector2D(canvas_center.X - crosshair_texture_asset->GetSurfaceWidth() * scale.X * 0.5f, canvas_center.Y - crosshair_texture_asset->GetSurfaceHeight() * scale.Y * 0.5f);
	FCanvasTileItem crosshair_tile_item(crosshair_position, crosshair_texture_asset->Resource, FLinearColor::White); // Starting to create crosshair.
	crosshair_tile_item.BlendMode = SE_BLEND_Translucent;
	crosshair_tile_item.Size = crosshair_tile_item.Size * scale;
	Canvas->DrawItem(crosshair_tile_item);
	//DrawTextureSimple(crosshair_texture_asset, crosshair_position.X, crosshair_position.Y, 1.0f);
	//DrawTexture(crosshair_texture_asset, crosshair_position.X, crosshair_position.Y, crosshair_texture_asset->GetSurfaceWidth(), crosshair_texture_asset->GetSurfaceHeight(), 1.0f, 1.0f, 1.0f, 1.0f);
	stand_player_health_position = FVector2D(distance * scale.X, Canvas->ClipY - distance * scale.Y - stand_player_health_texture_asset->GetSurfaceHeight() * scale.Y);
	FCanvasTileItem stand_health_tile_item(stand_player_health_position, stand_player_health_texture_asset->Resource, FLinearColor::White); // Starting to create health stand.
	stand_health_tile_item.BlendMode = SE_BLEND_Translucent;
	stand_health_tile_item.Size = stand_health_tile_item.Size * scale;
	Canvas->DrawItem(stand_health_tile_item);
	stand_player_health_center = FVector2D(stand_player_health_position.X + stand_player_health_texture_asset->GetSurfaceWidth() * scale.X * 0.5f, stand_player_health_position.Y + stand_player_health_texture_asset->GetSurfaceHeight() * scale.Y * 0.5f); // Starting to create health text.
	paper_player = Cast<Apaper_player>(player_controller->GetPawn());
	if (paper_player) {
		player_state_pure = paper_player->GetPlayerState();
		if (player_state_pure) {
			player_state = Cast<Aplayer_state>(player_state_pure);
			player_health = player_state->get_player_health();
			if (player_health <= 25.0f && !alerted) {
				audio_component_alert_low_health = UGameplayStatics::SpawnSound2D(world, sound_asset_alert_low_health, volume_multiplier_value_alert_low_health);
				alerted = true;
			}
			string_player_health = FString::FromInt(FMath::FloorToInt(player_health));
		}
	}
	GetTextSize(string_player_health, text_player_health_out_width, text_player_health_out_height, font_30, 1);
	text_player_health_position = FVector2D(stand_player_health_center.X - text_player_health_out_width * scale.X * 0.5f, stand_player_health_center.Y - text_player_health_out_height * scale.Y * 0.5f);
	//health_text_position = FVector2D((Canvas->ClipX / distance_rate), Canvas->ClipY - (Canvas->ClipY / distance_rate) - (health_text_out_height * scale.Y));
	//UE_LOG(LogTemp, Warning, TEXT("%f %f"), text_out_width, text_out_height);
	FCanvasTextItem text_health_item(text_player_health_position, FText::FromString(string_player_health), font_30, FColor(196, 4, 4));
	text_health_item.Scale = scale;
	Canvas->DrawItem(text_health_item);
	//player_controller = UGameplayStatics::GetPlayerController(world, 0);
	//pawn = player_controller->GetPawn();
	if (paper_player) {  // Starting to create score text. 
		if (player_state) {
			//player_state_pure = paper_player->GetPlayerState();
			//player_state = Cast<Aplayer_state>(player_state_pure);
			player_score = player_state->get_player_score();
			string_player_score = FString::FromInt(player_score);
			//UE_LOG(LogTemp, Warning, TEXT("%d"), player_score);
		}
	} 
	GetTextSize(string_player_score, text_player_score_out_width, text_player_score_out_height, font_20, 1);
	text_player_score_position = FVector2D(canvas_center.X  - text_player_score_out_width * scale.X, distance * scale.Y);
	FCanvasTextItem score_text_item(text_player_score_position, FText::FromString(string_player_score), font_20, FColor(196, 4, 4));
	score_text_item.Scale = scale;
	Canvas->DrawItem(score_text_item);
	if (paper_player) {  // Starting to create time text.
		if (player_state) {
			player_time = player_state->get_player_time();
			//UE_LOG(LogTemp, Warning, TEXT("%f"), player_time);
		}
	}
	string_time = calculate_time(player_time);
	GetTextSize(string_time, text_time_out_width, text_time_out_height, font_20, 1);
	text_time_position = FVector2D(Canvas->ClipX -  distance * scale.X - text_time_out_width * scale.X, distance * scale.Y);
	//InFontInfo.FontObject = font;
	FCanvasTextItem time_text_item(text_time_position, FText::FromString(string_time), font_20, FColor(196, 4, 4));
	time_text_item.Scale = scale;
	Canvas->DrawItem(time_text_item);
	//int32 centiseceonds = FMath::FloorToInt(elapsed_time / 600.0f);
	//UE_LOG(LogTemp, Warning, TEXT("%02d:%02d:%02d"), minutes, seconds, centiseceonds);
}
FString Ahud_combat::calculate_time(float time) {
	int remaining_time, minutes, seconds, centiseceonds;
	remaining_time = FMath::FloorToInt(time * 100.0f);
	minutes = remaining_time / 6000;
	remaining_time = remaining_time % 6000;
	seconds = remaining_time / 100;
	remaining_time = remaining_time % 100;
	centiseceonds = remaining_time;
	return FString::Printf(TEXT("%02d:%02d:%02d"), minutes, seconds, centiseceonds);
}
void Ahud_combat::EndPlay(EEndPlayReason::Type reason) {
	Super::EndPlay(reason);
	audio_component_combat->Stop();
}