// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GameFramework/HUD.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInterface.h"
#include "plane_struct_field.h"
#include "Engine/PlayerStartPIE.h"
#include "static_mesh_plane.h"
#include "player_start.h"
#include "paper_player.h"
#include "Kismet/GameplayStatics.h"


#include "game_mode_base_level_arena.generated.h"

class Astatic_mesh_plane;
class Apaper_player;
class Aplayer_start;
class Aplayer_state;
class Agame_state_base;
UENUM()
enum direction
{
	front, right, back, left,
};
UCLASS()
class GAME_PROJECT_API Agame_mode_base_level_arena : public AGameModeBase
{
	GENERATED_BODY()
public:
	Agame_mode_base_level_arena();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;
	virtual void StartPlay() override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* player) override;
	UPROPERTY() UWorld* world;
	UPROPERTY() Astatic_mesh_plane* temp_static_mesh_plane;
	UPROPERTY() AActor* default_player_start_PIE;
	UPROPERTY() Aplayer_start* player_start;
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() APawn* pawn;
	UPROPERTY() Apaper_player* paper_player;
	UPROPERTY() TSubclassOf<APawn> pawn_class;
	UPROPERTY() TSubclassOf<AHUD> hud_combat_class;
	UPROPERTY() TSubclassOf<AHUD> hud_ending_class;
	UPROPERTY() TSubclassOf<Aplayer_state> player_state_class;
	UPROPERTY() TSubclassOf<Agame_state_base> game_state_base_class;
	UPROPERTY() TSubclassOf<Astatic_mesh_plane> static_mesh_plane_class;
	UPROPERTY() TSubclassOf<Apaper_player> paper_player_class;
	UPROPERTY() TSubclassOf<Aplayer_start> player_start_class;
	UPROPERTY() TArray<Fplane_struct> room_0_array;
	UPROPERTY() TArray<Fplane_struct> floor_0_array;
	UPROPERTY() TArray<Fplane_struct> floor_1_array;
	UPROPERTY() TArray<Fplane_struct> floor_2_array;
	UPROPERTY() TArray<Fplane_struct> floor_3_array;
	UPROPERTY() TArray<Fplane_struct> floor_4_array;
	UPROPERTY() TArray<Fplane_struct> floor_5_array;
	UPROPERTY() TArray<Fplane_struct> floor_6_array;
	UPROPERTY() TArray<Fplane_struct> floor_7_array;
	UPROPERTY() TArray<Fplane_struct> floor_8_array;
	UPROPERTY() TArray<Fplane_struct> pillar_0_array;
	UPROPERTY() TArray<Fplane_struct> pillar_1_array;
	UPROPERTY() TArray<Fplane_struct> pillar_2_array;
	UPROPERTY() TArray<Fplane_struct> pillar_3_array;
	UPROPERTY() TArray<Fplane_struct> pillar_4_array;
	UPROPERTY() TArray<Fplane_struct> pillar_5_array;
	UPROPERTY() TArray<Fplane_struct> pillar_6_array;
	UPROPERTY() TArray<Fplane_struct> pillar_7_array;
	UPROPERTY() TArray<Fplane_struct> stair_0_array;
	UPROPERTY() TArray<Fplane_struct> stair_1_array;
	UPROPERTY() TArray<Fplane_struct> stair_2_array;
	UPROPERTY() TArray<Fplane_struct> stair_3_array;
	UPROPERTY() TArray<Fplane_struct> stair_4_array;
	UPROPERTY() TArray<Fplane_struct> stair_5_array;
	UPROPERTY() UMaterialInterface* material_asset;
	UPROPERTY() UMaterialInterface* material_asset_2;
	UPROPERTY() UMaterialInterface* material_asset_3;
	UPROPERTY() FIntVector room_0_xyz = FIntVector(42, 38, 18);
	UPROPERTY() FIntVector floor_0_xyz;
	UPROPERTY() FIntVector floor_1_xyz;
	UPROPERTY() FIntVector floor_2_xyz;
	UPROPERTY() FIntVector floor_3_xyz;
	UPROPERTY() FIntVector floor_4_xyz;
	UPROPERTY() FIntVector floor_5_xyz;
	UPROPERTY() FIntVector floor_6_xyz;
	UPROPERTY() FIntVector floor_7_xyz;
	UPROPERTY() FIntVector floor_8_xyz;
	UPROPERTY() FIntVector pillar_0_xyz;
	UPROPERTY() FIntVector pillar_1_xyz;
	UPROPERTY() FIntVector pillar_2_xyz;
	UPROPERTY() FIntVector pillar_3_xyz;
	UPROPERTY() FIntVector pillar_4_xyz;
	UPROPERTY() FIntVector pillar_5_xyz;
	UPROPERTY() FIntVector pillar_6_xyz;
	UPROPERTY() FIntVector pillar_7_xyz;
	UPROPERTY() FIntVector stair_0_xyz = FIntVector(12, 7, 12);
	UPROPERTY() FIntVector stair_1_xyz;
	UPROPERTY() FIntVector stair_2_xyz;
	UPROPERTY() FIntVector stair_3_xyz;
	UPROPERTY() FIntVector stair_4_xyz;
	UPROPERTY() FIntVector stair_5_xyz;
	UPROPERTY() FVector initial_room_0_location = FVector(0.0f);
	UPROPERTY() FVector initial_floor_0_location;
	UPROPERTY() FVector initial_floor_1_location;
	UPROPERTY() FVector initial_floor_2_location;
	UPROPERTY() FVector initial_floor_3_location;
	UPROPERTY() FVector initial_floor_4_location;
	UPROPERTY() FVector initial_floor_5_location;
	UPROPERTY() FVector initial_floor_6_location;
	UPROPERTY() FVector initial_floor_7_location;
	UPROPERTY() FVector initial_floor_8_location;
	UPROPERTY() FVector initial_pillar_0_location;
	UPROPERTY() FVector initial_pillar_1_location;
	UPROPERTY() FVector initial_pillar_2_location;
	UPROPERTY() FVector initial_pillar_3_location;
	UPROPERTY() FVector initial_pillar_4_location;
	UPROPERTY() FVector initial_pillar_5_location;
	UPROPERTY() FVector initial_pillar_6_location;
	UPROPERTY() FVector initial_pillar_7_location;
	UPROPERTY() FVector initial_stair_0_location;
	UPROPERTY() FVector initial_stair_1_location;
	UPROPERTY() FVector initial_stair_2_location;
	UPROPERTY() FVector initial_stair_3_location;
	UPROPERTY() FVector initial_stair_4_location;
	UPROPERTY() FVector initial_stair_5_location;
	UPROPERTY() TEnumAsByte<direction> room_0_direction = front;
	UPROPERTY() TEnumAsByte<direction> floor_0_direction = front;
	UPROPERTY() TEnumAsByte<direction> floor_1_direction = right;
	UPROPERTY() TEnumAsByte<direction> floor_2_direction = right;
	UPROPERTY() TEnumAsByte<direction> floor_3_direction = back;
	UPROPERTY() TEnumAsByte<direction> floor_4_direction = back;
	UPROPERTY() TEnumAsByte<direction> floor_5_direction = left;
	UPROPERTY() TEnumAsByte<direction> floor_6_direction = back;
	UPROPERTY() TEnumAsByte<direction> floor_7_direction = left;
	UPROPERTY() TEnumAsByte<direction> floor_8_direction = right;
	UPROPERTY() TEnumAsByte<direction> pillar_0_direction = left;
	UPROPERTY() TEnumAsByte<direction> pillar_1_direction = back;
	UPROPERTY() TEnumAsByte<direction> pillar_2_direction = right;
	UPROPERTY() TEnumAsByte<direction> pillar_3_direction = front;
	UPROPERTY() TEnumAsByte<direction> pillar_4_direction = right;
	UPROPERTY() TEnumAsByte<direction> pillar_5_direction = back;
	UPROPERTY() TEnumAsByte<direction> pillar_6_direction = right;
	UPROPERTY() TEnumAsByte<direction> pillar_7_direction = front;
	UPROPERTY() TEnumAsByte<direction> stair_0_direction = front;
	UPROPERTY() TEnumAsByte<direction> stair_1_direction = right;
	UPROPERTY() TEnumAsByte<direction> stair_2_direction = back;
	UPROPERTY() TEnumAsByte<direction> stair_3_direction = back;
	UPROPERTY() TEnumAsByte<direction> stair_4_direction = back;
	UPROPERTY() TEnumAsByte<direction> stair_5_direction = left;
	UPROPERTY() FRotator floor_rotation = FRotator(0.0f);
	UPROPERTY() FRotator ceiling_rotation = FRotator(180.0f, 0.0f, 0.0f);
	UPROPERTY() FRotator wall_left_rotation = FRotator(0.0f, 0.0f, 90.0f);
	UPROPERTY() FRotator wall_right_rotation = FRotator(0.0f, 180.0f, 90.0f);
	UPROPERTY() FRotator wall_back_rotation = FRotator(0.0f, 270.0f, 90.0f);
	UPROPERTY() FRotator wall_front_rotation = FRotator(0.0f, 90.0f, 90.0f);
	UPROPERTY() FVector stair_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector room_0_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector room_0_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector room_0_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_0_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_0_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_0_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_1_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_1_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_1_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_2_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_2_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_2_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_3_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_3_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_3_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_4_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_4_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_4_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_5_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_5_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_5_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_6_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_6_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_6_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_7_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_7_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_7_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_8_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector floor_8_xz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector floor_8_yz_scale = FVector(1.0f, 0.25f, 1.0f);
	UPROPERTY() FVector pillar_0_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_0_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_0_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_1_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_1_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_1_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_2_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_2_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_2_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_3_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_3_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_3_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_4_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_4_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_4_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_5_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_5_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_5_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_6_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_6_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_6_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_7_xy_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_7_xz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() FVector pillar_7_yz_scale = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY() float plane_size;
	UPROPERTY() bool dead = false;
	UPROPERTY() int32 stair_0_initial_gap = 12;
	UPROPERTY() int32 floor_1_length = 13;
	UPROPERTY() int32 floor_3_length = 10;
	UFUNCTION() void set_num(TArray<Fplane_struct>& box_array, int32 face_count, FIntVector xyz);
	UFUNCTION() void spawn_plane(TArray<Fplane_struct>& box_array, FVector initial_location, FVector scale_xy, FVector scale_xz, FVector scale_yz, FIntVector xyz, float distance, bool inside, TEnumAsByte<direction> plane_direction);
	UFUNCTION() void spawn_stair(TArray<Fplane_struct>& stair_array, FVector initial_location, float distance, FIntVector xyz, FVector scale, TEnumAsByte<direction> stair_direction);
	UFUNCTION() void implement_hud_ending();
};
