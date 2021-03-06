// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "hud_main_menu.h"

Ahud_main_menu::Ahud_main_menu() {
	PrimaryActorTick.bCanEverTick = false;
	scene_component = CreateDefaultSubobject<USceneComponent>(TEXT("scene_component"));
	SetRootComponent(scene_component);
	audio_component_main_menu = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_main_menu"));
	check(audio_component_main_menu != nullptr);
	audio_component_main_menu->bAutoActivate = false;
	audio_component_main_menu->SetupAttachment(RootComponent);
	world = GetWorld();
	game_mode_base_level_arena_class = LoadClass<AGameModeBase>(world, TEXT("/Script/game_project.game_mode_base_level_arena"));
	button_normal_texture_asset = LoadObject<UTexture>(world, TEXT("/Game/textures/button_normal.button_normal"));
	button_light_texture_asset = LoadObject<UTexture>(world, TEXT("/Game/textures/button_light.button_light"));
	font_25 = LoadObject<UFont>(world, TEXT("/Game/fonts/PressStart2P_Font_25.PressStart2P_Font_25"));
	sound_cue_asset_main_menu = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_main_menu.sound_cue_main_menu"));
	sound_asset_cursor_over_button = LoadObject<USoundBase>(world, TEXT("/Game/sounds/buttonrollover.buttonrollover"));
	sound_asset_click_button_sound = LoadObject<USoundBase>(world, TEXT("/Game/sounds/buttonclickrelease.buttonclickrelease"));
	game_user_settings = const_cast<UGameUserSettings*>(GetDefault<UGameUserSettings>());
	button_current_start_texture_asset = button_normal_texture_asset;
	button_current_quit_texture_asset = button_normal_texture_asset;
	audio_component_main_menu->SetSound(sound_cue_asset_main_menu);
	audio_component_main_menu->SetVolumeMultiplier(volume_multiplier_main_menu);
}
void Ahud_main_menu::BeginPlay() {
	player_controller = UGameplayStatics::GetPlayerController(world, 0);
	player_controller->bShowMouseCursor = true;
	player_controller->bEnableClickEvents = true;
	audio_component_main_menu->Play();
}
void Ahud_main_menu::Tick(float delta_time) {
	Super::Tick(delta_time);
}
void Ahud_main_menu::DrawHUD() {
	Super::DrawHUD();
	screen_resolution = game_user_settings->GetScreenResolution();
	scale = FVector2D(Canvas->ClipX / screen_resolution.X, Canvas->ClipY / screen_resolution.Y);
	canvas_scenter = FVector2D(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	DrawRect(FColor(18, 18, 18), 0.0f, 0.0f, Canvas->ClipX, Canvas->ClipY); // Creating background.
	button_start_position = FVector2D(canvas_scenter.X - (button_current_start_texture_asset->GetSurfaceWidth() * scale.X * 0.5f), gap_initial * scale.Y); // Starting to create start button.
	FCanvasTileItem button_start_tile_item(button_start_position, button_current_start_texture_asset->Resource, FLinearColor::White);
	button_start_tile_item.BlendMode = SE_BLEND_Translucent;
	button_start_tile_item.Size = button_start_tile_item.Size * scale;
	Canvas->DrawItem(button_start_tile_item);
	button_start_center = FVector2D(button_start_position.X + button_current_start_texture_asset->GetSurfaceWidth() * scale.X * 0.5f, button_start_position.Y + button_current_start_texture_asset->GetSurfaceHeight() * scale.Y * 0.5f);  // Starting to create start text.
	GetTextSize(string_start, text_start_out_width, text_start_out_height, font_25);
	text_start_position = FVector2D(button_start_center.X - text_start_out_width * scale.X * 0.5f, button_start_center.Y - text_start_out_height * scale.Y * 0.5f);
	FCanvasTextItem text_start_item(text_start_position, FText::FromString(string_start), font_25, FColor::Black);
	text_start_item.Scale = scale;
	Canvas->DrawItem(text_start_item);
	button_quit_position = FVector2D(canvas_scenter.X - (button_current_quit_texture_asset->GetSurfaceWidth() * scale.X * 0.5f), button_start_position.Y + button_current_start_texture_asset->GetSurfaceHeight() * scale.Y  + gap_buttons * scale.Y * 0.5f); // Starting to create quit button.
	FCanvasTileItem button_quit_tile_item(button_quit_position, button_current_quit_texture_asset->Resource, FLinearColor::White);
	button_quit_tile_item.BlendMode = SE_BLEND_Translucent;
	button_quit_tile_item.Size = button_quit_tile_item.Size * scale;
	Canvas->DrawItem(button_quit_tile_item);
	button_quit_center = FVector2D(button_quit_position.X + button_current_quit_texture_asset->GetSurfaceWidth() * scale.X * 0.5f, button_quit_position.Y + button_current_quit_texture_asset->GetSurfaceHeight() * scale.Y * 0.5f);  // Starting to create quit text.
	GetTextSize(string_quit, text_quit_out_width, text_quit_out_height, font_25);
	text_quit_position = FVector2D(button_quit_center.X - text_quit_out_width * scale.X * 0.5f, button_quit_center.Y - text_quit_out_height * scale.Y * 0.5f);
	FCanvasTextItem text_quit_item(text_quit_position, FText::FromString(string_quit), font_25, FColor::Black);
	text_quit_item.Scale = scale;
	Canvas->DrawItem(text_quit_item);
	AddHitBox(button_start_position, FVector2D(button_current_start_texture_asset->GetSurfaceWidth() * scale.X, button_current_start_texture_asset->GetSurfaceHeight() * scale.Y), hit_box_start_button_name, false);
	AddHitBox(button_quit_position, FVector2D(button_current_quit_texture_asset->GetSurfaceWidth() * scale.X, button_current_quit_texture_asset->GetSurfaceHeight() * scale.Y), hit_box_quit_button_name, false);
	if (clicked) {
		player_controller->SetMouseLocation(mouse_x, mouse_y);
	}
}
void Ahud_main_menu::NotifyHitBoxClick(FName hit_box_name) {
	Super::NotifyHitBoxClick(hit_box_name);
	if (hit_box_name == FName("hit_box_button_start")) {
		player_controller->bShowMouseCursor = false;
		player_controller->bEnableClickEvents = false;
		audio_component_click_button = UGameplayStatics::SpawnSound2D(world, sound_asset_click_button_sound);
		duration_clicked_sound = sound_asset_click_button_sound->GetDuration();
		FTimerHandle timer_handle_start_button;
		GetWorldTimerManager().SetTimer(timer_handle_start_button, this, &Ahud_main_menu::start_level, duration_clicked_sound, false);
		player_controller->GetMousePosition(mouse_x, mouse_y);
		clicked = true;
	}
	else if (hit_box_name == FName("hit_box_button_quit")) {
		player_controller->bShowMouseCursor = false;
		player_controller->bEnableClickEvents = false;
		audio_component_click_button = UGameplayStatics::SpawnSound2D(world, sound_asset_click_button_sound);
		duration_clicked_sound = sound_asset_click_button_sound->GetDuration();
		FTimerHandle timer_handle_start_button;
		GetWorldTimerManager().SetTimer(timer_handle_start_button, this, &Ahud_main_menu::quit_game, duration_clicked_sound, false);
		player_controller->GetMousePosition(mouse_x, mouse_y);
		clicked = true;
	}
}
void Ahud_main_menu::NotifyHitBoxBeginCursorOver(FName hit_box_name){
	ReceiveHitBoxBeginCursorOver(hit_box_name);
	if (hit_box_name == FName("hit_box_button_start")) {
		button_current_start_texture_asset = button_light_texture_asset;
		audio_component_cursor_over_button = UGameplayStatics::SpawnSound2D(world, sound_asset_cursor_over_button);
	}
	else if (hit_box_name == FName("hit_box_button_quit")) {
		audio_component_cursor_over_button = UGameplayStatics::SpawnSound2D(world, sound_asset_cursor_over_button);
		button_current_quit_texture_asset = button_light_texture_asset;
	}
}
void Ahud_main_menu::NotifyHitBoxEndCursorOver(FName hit_box_name){
	ReceiveHitBoxEndCursorOver(hit_box_name);
	if (hit_box_name == FName("hit_box_button_start")) {
		button_current_start_texture_asset = button_normal_texture_asset;
	}
	else if (hit_box_name == FName("hit_box_button_quit")) {
		button_current_quit_texture_asset = button_normal_texture_asset;
	}
}
void Ahud_main_menu::EndPlay(EEndPlayReason::Type reason) {
	Super::EndPlay(reason);
	audio_component_main_menu->Stop();
}
void Ahud_main_menu::start_level() {
	next_level_name = "level_arena";
	options = "?Game=/Script/game_project.game_mode_base_level_arena";
	UGameplayStatics::OpenLevel(world, next_level_name, false, options);
}
void Ahud_main_menu::quit_game() {
	player_controller->ConsoleCommand("quit");
}