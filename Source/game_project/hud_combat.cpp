// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "hud_combat.h"
#include "paper_player.h"
#include "player_state.h"

Ahud_combat::Ahud_combat() {
	PrimaryActorTick.bCanEverTick = false;
	world = GetWorld();
	scene_component = CreateDefaultSubobject<USceneComponent>(TEXT("scene_component"));
	SetRootComponent(scene_component);
	audio_component_combat = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_combat"));
	check(audio_component_combat != nullptr);
	audio_component_combat->bAutoActivate = false;
	audio_component_combat->SetupAttachment(RootComponent);
	audio_component_combat_heavy = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_combat_heavy"));
	check(audio_component_combat_heavy != nullptr);
	audio_component_combat_heavy->bAutoActivate = false;
	audio_component_combat_heavy->SetupAttachment(RootComponent);
	audio_component_alert_low_health = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_alert_low_health"));
	check(audio_component_alert_low_health != nullptr);
	audio_component_alert_low_health->bAutoActivate = false;
	audio_component_alert_low_health->SetupAttachment(RootComponent);
	crosshair_texture_asset = LoadObject<UTexture2D>(world, TEXT("/Game/textures/crosshair_v1.crosshair_v1"));
	stand_player_health_texture_asset = LoadObject<UTexture>(world, TEXT("/Game/textures/hud_health_v1.hud_health_v1"));
	font_30 = LoadObject<UFont>(world, TEXT("/Game/fonts/PressStart2P_Font_30.PressStart2P_Font_30"));
	font_20 = LoadObject<UFont>(world, TEXT("/Game/fonts/PressStart2P_Font_20.PressStart2P_Font_20"));
	sound_cue_asset_combat = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_combat.sound_cue_combat"));
	sound_cue_asset_combat_heavy = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_combat_heavy.sound_cue_combat_heavy"));
	sound_asset_alert_low_health = LoadObject<USoundBase>(world, TEXT("/Game/sounds/alert_low_health.alert_low_health"));
	game_user_settings = const_cast<UGameUserSettings*>(GetDefault<UGameUserSettings>());
	audio_component_combat->SetSound(sound_cue_asset_combat);
	audio_component_combat->SetVolumeMultiplier(volume_multiplier_combat);
	audio_component_combat_heavy->SetSound(sound_cue_asset_combat_heavy);
	audio_component_combat_heavy->SetVolumeMultiplier(volume_multiplier_combat_heavy);
	audio_component_alert_low_health->SetSound(sound_asset_alert_low_health);
	audio_component_alert_low_health->SetVolumeMultiplier(volume_multiplier_alert_low_health);
}
void Ahud_combat::BeginPlay() {
	Super::BeginPlay();
	player_controller = UGameplayStatics::GetPlayerController(world, 0);
	audio_component_combat->Play();
}
void Ahud_combat::Tick(float delta_time) {
	Super::Tick(delta_time);
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
			if (player_health <= 25.0f && !alerted && !audio_component_alert_low_health->IsActive()) {
				alerted = true;
				audio_component_alert_low_health->Play();
			}
			else if (player_health <= 50.0f && !audio_component_combat_heavy->IsActive()) {
				audio_component_combat->Stop();
				audio_component_combat_heavy->Play();
			}
			string_player_health = FString::FromInt(FMath::FloorToInt(player_health));
		}
	}
	GetTextSize(string_player_health, text_player_health_out_width, text_player_health_out_height, font_30, 1);
	text_player_health_position = FVector2D(stand_player_health_center.X - text_player_health_out_width * scale.X * 0.5f, stand_player_health_center.Y - text_player_health_out_height * scale.Y * 0.5f);
	FCanvasTextItem text_health_item(text_player_health_position, FText::FromString(string_player_health), font_30, FColor(220, 0, 0));
	text_health_item.Scale = scale;
	Canvas->DrawItem(text_health_item);
	if (paper_player) {  // Starting to create score text. 
		if (player_state) {
			player_score = player_state->get_player_score();
			string_player_score = FString::FromInt(player_score);
		}
	} 
	GetTextSize(string_player_score, text_player_score_out_width, text_player_score_out_height, font_20, 1);
	text_player_score_position = FVector2D(canvas_center.X  - text_player_score_out_width * scale.X, distance * scale.Y);
	FCanvasTextItem score_text_item(text_player_score_position, FText::FromString(string_player_score), font_20, FColor(255, 119, 0));
	score_text_item.Scale = scale;
	Canvas->DrawItem(score_text_item);
	if (paper_player) {  // Starting to create time text.
		if (player_state) {
			player_time = player_state->get_player_time();
		}
	}
	string_time = calculate_time(player_time);
	GetTextSize(string_time, text_time_out_width, text_time_out_height, font_20, 1);
	text_time_position = FVector2D(Canvas->ClipX -  distance * scale.X - text_time_out_width * scale.X, distance * scale.Y);
	FCanvasTextItem time_text_item(text_time_position, FText::FromString(string_time), font_20, FColor(255, 119, 0));
	time_text_item.Scale = scale;
	Canvas->DrawItem(time_text_item);
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