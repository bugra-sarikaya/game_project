// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "hud_ending.h"
#include "game_state_base.h"

Ahud_ending::Ahud_ending() {
	world = GetWorld();
	button_normal_texture_asset = LoadObject<UTexture>(world, TEXT("/Game/textures/button_normal.button_normal"));
	button_light_texture_asset = LoadObject<UTexture>(world, TEXT("/Game/textures/button_light.button_light"));
	//game_mode_base_current = UGameplayStatics::GetGameMode(world);
	font_25 = LoadObject<UFont>(world, TEXT("/Game/fonts/PressStart2P_Font_25.PressStart2P_Font_25"));
	font_30 = LoadObject<UFont>(world, TEXT("/Game/fonts/PressStart2P_Font_30.PressStart2P_Font_30"));
	font_50 = LoadObject<UFont>(world, TEXT("/Game/fonts/PressStart2P_Font_50.PressStart2P_Font_50"));
	game_user_settings = const_cast<UGameUserSettings*>(GetDefault<UGameUserSettings>());
	button_current_restart_texture_asset = button_normal_texture_asset;
	button_current_quit_texture_asset = button_normal_texture_asset;
}
void Ahud_ending::BeginPlay() {
	player_controller = UGameplayStatics::GetPlayerController(world, 0);
	player_controller->bShowMouseCursor = true;
	player_controller->bEnableClickEvents = true;
	game_state_base_pure = world->GetGameState();
	game_state_base = Cast<Agame_state_base>(game_state_base_pure);
	if (game_state_base) {
		string_high_score += FString::FromInt(game_state_base->get_score_high()) + " " + calculate_time(game_state_base->get_time_high_score());
		string_current_score += FString::FromInt(game_state_base->get_score_current()) + " " + calculate_time(game_state_base->get_time_current_score());
	}
}
void Ahud_ending::DrawHUD() {
	Super::DrawHUD();
	screen_resolution = game_user_settings->GetScreenResolution();
	scale = FVector2D(Canvas->ClipX / screen_resolution.X, Canvas->ClipY / screen_resolution.Y);
	canvas_scenter = FVector2D(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	DrawRect(FColor(18, 18, 18), 0.0f, 0.0f, Canvas->ClipX, Canvas->ClipY); // Creating background.
	GetTextSize(string_game_over, text_game_over_out_width, text_game_over_out_height, font_50, 1); // Starting to create game over text.
	text_game_over_position = FVector2D(canvas_scenter.X - text_game_over_out_width * scale.X * 0.5f, gap_initial * scale.Y);
	FCanvasTextItem text_game_over_item(text_game_over_position, FText::FromString(string_game_over), font_50, FColor::Red);
	text_game_over_item.Scale = scale;
	Canvas->DrawItem(text_game_over_item);
	GetTextSize(string_high_score, text_high_score_out_width, text_high_score_out_height, font_25, 1); // Starting to create high score text.
	text_high_score_position = FVector2D(canvas_scenter.X - text_high_score_out_width * scale.X * 0.5f, text_game_over_position.Y + text_game_over_out_height * scale.Y + gap_second * scale.Y * 0.5f);
	FCanvasTextItem text_high_score_item(text_high_score_position, FText::FromString(string_high_score), font_25, FColor::Red);
	text_high_score_item.Scale = scale;
	Canvas->DrawItem(text_high_score_item);
	GetTextSize(string_current_score, text_current_score_out_width, text_current_score_out_height, font_25, 1); // Starting to create current score text.
	text_current_score_position = FVector2D(canvas_scenter.X - text_current_score_out_width * scale.X * 0.5f, text_high_score_position.Y + text_high_score_out_height * scale.Y + gap_scores * scale.Y * 0.5f);
	FCanvasTextItem text_current_score_item(text_current_score_position, FText::FromString(string_current_score), font_25, FColor::Red);
	text_current_score_item.Scale = scale;
	Canvas->DrawItem(text_current_score_item);
	button_restart_position = FVector2D(canvas_scenter.X - (button_current_restart_texture_asset->GetSurfaceWidth() * scale.X * 0.5f), text_current_score_position.Y + text_current_score_out_height * scale.Y + gap_third * scale.Y * 0.5f); // Starting to create restart button.
	FCanvasTileItem button_restart_tile_item(button_restart_position, button_current_restart_texture_asset->Resource, FLinearColor::White); 
	button_restart_tile_item.BlendMode = SE_BLEND_Translucent;
	button_restart_tile_item.Size = button_restart_tile_item.Size * scale;
	Canvas->DrawItem(button_restart_tile_item);
	button_restart_center = FVector2D(button_restart_position.X + button_current_restart_texture_asset->GetSurfaceWidth() * scale.X * 0.5f, button_restart_position.Y + button_current_restart_texture_asset->GetSurfaceHeight() * scale.Y * 0.5f);  // Starting to create restart text.
	GetTextSize(string_restart, text_restart_out_width, text_restart_out_height, font_25, 1);
	text_restart_position = FVector2D(button_restart_center.X - text_restart_out_width * scale.X * 0.5f, button_restart_center.Y - text_restart_out_height * scale.Y * 0.5f);
	FCanvasTextItem text_restart_item(text_restart_position, FText::FromString(string_restart), font_25, FColor::Black);
	text_restart_item.Scale = scale;
	Canvas->DrawItem(text_restart_item);
	button_quit_position = FVector2D(canvas_scenter.X - (button_current_quit_texture_asset->GetSurfaceWidth() * scale.X * 0.5f), button_restart_position.Y + button_current_quit_texture_asset->GetSurfaceHeight() * scale.Y + gap_buttons * scale.Y * 0.5f); // Starting to create quit button.
	FCanvasTileItem button_quit_tile_item(button_quit_position, button_current_quit_texture_asset->Resource, FLinearColor::White);
	button_quit_tile_item.BlendMode = SE_BLEND_Translucent;
	button_quit_tile_item.Size = button_quit_tile_item.Size * scale;
	Canvas->DrawItem(button_quit_tile_item);
	button_quit_center = FVector2D(button_quit_position.X + button_current_quit_texture_asset->GetSurfaceWidth() * scale.X * 0.5f, button_quit_position.Y + button_current_quit_texture_asset->GetSurfaceHeight() * scale.Y * 0.5f);  // Starting to create quit text.
	GetTextSize(string_quit, text_quit_out_width, text_quit_out_height, font_25, 1);
	text_quit_position = FVector2D(button_quit_center.X - text_quit_out_width * scale.X * 0.5f, button_quit_center.Y - text_quit_out_height * scale.Y * 0.5f);
	FCanvasTextItem text_quit_item(text_quit_position, FText::FromString(string_quit), font_25, FColor::Black);
	text_quit_item.Scale = scale;
	Canvas->DrawItem(text_quit_item);
	//DrawTextureSimple(start_button_texture_asset, start_button_position.X, start_button_position.Y, scale);
	//DrawTextureSimple(quit_button_texture_asset, quit_button_position.X, quit_button_position.Y, scale);
	AddHitBox(button_restart_position, FVector2D(button_current_restart_texture_asset->GetSurfaceWidth() * scale.X, button_current_restart_texture_asset->GetSurfaceHeight() * scale.Y), hit_box_restart_button_name, false);
	AddHitBox(button_quit_position, FVector2D(button_current_quit_texture_asset->GetSurfaceWidth() * scale.X, button_current_quit_texture_asset->GetSurfaceHeight() * scale.Y), hit_box_quit_button_name, false);
}
FString Ahud_ending::calculate_time(float time) {
	int remaining_time, minutes, seconds, centiseceonds;
	remaining_time = FMath::FloorToInt(time * 100.0f);
	minutes = remaining_time / 6000;
	remaining_time = remaining_time % 6000;
	seconds = remaining_time / 100;
	remaining_time = remaining_time % 100;
	centiseceonds = remaining_time;
	return FString::Printf(TEXT("%02d:%02d:%02d"), minutes, seconds, centiseceonds);
}
void Ahud_ending::NotifyHitBoxClick(FName hit_box_name) {
	Super::NotifyHitBoxClick(hit_box_name);
	if (hit_box_name == FName("hit_box_button_restart")) {
		current_level_name = world->GetMapName();
		current_level_name.RemoveFromStart(world->StreamingLevelsPrefix);
		next_level_name = "level_arena";
		options = "?Game=/Script/game_project.game_mode_base_level_arena";
		UGameplayStatics::OpenLevel(world, next_level_name, false, options);
	}
	else if (hit_box_name == FName("hit_box_button_quit")) {
		UGameplayStatics::GetPlayerController(world, 0)->ConsoleCommand("quit");
	}
}
void Ahud_ending::NotifyHitBoxBeginCursorOver(FName hit_box_name) {
	ReceiveHitBoxBeginCursorOver(hit_box_name);
	if (hit_box_name == FName("hit_box_button_restart")) {
		button_current_restart_texture_asset = button_light_texture_asset;
	}
	else if (hit_box_name == FName("hit_box_button_quit")) {
		button_current_quit_texture_asset = button_light_texture_asset;
	}
}

void Ahud_ending::NotifyHitBoxEndCursorOver(FName hit_box_name) {
	ReceiveHitBoxEndCursorOver(hit_box_name);
	if (hit_box_name == FName("hit_box_button_restart")) {
		button_current_restart_texture_asset = button_normal_texture_asset;
	}
	else if (hit_box_name == FName("hit_box_button_quit")) {
		button_current_quit_texture_asset = button_normal_texture_asset;
	}
}