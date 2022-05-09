// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GameFramework/HUD.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInterface.h"
#include "Engine/UserDefinedStruct.h"
#include "plane_struct.h"

#include "game_mode_base_level_1.generated.h"

class Astatic_mesh_plane;

UCLASS()
class GAME_PROJECT_API Agame_mode_base_level_1 : public AGameModeBase
{
	GENERATED_BODY()
public:
	Agame_mode_base_level_1();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	UPROPERTY() UWorld* world;
	UPROPERTY() Astatic_mesh_plane* temp_static_mesh_plane;
	UPROPERTY() TArray<FFplane_struct> floor_0_array;
	UPROPERTY() TArray<FFplane_struct> wall_0_right_array;
	UPROPERTY() TArray<FFplane_struct> wall_0_back_array;
	UPROPERTY() TArray<FFplane_struct> wall_0_left_array;
	UPROPERTY() TArray<FFplane_struct> wall_0_front_array;
	UPROPERTY() TArray<FFplane_struct> ceiling_0_array;
	UPROPERTY() TArray<FFplane_struct> stair_0_riser_up_array;
	UPROPERTY() TArray<FFplane_struct> stair_0_tread_up_array;
	UPROPERTY() TArray<Astatic_mesh_plane*> stair_0_stringer_left_array;
	UPROPERTY() TArray<FFplane_struct> stair_0_riser_bottom_array;
	UPROPERTY() TArray<FFplane_struct> stair_0_tread_bottom_array;
	UPROPERTY() TSubclassOf<Astatic_mesh_plane> static_mesh_plane_class;
	UPROPERTY() UMaterialInterface* material_asset;
	UPROPERTY() TSubclassOf<AGameModeBase> game_mode_class_base;
	UPROPERTY() int32 floor_0_row_count = 50;
	UPROPERTY() int32 floor_0_column_count = 50;
	UPROPERTY() int32 wall_0_right_row_count = 30;
	UPROPERTY() int32 wall_0_right_column_count = floor_0_row_count;
	UPROPERTY() int32 wall_0_back_row_count = wall_0_right_row_count;
	UPROPERTY() int32 wall_0_back_column_count = floor_0_column_count;
	UPROPERTY() int32 wall_0_left_row_count = wall_0_back_row_count;
	UPROPERTY() int32 wall_0_left_column_count = floor_0_row_count;
	UPROPERTY() int32 wall_0_front_row_count = wall_0_left_row_count;
	UPROPERTY() int32 wall_0_front_column_count = wall_0_back_column_count;
	UPROPERTY() int32 ceiling_0_row_count = wall_0_left_column_count;
	UPROPERTY() int32 ceiling_0_column_count = wall_0_front_column_count;
	UPROPERTY() int32 stair_0_riser_up_row_count = 8;
	UPROPERTY() int32 stair_0_riser_up_column_count = 16; // It should be multiple of 4.
	UPROPERTY() int32 stair_0_tread_up_row_count = stair_0_riser_up_row_count;
	UPROPERTY() int32 stair_0_tread_up_column_count = stair_0_riser_up_column_count;
	UPROPERTY() int32 stair_0_stringer_left_count = stair_0_riser_up_column_count;
	UPROPERTY() int32 stair_0_riser_bottom_row_count = stair_0_tread_up_row_count;
	UPROPERTY() int32 stair_0_riser_bottom_column_count = stair_0_stringer_left_count;
	UPROPERTY() int32 stair_0_tread_bottom_row_count = stair_0_riser_bottom_row_count;
	UPROPERTY() int32 stair_0_tread_bottom_column_count = stair_0_riser_bottom_column_count;
	UPROPERTY() float plane_size;
	UPROPERTY() float initial_floor_0_location_x = 0.0f;
	UPROPERTY() float initial_floor_0_location_y = 0.0f;
	UPROPERTY() float initial_floor_0_location_z = 0.0f;
	UPROPERTY() float initial_wall_0_right_location_x;
	UPROPERTY() float initial_wall_0_right_location_y;
	UPROPERTY() float initial_wall_0_right_location_z;
	UPROPERTY() float initial_wall_0_back_location_x;
	UPROPERTY() float initial_wall_0_back_location_y;
	UPROPERTY() float initial_wall_0_back_location_z;
	UPROPERTY() float initial_wall_0_left_location_x;
	UPROPERTY() float initial_wall_0_left_location_y;
	UPROPERTY() float initial_wall_0_left_location_z;
	UPROPERTY() float initial_wall_0_front_location_x;
	UPROPERTY() float initial_wall_0_front_location_y;
	UPROPERTY() float initial_wall_0_front_location_z;
	UPROPERTY() float initial_ceiling_0_location_x;
	UPROPERTY() float initial_ceiling_0_location_y;
	UPROPERTY() float initial_ceiling_0_location_z;
	UPROPERTY() float initial_stair_0_riser_up_location_x;
	UPROPERTY() float initial_stair_0_riser_up_location_y;
	UPROPERTY() float initial_stair_0_riser_up_location_z;
	UPROPERTY() float initial_stair_0_tread_up_location_x;
	UPROPERTY() float initial_stair_0_tread_up_location_y;
	UPROPERTY() float initial_stair_0_tread_up_location_z;
	UPROPERTY() float initial_stair_0_riser_bottom_location_x;
	UPROPERTY() float initial_stair_0_riser_bottom_location_y;
	UPROPERTY() float initial_stair_0_riser_bottom_location_z;
	UPROPERTY() float initial_stair_0_tread_bottom_location_x;
	UPROPERTY() float initial_stair_0_tread_bottom_location_y;
	UPROPERTY() float initial_stair_0_tread_bottom_location_z;
	UPROPERTY() float initial_stair_0_stringer_left_location_x;
	UPROPERTY() float initial_stair_0_stringer_left_location_y;
	UPROPERTY() float initial_stair_0_stringer_left_location_z;
	UPROPERTY() float last_floor_0_location_x;
	UPROPERTY() float last_floor_0_location_y;
	UPROPERTY() float last_floor_0_location_z;
	UPROPERTY() float last_wall_0_right_location_x;
	UPROPERTY() float last_wall_0_right_location_y;
	UPROPERTY() float last_wall_0_right_location_z;
	UPROPERTY() float last_wall_0_back_location_x;
	UPROPERTY() float last_wall_0_back_location_y;
	UPROPERTY() float last_wall_0_back_location_z;
	UPROPERTY() float last_wall_0_left_location_x;
	UPROPERTY() float last_wall_0_left_location_y;
	UPROPERTY() float last_wall_0_left_location_z;
	UPROPERTY() float last_wall_0_front_location_x;
	UPROPERTY() float last_wall_0_front_location_y;
	UPROPERTY() float last_wall_0_front_location_z;
	UPROPERTY() float last_ceiling_0_location_x;
	UPROPERTY() float last_ceiling_0_location_y;
	UPROPERTY() float last_ceiling_0_location_z;
	UPROPERTY() float last_stair_0_riser_up_location_x;
	UPROPERTY() float last_stair_0_riser_up_location_y;
	UPROPERTY() float last_stair_0_riser_up_location_z;
	UPROPERTY() float last_stair_0_tread_up_location_x;
	UPROPERTY() float last_stair_0_tread_up_location_y;
	UPROPERTY() float last_stair_0_tread_up_location_z;
	UPROPERTY() float last_stair_0_riser_bottom_location_x;
	UPROPERTY() float last_stair_0_riser_bottom_location_y;
	UPROPERTY() float last_stair_0_riser_bottom_location_z;
	UPROPERTY() float last_stair_0_tread_bottom_location_x;
	UPROPERTY() float last_stair_0_tread_bottom_location_y;
	UPROPERTY() float last_stair_0_tread_bottom_location_z;
	UPROPERTY() float last_stair_0_stringer_left_location_x;
	UPROPERTY() float last_stair_0_stringer_left_location_y;
	UPROPERTY() float last_stair_0_stringer_left_location_z;
	UPROPERTY() float temp_location_x;
	UPROPERTY() float temp_location_y;
	UPROPERTY() float temp_location_z;
	UPROPERTY() FRotator floor_rotation = FRotator(0.0f);
	UPROPERTY() FRotator wall_right_rotation = FRotator(0.0f, 0.0f, 270.0f); // FRotator(270.0f, 180.0f, 0.0f);
	UPROPERTY() FRotator wall_back_rotation = FRotator(0.0f, 90.0f, 270.0f);
	UPROPERTY() FRotator wall_left_rotation = FRotator(0.0f, 0.0f, 90.0f);
	UPROPERTY() FRotator wall_front_rotation = FRotator(90.0f, 0.0f, 0.0f);
	UPROPERTY() FRotator ceiling_rotation = FRotator(180.0f, 0.0f, 0.0f);

};
