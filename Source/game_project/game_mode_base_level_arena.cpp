// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_mode_base_level_arena.h"
#include "hud_main_menu.h"
#include "player_state.h"
#include "game_state_base.h"

Agame_mode_base_level_arena::Agame_mode_base_level_arena() {
    PrimaryActorTick.bCanEverTick = true;
    world = GetWorld();
    pawn_class = LoadClass<APawn>(world, TEXT("/Script/game_project.paper_player"));
    check(pawn_class != nullptr);
    DefaultPawnClass = pawn_class;
    hud_combat_class = LoadClass<AHUD>(world, TEXT("/Script/game_project.hud_combat"));
    check(hud_combat_class != nullptr);
    HUDClass = hud_combat_class;
    hud_ending_class = LoadClass<AHUD>(world, TEXT("/Script/game_project.hud_ending"));
    check(hud_ending_class != nullptr);
    player_state_class = LoadClass<Aplayer_state>(world, TEXT("/Script/game_project.player_state"));
    check(player_state_class != nullptr);
    PlayerStateClass = player_state_class;
    game_state_base_class = LoadClass<Agame_state_base>(world, TEXT("/Script/game_project.game_state_base"));
    check(game_state_base_class != nullptr);
    GameStateClass = game_state_base_class;
    static_mesh_plane_class = LoadClass<Astatic_mesh_plane>(world, TEXT("/Script/game_project.static_mesh_plane"));
    material_asset = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_test.plane_material_instance_test"));
    paper_player_class = LoadClass<Apaper_player>(world, TEXT("/Script/game_project.paper_player"));
    player_start_class = LoadClass<Aplayer_start>(world, TEXT("/Script/game_project.player_start"));
}
void Agame_mode_base_level_arena::BeginPlay() {
    Super::BeginPlay();
    FTransform local_to_world;
    temp_static_mesh_plane = GetWorld()->SpawnActor<Astatic_mesh_plane>();
    plane_size = ((temp_static_mesh_plane->GetStaticMeshComponent()->CalcBounds(local_to_world).BoxExtent).X) * 2; // plane_size = 10
    temp_static_mesh_plane->Destroy();
    set_num(room_0_array, 6, room_0_xyz); // Starting to create Room 0.
    spawn_plane(room_0_array, initial_room_0_location, room_0_xy_scale, room_0_xz_scale, room_0_yz_scale, room_0_xyz, plane_size, true, room_0_direction);
    set_num(stair_0_array, 6, stair_0_xyz); // Starting to create Stair 0.
    initial_stair_0_location = FVector(room_0_array[0].row[stair_0_initial_gap].column[0]->GetActorLocation().X, 0.0f, 0.0f);
    spawn_stair(stair_0_array, initial_stair_0_location, plane_size, stair_0_xyz, stair_scale, stair_0_direction);
    floor_0_xyz = FIntVector(room_0_xyz.X - stair_0_xyz.X - stair_0_initial_gap, stair_0_xyz.Y, 1); // Starting to create Floor 0.
    set_num(floor_0_array, 6, floor_0_xyz);
    initial_floor_0_location = FVector(stair_0_array[0].row[stair_0_xyz.X - 1].column[0]->GetActorLocation().X + plane_size, stair_0_array[0].row[stair_0_xyz.X - 1].column[0]->GetActorLocation().Y, stair_0_array[0].row[stair_0_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_plane(floor_0_array, initial_floor_0_location, floor_0_xy_scale, floor_0_xz_scale, floor_0_yz_scale, floor_0_xyz, plane_size, false, floor_0_direction);
    floor_1_xyz = FIntVector(stair_0_xyz.Y, floor_1_length, 1); // Starting to create Floor 1.
    set_num(floor_1_array, 6, floor_1_xyz);
    initial_floor_1_location = FVector(floor_0_array[0].row[floor_0_xyz.X - 1].column[floor_0_xyz.Y - 1]->GetActorLocation().X, floor_0_array[0].row[floor_0_xyz.X - 1].column[floor_0_xyz.Y - 1]->GetActorLocation().Y + plane_size, floor_0_array[0].row[floor_0_xyz.X - 1].column[floor_0_xyz.Y - 1]->GetActorLocation().Z);
    spawn_plane(floor_1_array, initial_floor_1_location, floor_1_xy_scale, floor_1_xz_scale, floor_1_yz_scale, floor_1_xyz, plane_size, false, floor_1_direction);
    stair_1_xyz = FIntVector(stair_0_xyz.Y, stair_0_xyz.X, stair_0_xyz.X); // Starting to create Stair 1.
    set_num(stair_1_array, 6, stair_1_xyz);
    initial_stair_1_location = FVector(floor_1_array[1].row[0].column[floor_1_xyz.Y - 1]->GetActorLocation().X, floor_1_array[1].row[0].column[floor_1_xyz.Y - 1]->GetActorLocation().Y + plane_size, floor_1_array[1].row[0].column[floor_1_xyz.Y - 1]->GetActorLocation().Z);
    spawn_stair(stair_1_array, initial_stair_1_location, plane_size, stair_1_xyz, stair_scale, stair_1_direction);
    floor_2_xyz = FIntVector(stair_1_xyz.X, room_0_xyz.Y - floor_0_xyz.Y - floor_1_xyz.Y - stair_1_xyz.Y, 1); // Starting to create Floor 2.
    set_num(floor_2_array, 6, floor_2_xyz);
    initial_floor_2_location = FVector(stair_1_array[0].row[0].column[stair_1_xyz.Y - 1]->GetActorLocation().X, stair_1_array[0].row[0].column[stair_1_xyz.Y - 1]->GetActorLocation().Y + plane_size, stair_1_array[0].row[0].column[stair_1_xyz.Y - 1]->GetActorLocation().Z);
    spawn_plane(floor_2_array, initial_floor_2_location, floor_2_xy_scale, floor_2_xz_scale, floor_2_yz_scale, floor_2_xyz, plane_size, false, floor_2_direction);
    floor_3_xyz = FIntVector(floor_3_length, floor_2_xyz.Y + 1, 1); // Starting to create Floor 3.
    set_num(floor_3_array, 6, floor_3_xyz);
    initial_floor_3_location = FVector(floor_2_array[0].row[floor_2_xyz.X - 1].column[floor_2_xyz.Y - 1]->GetActorLocation().X - plane_size, floor_2_array[0].row[floor_2_xyz.X - 1].column[floor_2_xyz.Y - 1]->GetActorLocation().Y, floor_2_array[0].row[floor_2_xyz.X - 1].column[floor_2_xyz.Y - 1]->GetActorLocation().Z);
    spawn_plane(floor_3_array, initial_floor_3_location, floor_3_xy_scale, floor_3_xz_scale, floor_3_yz_scale, floor_3_xyz, plane_size, false, floor_3_direction);
    stair_2_xyz = FIntVector(stair_0_xyz.X, stair_0_xyz.Y, stair_0_xyz.X); // Starting to create Stair 2.
    set_num(stair_2_array, 6, stair_2_xyz);
    initial_stair_2_location = FVector(floor_3_array[1].row[floor_3_xyz.X - 1].column[floor_3_xyz.Y - 1]->GetActorLocation().X - plane_size, floor_3_array[1].row[floor_3_xyz.X - 1].column[floor_3_xyz.Y - 1]->GetActorLocation().Y, floor_3_array[1].row[floor_3_xyz.X - 1].column[floor_3_xyz.Y - 1]->GetActorLocation().Z);
    spawn_stair(stair_2_array, initial_stair_2_location, plane_size, stair_2_xyz, stair_scale, stair_2_direction);
    floor_4_xyz = FIntVector(room_0_xyz.X - floor_3_xyz.X - floor_2_xyz.X - stair_2_xyz.X, stair_2_xyz.Y, 1); // Starting to create Floor 4.
    set_num(floor_4_array, 6, floor_4_xyz);
    initial_floor_4_location = FVector(stair_2_array[0].row[stair_2_xyz.X - 1].column[stair_2_xyz.Y - 1]->GetActorLocation().X - plane_size, stair_2_array[0].row[stair_2_xyz.X - 1].column[stair_2_xyz.Y - 1]->GetActorLocation().Y, stair_2_array[0].row[stair_2_xyz.X - 1].column[stair_2_xyz.Y - 1]->GetActorLocation().Z);
    spawn_plane(floor_4_array, initial_floor_4_location, floor_4_xy_scale, floor_4_xz_scale, floor_4_yz_scale, floor_4_xyz, plane_size, false, floor_4_direction);
    floor_5_xyz = FIntVector(floor_4_xyz.Y, room_0_xyz.Y - floor_4_xyz.Y, 1); // Starting to create Floor 5.
    set_num(floor_5_array, 6, floor_5_xyz);
    initial_floor_5_location = FVector(floor_4_array[0].row[floor_4_xyz.X - 1].column[floor_4_xyz.Y - 1]->GetActorLocation().X, floor_4_array[0].row[floor_4_xyz.X - 1].column[floor_4_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_4_array[0].row[floor_4_xyz.X - 1].column[floor_4_xyz.Y - 1]->GetActorLocation().Z);
    spawn_plane(floor_5_array, initial_floor_5_location, floor_5_xy_scale, floor_5_xz_scale, floor_5_yz_scale, floor_5_xyz, plane_size, false, floor_5_direction);
    pillar_0_xyz = FIntVector(3, 3, room_0_xyz.Z); // Starting to create Pillar 0.
    set_num(pillar_0_array, 6, pillar_0_xyz);
    initial_pillar_0_location = FVector(floor_5_array[0].row[floor_5_xyz.X - 1].column[0]->GetActorLocation().X + plane_size, floor_5_array[0].row[floor_5_xyz.X - 1].column[0]->GetActorLocation().Y, 0.0f);
    spawn_plane(pillar_0_array, initial_pillar_0_location, pillar_0_xy_scale, pillar_0_xz_scale, pillar_0_yz_scale, pillar_0_xyz, plane_size, false, pillar_0_direction);
    pillar_1_xyz = FIntVector(3, 3, room_0_xyz.Z); // Starting to create Pillar 1.
    set_num(pillar_1_array, 6, pillar_1_xyz);
    initial_pillar_1_location = FVector(floor_3_array[0].row[0].column[floor_3_xyz.Y - 1]->GetActorLocation().X, floor_3_array[0].row[0].column[floor_3_xyz.Y - 1]->GetActorLocation().Y - plane_size, 0.0f);
    spawn_plane(pillar_1_array, initial_pillar_1_location, pillar_1_xy_scale, pillar_1_xz_scale, pillar_1_yz_scale, pillar_1_xyz, plane_size, false, pillar_1_direction);
    pillar_2_xyz = FIntVector(3, 3, room_0_xyz.Z); // Starting to create Pillar 2.
    set_num(pillar_2_array, 6, pillar_2_xyz);
    initial_pillar_2_location = FVector(floor_1_array[0].row[floor_1_xyz.X - 1].column[0]->GetActorLocation().X - plane_size, floor_1_array[0].row[floor_1_xyz.X - 1].column[0]->GetActorLocation().Y, 0.0f);
    spawn_plane(pillar_2_array, initial_pillar_2_location, pillar_2_xy_scale, pillar_2_xz_scale, pillar_2_yz_scale, pillar_2_xyz, plane_size, false, pillar_2_direction);
    pillar_3_xyz = FIntVector(3, 3, room_0_xyz.Z); // Starting to create Pillar 2.
    set_num(pillar_3_array, 6, pillar_3_xyz);
    initial_pillar_3_location = FVector(pillar_0_array[0].row[0].column[0]->GetActorLocation().X, pillar_2_array[0].row[0].column[0]->GetActorLocation().Y, 0.0f);
    spawn_plane(pillar_3_array, initial_pillar_3_location, pillar_3_xy_scale, pillar_3_xz_scale, pillar_3_yz_scale, pillar_3_xyz, plane_size, false, pillar_3_direction);
    stair_3_xyz = FIntVector(stair_2_xyz.X, stair_2_xyz.Y, stair_2_xyz.Z); // Starting to create Stair 3.
    set_num(stair_3_array, 6, stair_3_xyz);
    initial_stair_3_location = FVector(pillar_2_array[0].row[0].column[pillar_2_xyz.Y - 1]->GetActorLocation().X, pillar_2_array[1].row[0].column[pillar_2_xyz.Y - 1]->GetActorLocation().Y + plane_size, stair_1_array[0].row[0].column[0]->GetActorLocation().Z);
    spawn_stair(stair_3_array, initial_stair_3_location, plane_size, stair_3_xyz, stair_scale, stair_3_direction);
    floor_6_xyz = FIntVector(room_0_xyz.X - floor_5_xyz.X - floor_2_xyz.X - 2 * stair_3_xyz.X, stair_3_xyz.Y, 1); // Starting to create Floor 6.
    set_num(floor_6_array, 6, floor_6_xyz);
    initial_floor_6_location = FVector(stair_3_array[0].row[stair_3_xyz.X - 1].column[stair_3_xyz.Y - 1]->GetActorLocation().X - plane_size, stair_3_array[0].row[stair_3_xyz.X - 1].column[stair_3_xyz.Y - 1]->GetActorLocation().Y, stair_3_array[0].row[stair_3_xyz.X - 1].column[stair_3_xyz.Y - 1]->GetActorLocation().Z);
    spawn_plane(floor_6_array, initial_floor_6_location, floor_6_xy_scale, floor_6_xz_scale, floor_6_yz_scale, floor_6_xyz, plane_size, false, floor_6_direction);
    stair_4_xyz = FIntVector(stair_3_xyz.X, stair_3_xyz.Y, stair_3_xyz.Z); // Starting to create Stair 4.
    set_num(stair_4_array, 6, stair_4_xyz);
    initial_stair_4_location = FVector(floor_6_array[0].row[floor_6_xyz.X - 1].column[floor_6_xyz.Y - 1]->GetActorLocation().X - plane_size, floor_6_array[1].row[floor_6_xyz.X - 1].column[floor_6_xyz.Y - 1]->GetActorLocation().Y, floor_6_array[1].row[0].column[floor_6_xyz.Y - 1]->GetActorLocation().Z);
    spawn_stair(stair_4_array, initial_stair_4_location, plane_size, stair_4_xyz, stair_scale, stair_4_direction);
    stair_5_xyz = FIntVector(stair_1_xyz.X, stair_1_xyz.Y, stair_1_xyz.Z); // Starting to create Stair 5.
    set_num(stair_5_array, 6, stair_5_xyz);
    initial_stair_5_location = FVector(pillar_1_array[0].row[pillar_1_xyz.X - 1].column[0]->GetActorLocation().X - plane_size, pillar_1_array[1].row[pillar_1_xyz.X - 1].column[0]->GetActorLocation().Y, stair_2_array[0].row[0].column[0]->GetActorLocation().Z);
    spawn_stair(stair_5_array, initial_stair_5_location, plane_size, stair_5_xyz, stair_scale, stair_5_direction);
    floor_7_xyz = FIntVector(stair_5_xyz.X, room_0_xyz.Y - stair_5_xyz.Y - floor_3_xyz.Y, 1); // Starting to create Floor 7.
    set_num(floor_7_array, 6, floor_7_xyz);
    initial_floor_7_location = FVector(stair_5_array[0].row[stair_5_xyz.X - 1].column[stair_5_xyz.Y - 1]->GetActorLocation().X, stair_5_array[0].row[stair_5_xyz.X - 1].column[stair_5_xyz.Y - 1]->GetActorLocation().Y - plane_size, stair_5_array[0].row[stair_5_xyz.X - 1].column[stair_5_xyz.Y - 1]->GetActorLocation().Z);
    spawn_plane(floor_7_array, initial_floor_7_location, floor_7_xy_scale, floor_7_xz_scale, floor_7_yz_scale, floor_7_xyz, plane_size, false, floor_7_direction);
    floor_8_xyz = FIntVector((floor_7_array[0].row[floor_7_xyz.X - 1].column[floor_7_xyz.Y - 1]->GetActorLocation().X / 100) - floor_5_xyz.X - floor_7_xyz.X  + 1, (pillar_3_array[0].row[0].column[0]->GetActorLocation().Y / 100), 1); // Starting to create Floor 8.
    set_num(floor_8_array, 6, floor_8_xyz);
    initial_floor_8_location = FVector(floor_7_array[0].row[0].column[floor_7_xyz.Y - 1]->GetActorLocation().X - plane_size, floor_7_array[0].row[0].column[floor_7_xyz.Y - 1]->GetActorLocation().Y, floor_7_array[0].row[0].column[floor_7_xyz.Y - 1]->GetActorLocation().Z);
    spawn_plane(floor_8_array, initial_floor_8_location, floor_8_xy_scale, floor_8_xz_scale, floor_8_yz_scale, floor_8_xyz, plane_size, false, floor_8_direction);
    pillar_4_xyz = FIntVector(3, 3, room_0_xyz.Z); // Starting to create Pillar 4.
    set_num(pillar_4_array, 6, pillar_4_xyz);
    initial_pillar_4_location = FVector(floor_8_array[0].row[0].column[floor_8_xyz.Y - 1]->GetActorLocation().X, floor_8_array[0].row[0].column[floor_8_xyz.Y - 1]->GetActorLocation().Y + plane_size, 0.0f);
    spawn_plane(pillar_4_array, initial_pillar_4_location, pillar_4_xy_scale, pillar_4_xz_scale, pillar_4_yz_scale, pillar_4_xyz, plane_size, false, pillar_4_direction);
    pillar_5_xyz = FIntVector(3, 3, room_0_xyz.Z); // Starting to create Pillar 5.
    set_num(pillar_5_array, 6, pillar_5_xyz);
    initial_pillar_5_location = FVector(floor_3_array[0].row[floor_3_xyz.X - 1].column[floor_3_xyz.Y - 1]->GetActorLocation().X - plane_size, floor_3_array[0].row[floor_3_xyz.X - 1].column[floor_3_xyz.Y - 1]->GetActorLocation().Y - plane_size, 0.0f);
    spawn_plane(pillar_5_array, initial_pillar_5_location, pillar_5_xy_scale, pillar_5_xz_scale, pillar_5_yz_scale, pillar_5_xyz, plane_size, false, pillar_5_direction);
    pillar_6_xyz = FIntVector(3, 3, room_0_xyz.Z); // Starting to create Pillar 6.
    set_num(pillar_6_array, 6, pillar_6_xyz);
    initial_pillar_6_location = FVector(stair_3_array[0].row[0].column[stair_3_xyz.Y - 1]->GetActorLocation().X, stair_3_array[0].row[0].column[stair_3_xyz.Y - 1]->GetActorLocation().Y + plane_size, 0.0f);
    spawn_plane(pillar_6_array, initial_pillar_6_location, pillar_6_xy_scale, pillar_6_xz_scale, pillar_6_yz_scale, pillar_6_xyz, plane_size, false, pillar_6_direction);
    pillar_7_xyz = FIntVector(3, 3, room_0_xyz.Z); // Starting to create Pillar 7.
    set_num(pillar_7_array, 6, pillar_7_xyz);
    initial_pillar_7_location = FVector(stair_4_array[0].row[stair_4_xyz.X - 1].column[stair_4_xyz.Y - 1]->GetActorLocation().X, stair_4_array[0].row[stair_4_xyz.X - 1].column[stair_4_xyz.Y - 1]->GetActorLocation().Y + plane_size, 0.0f);
    spawn_plane(pillar_7_array, initial_pillar_7_location, pillar_7_xy_scale, pillar_7_xz_scale, pillar_7_yz_scale, pillar_7_xyz, plane_size, false, pillar_7_direction);
    default_player_start_PIE = UGameplayStatics::GetActorOfClass(world, APlayerStartPIE::StaticClass());
    if(default_player_start_PIE) default_player_start_PIE->Destroy();
    //APlayerController* NewPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    //

    //
    //NewPC->Possess(characterNew);


    //AController* CortollerRef = GetController();


    //APawn* lol_2 = GetWorld()->SpawnActor<APawn>(paper_player_class, FVector( 0.0f),FRotator(0.0f));
    //AddPlayerStart(PlayerStart);
    
    //UGameplayStatics::GetPlayerController();
//Possess
    //FActorSpawnParameters paper_plane_spawn_parameters;
	//paper_plane_spawn_parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}
void Agame_mode_base_level_arena::Tick(float delta_time) {
    Super::Tick(delta_time);
    //player_controller = UGameplayStatics::GetPlayerController(world, 0);
    //pawn = player_controller->GetPawn();
    //paper_player = Cast<Apaper_player>(pawn);
    //if (!paper_player && !dead) {
    //    player_controller->ClientSetHUD_Implementation(_hud_class);
    //    dead = true;
    //}
}
void Agame_mode_base_level_arena::implement_hud_ending() {
    player_controller = UGameplayStatics::GetPlayerController(world, 0);
    pawn = player_controller->GetPawn();
    player_controller->ClientSetHUD_Implementation(hud_ending_class);
}
void Agame_mode_base_level_arena::EndPlay(EEndPlayReason::Type reason) {
    Super::EndPlay(reason);

}
AActor* Agame_mode_base_level_arena::ChoosePlayerStart_Implementation(AController* player) {
    //return Super::ChoosePlayerStart_Implementation(Player);
    player_start = world->SpawnActor<Aplayer_start>(FVector(1000.0f), FRotator(0.0f));
    return player_start;
}
void Agame_mode_base_level_arena::StartPlay() {
    Super::StartPlay();
    //APawn* lol_2 = Cast<APawn>(UGameplayStatics::GetPlayerPawn(world, 0));
    //UGameplayStatics::GetPlayerPawn(world, 0)->SetActorLocation(FVector(1000.0f));
}
void Agame_mode_base_level_arena::set_num(TArray<Fplane_struct>& box_array, int32 face_count, FIntVector xyz) {
    box_array.SetNum(face_count);
    for (int32 face_number = 0; face_number < face_count; face_number++) {
        if (face_number < 2) {
            box_array[face_number].row.SetNum(xyz.X);
            for (int32 i = 0; i < xyz.X; i++) box_array[face_number].row[i].column.SetNum(xyz.Y);
        }
        else if (face_number < 4) {
            box_array[face_number].row.SetNum(xyz.X);
            for (int32 i = 0; i < xyz.X; i++) box_array[face_number].row[i].column.SetNum(xyz.Z);
        }
        else if (face_number < 6) {
            box_array[face_number].row.SetNum(xyz.Y);
            for (int32 i = 0; i < xyz.Y; i++) box_array[face_number].row[i].column.SetNum(xyz.Z);
        }
    }
}
void Agame_mode_base_level_arena::spawn_plane(TArray<Fplane_struct>& box_array, FVector initial_location, FVector scale_xy, FVector scale_xz, FVector scale_yz, FIntVector xyz, float distance, bool inside, TEnumAsByte<direction> plane_direction) {
    FVector location, temp_location;
    if (plane_direction == front) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? floor_rotation : ceiling_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (xyz.Z * distance * scale_yz.Y));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? ceiling_rotation : floor_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + (distance * scale_xz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_xz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_left_rotation : wall_right_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_xz);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2) + (xyz.Y * distance), initial_location.Z + (distance * scale_xz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_xz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_right_rotation : wall_left_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_xz);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X - (distance / 2), initial_location.Y, initial_location.Z + (distance * scale_yz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_yz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_back_rotation : wall_front_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_yz);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X - (distance / 2) + (xyz.X * distance), initial_location.Y, initial_location.Z + (distance * scale_yz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_yz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_front_rotation : wall_back_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_yz);
                        }
                    }
                }
            }
        }
    }
    else if (plane_direction == right) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? floor_rotation : ceiling_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (xyz.Z * distance * scale_yz.Y));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? ceiling_rotation : floor_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + (distance * scale_xz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_xz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_left_rotation : wall_right_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_xz);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2) + (xyz.Y * distance), initial_location.Z + (distance * scale_xz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_xz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_right_rotation : wall_left_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_xz);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + (distance * scale_yz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_yz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_front_rotation : wall_back_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_yz);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2) - (xyz.X * distance), initial_location.Y, initial_location.Z + (distance * scale_yz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_yz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_back_rotation : wall_front_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_yz);
                        }
                    }
                }
            }
        }
    }
    else if (plane_direction == back) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? floor_rotation : ceiling_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (xyz.Z * distance * scale_yz.Y));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? ceiling_rotation : floor_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y + (distance / 2), initial_location.Z + (distance * scale_xz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_xz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_right_rotation : wall_left_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_xz);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y + (distance / 2) - (xyz.Y * distance), initial_location.Z + (distance * scale_xz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_xz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_left_rotation : wall_right_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_xz);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + (distance * scale_yz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_yz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_front_rotation : wall_back_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_yz);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2) - (xyz.X * distance), initial_location.Y, initial_location.Z + (distance * scale_yz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_yz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_back_rotation : wall_front_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_yz);
                        }
                    }
                }
            }
        }
    }
    else if (plane_direction == left) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? floor_rotation : ceiling_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (xyz.Z * distance * scale_yz.Y));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? ceiling_rotation : floor_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y + (distance / 2), initial_location.Z + (distance * scale_xz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_xz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_right_rotation : wall_left_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_xz);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y + (distance / 2) - (xyz.Y * distance), initial_location.Z + (distance * scale_xz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_xz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_left_rotation : wall_right_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_xz);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X - (distance / 2), initial_location.Y, initial_location.Z + (distance * scale_yz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_yz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_back_rotation : wall_front_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_yz);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X - (distance / 2) + (xyz.X * distance), initial_location.Y, initial_location.Z + (distance * scale_yz.Y / 2));
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Z += (distance * scale_yz.Y)) {
                        box_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, inside ? wall_front_rotation : wall_back_rotation);
                        if (box_array[face_number].row[row_number].column[column_number]) {
                            box_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            box_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale_yz);
                        }
                    }
                }
            }
        }
    }
}
void Agame_mode_base_level_arena::spawn_stair(TArray<Fplane_struct>& stair_array, FVector initial_location, float distance, FIntVector xyz, FVector scale, TEnumAsByte<direction> stair_direction) {
    FVector location, temp_location;
    if (stair_direction == front) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                    location.Z += (distance / 4);
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                    location.Z += (distance / 4);
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2) + (xyz.Y * distance), initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X - (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.X += distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.X += distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
    else if (stair_direction == right) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                        location.Z += (distance / 4);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                        location.Z += (distance / 4);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + ((distance / 4) / 2));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Y += distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2) + distance, initial_location.Z + ((distance / 4) / 2));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Y += distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2) - (xyz.X * distance), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
    else if (stair_direction == back) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                    location.Z += (distance / 4);
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                    }
                    location.Z += (distance / 4);
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2), initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - (distance / 2) + (xyz.Y * distance), initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X - (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.X -= distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.X -= distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
    else if (stair_direction == left) {
        for (int32 face_number = 0; face_number < 6; face_number++) {
            if (face_number == 0) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                        location.Z += (distance / 4);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                        location.Z += (distance / 4);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y + (distance / 2), initial_location.Z + ((distance / 4) / 2));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Y -= distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y + (distance / 2) - distance, initial_location.Z + ((distance / 4) / 2));
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Y -= distance, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }

                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X + (distance / 2), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + (distance / 2) - (xyz.X * distance), initial_location.Y, initial_location.Z + ((distance / 4) / 2));
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += (distance / 4)) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset);
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
}