// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "main_menu_hud.h"

Amain_menu_hud::Amain_menu_hud() {
	//static ConstructorHelpers::FObjectFinder<UTexture2D> crosshair_texture_object(TEXT("/Game/hud/crosshair_v1.crosshair_v1"));
	//crosshair_texture = crosshair_texture_object.Object;
	//FTextBlockStyle
	world = GetWorld();
	start_button_texture_asset = LoadObject<UTexture>(world, TEXT("/Game/textures/button_start_v1.button_start_v1"));
	quit_button_texture_asset = LoadObject<UTexture>(world, TEXT("/Game/textures/button_quit_v1.button_quit_v1"));
	game_mode_base_level_arena_class = LoadClass<AGameModeBase>(GetWorld(), TEXT("/Script/game_project.game_mode_base_level_arena"));
	
}

void Amain_menu_hud::DrawHUD() {
	Super::DrawHUD();
	float button_gap = 175.0f;
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D start_button_position(Center.X - (start_button_texture_asset->GetSurfaceWidth() * 0.5f), Center.Y - (start_button_texture_asset->GetSurfaceHeight() * 0.5f) - button_gap / 2);
	FVector2D quit_button_position(Center.X - (quit_button_texture_asset->GetSurfaceWidth() * 0.5f), Center.Y - (quit_button_texture_asset->GetSurfaceHeight() * 0.5f) + button_gap / 2);
	player_controller = UGameplayStatics::GetPlayerController(world, 0);
	player_controller->bShowMouseCursor = true;
	player_controller->bEnableClickEvents = true;
	DrawRect(FColor(18, 18, 18), 0.0f, 0.0f, Canvas->ClipX, Canvas->ClipY);
	DrawTextureSimple(start_button_texture_asset, start_button_position.X, start_button_position.Y, 1.0f);
	DrawTextureSimple(quit_button_texture_asset, quit_button_position.X, quit_button_position.Y, 1.0f);
	AddHitBox(start_button_position, FVector2D(start_button_texture_asset->GetSurfaceWidth(), start_button_texture_asset->GetSurfaceHeight()), FName("hit_box_start_button"), false);
	AddHitBox(quit_button_position, FVector2D(quit_button_texture_asset->GetSurfaceWidth(), quit_button_texture_asset->GetSurfaceHeight()), FName("hit_box_quit_button"), false);
	//ReceiveHitBoxClick(FName("HitBox"));
	

}
void Amain_menu_hud::NotifyHitBoxClick(FName hit_box_name) {
	Super::NotifyHitBoxClick(hit_box_name);
	if (hit_box_name == FName("hit_box_start_button")) {
		FString current_level_name = world->GetMapName();
		current_level_name.RemoveFromStart(world->StreamingLevelsPrefix);
		FName new_level_name = "level_arena";
		FString options = "?Game=/Script/game_project.game_mode_base_level_arena";
		UGameplayStatics::OpenLevel(world, new_level_name, false, options);
	}
	else if (hit_box_name == FName("hit_box_quit_button")) {
		UGameplayStatics::GetPlayerController(world, 0)->ConsoleCommand("quit");
	}

}