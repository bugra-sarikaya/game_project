// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "game_mode_base_level_arena.h"
#include "hud_main_menu.h"
#include "player_state.h"
#include "game_state_base.h"
#include "enemy.h"

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
    check(static_mesh_plane_class != nullptr);
    paper_player_class = LoadClass<Apaper_player>(world, TEXT("/Script/game_project.paper_player"));
    check(paper_player_class != nullptr);
    player_start_class = LoadClass<Aplayer_start>(world, TEXT("/Script/game_project.player_start"));
    check(player_start_class != nullptr);
    material_asset_type_14_part_0_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_bottom_left_v1.plane_material_instance_type_14_part_0_bottom_left_v1"));
    material_asset_type_14_part_0_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_bottom_middle_v1.plane_material_instance_type_14_part_0_bottom_middle_v1"));
    material_asset_type_14_part_0_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_bottom_right_v1.plane_material_instance_type_14_part_0_bottom_right_v1"));
    material_asset_type_14_part_0_middle_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_middle_left_v1.plane_material_instance_type_14_part_0_middle_left_v1"));
    material_asset_type_14_part_0_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_middle_middle_v1.plane_material_instance_type_14_part_0_middle_middle_v1"));
    material_asset_type_14_part_0_middle_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_middle_right_v1.plane_material_instance_type_14_part_0_middle_right_v1"));
    material_asset_type_14_part_0_top_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_top_left_v1.plane_material_instance_type_14_part_0_top_left_v1"));
    material_asset_type_14_part_0_top_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_top_middle_v1.plane_material_instance_type_14_part_0_top_middle_v1"));
    material_asset_type_14_part_0_top_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_0_top_right_v1.plane_material_instance_type_14_part_0_top_right_v1"));
    material_asset_type_14_part_1_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_bottom_left_v1.plane_material_instance_type_14_part_1_bottom_left_v1"));
    material_asset_type_14_part_1_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_bottom_middle_v1.plane_material_instance_type_14_part_1_bottom_middle_v1"));
    material_asset_type_14_part_1_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_bottom_right_v1.plane_material_instance_type_14_part_1_bottom_right_v1"));
    material_asset_type_14_part_1_middle_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_middle_left_v1.plane_material_instance_type_14_part_1_middle_left_v1"));
    material_asset_type_14_part_1_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_middle_middle_v1.plane_material_instance_type_14_part_1_middle_middle_v1"));
    material_asset_type_14_part_1_middle_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_middle_right_v1.plane_material_instance_type_14_part_1_middle_right_v1"));
    material_asset_type_14_part_1_top_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_top_left_v1.plane_material_instance_type_14_part_1_top_left_v1"));
    material_asset_type_14_part_1_top_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_top_middle_v1.plane_material_instance_type_14_part_1_top_middle_v1"));
    material_asset_type_14_part_1_top_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_1_top_right_v1.plane_material_instance_type_14_part_1_top_right_v1"));    
    material_asset_type_14_part_2_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_bottom_left_v1.plane_material_instance_type_14_part_2_bottom_left_v1"));
    material_asset_type_14_part_2_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_bottom_middle_v1.plane_material_instance_type_14_part_2_bottom_middle_v1"));
    material_asset_type_14_part_2_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_bottom_right_v1.plane_material_instance_type_14_part_2_bottom_right_v1"));
    material_asset_type_14_part_2_middle_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_middle_left_v1.plane_material_instance_type_14_part_2_middle_left_v1"));
    material_asset_type_14_part_2_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_middle_middle_v1.plane_material_instance_type_14_part_2_middle_middle_v1"));
    material_asset_type_14_part_2_middle_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_middle_right_v1.plane_material_instance_type_14_part_2_middle_right_v1"));
    material_asset_type_14_part_2_top_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_top_left_v1.plane_material_instance_type_14_part_2_top_left_v1"));
    material_asset_type_14_part_2_top_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_top_middle_v1.plane_material_instance_type_14_part_2_top_middle_v1"));
    material_asset_type_14_part_2_top_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_2_top_right_v1.plane_material_instance_type_14_part_2_top_right_v1"));
    material_asset_type_14_part_3_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_3_bottom_left_v1.plane_material_instance_type_14_part_3_bottom_left_v1"));
    material_asset_type_14_part_3_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_3_bottom_middle_v1.plane_material_instance_type_14_part_3_bottom_middle_v1"));
    material_asset_type_14_part_3_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_3_bottom_right_v1.plane_material_instance_type_14_part_3_bottom_right_v1"));
    material_asset_type_14_part_4_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_4_bottom_middle_v1.plane_material_instance_type_14_part_4_bottom_middle_v1"));
    material_asset_type_14_part_4_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_4_middle_middle_v1.plane_material_instance_type_14_part_4_middle_middle_v1"));
    material_asset_type_14_part_4_top_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_4_top_middle_v1.plane_material_instance_type_14_part_4_top_middle_v1"));
    material_asset_type_14_part_5_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_5_bottom_left_v1.plane_material_instance_type_14_part_5_bottom_left_v1"));
    material_asset_type_14_part_5_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_5_bottom_middle_v1.plane_material_instance_type_14_part_5_bottom_middle_v1"));
    material_asset_type_14_part_5_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_5_bottom_right_v1.plane_material_instance_type_14_part_5_bottom_right_v1"));
    material_asset_type_14_part_6_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_6_middle_middle_v1.plane_material_instance_type_14_part_6_middle_middle_v1"));
    material_asset_type_14_part_7_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_bottom_left_v1.plane_material_instance_type_14_part_7_bottom_left_v1"));
    material_asset_type_14_part_7_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_bottom_middle_v1.plane_material_instance_type_14_part_7_bottom_middle_v1"));
    material_asset_type_14_part_7_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_bottom_right_v1.plane_material_instance_type_14_part_7_bottom_right_v1"));
    material_asset_type_14_part_7_middle_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_middle_left_v1.plane_material_instance_type_14_part_7_middle_left_v1"));
    material_asset_type_14_part_7_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_middle_middle_v1.plane_material_instance_type_14_part_7_middle_middle_v1"));
    material_asset_type_14_part_7_middle_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_middle_right_v1.plane_material_instance_type_14_part_7_middle_right_v1"));
    material_asset_type_14_part_7_top_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_top_left_v1.plane_material_instance_type_14_part_7_top_left_v1"));
    material_asset_type_14_part_7_top_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_top_middle_v1.plane_material_instance_type_14_part_7_top_middle_v1"));
    material_asset_type_14_part_7_top_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_7_top_right_v1.plane_material_instance_type_14_part_7_top_right_v1"));
    material_asset_type_14_part_8_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_bottom_left_v1.plane_material_instance_type_14_part_8_bottom_left_v1"));
    material_asset_type_14_part_8_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_bottom_middle_v1.plane_material_instance_type_14_part_8_bottom_middle_v1"));
    material_asset_type_14_part_8_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_bottom_right_v1.plane_material_instance_type_14_part_8_bottom_right_v1"));
    material_asset_type_14_part_8_middle_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_middle_left_v1.plane_material_instance_type_14_part_8_middle_left_v1"));
    material_asset_type_14_part_8_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_middle_middle_v1.plane_material_instance_type_14_part_8_middle_middle_v1"));
    material_asset_type_14_part_8_middle_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_middle_right_v1.plane_material_instance_type_14_part_8_middle_right_v1"));
    material_asset_type_14_part_8_top_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_top_left_v1.plane_material_instance_type_14_part_8_top_left_v1"));
    material_asset_type_14_part_8_top_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_top_middle_v1.plane_material_instance_type_14_part_8_top_middle_v1"));
    material_asset_type_14_part_8_top_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_8_top_right_v1.plane_material_instance_type_14_part_8_top_right_v1"));
    material_asset_type_14_part_9_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_9_bottom_left_v1.plane_material_instance_type_14_part_9_bottom_left_v1"));
    material_asset_type_14_part_9_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_9_bottom_middle_v1.plane_material_instance_type_14_part_9_bottom_middle_v1"));
    material_asset_type_14_part_9_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_9_bottom_right_v1.plane_material_instance_type_14_part_9_bottom_right_v1"));
    material_asset_type_14_part_10_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_bottom_left_v1.plane_material_instance_type_14_part_10_bottom_left_v1"));
    material_asset_type_14_part_10_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_bottom_middle_v1.plane_material_instance_type_14_part_10_bottom_middle_v1"));
    material_asset_type_14_part_10_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_bottom_right_v1.plane_material_instance_type_14_part_10_bottom_right_v1"));
    material_asset_type_14_part_10_middle_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_middle_left_v1.plane_material_instance_type_14_part_10_middle_left_v1"));
    material_asset_type_14_part_10_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_middle_middle_v1.plane_material_instance_type_14_part_10_middle_middle_v1"));
    material_asset_type_14_part_10_middle_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_middle_right_v1.plane_material_instance_type_14_part_10_middle_right_v1"));
    material_asset_type_14_part_10_top_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_top_left_v1.plane_material_instance_type_14_part_10_top_left_v1"));
    material_asset_type_14_part_10_top_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_top_middle_v1.plane_material_instance_type_14_part_10_top_middle_v1"));
    material_asset_type_14_part_10_top_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_10_top_right_v1.plane_material_instance_type_14_part_10_top_right_v1"));
    material_asset_type_14_part_11_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_11_bottom_middle_v1.plane_material_instance_type_14_part_11_bottom_middle_v1"));
    material_asset_type_14_part_11_middle_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_11_middle_middle_v1.plane_material_instance_type_14_part_11_middle_middle_v1"));
    material_asset_type_14_part_11_top_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_11_top_middle_v1.plane_material_instance_type_14_part_11_top_middle_v1"));
    material_asset_type_14_part_12_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_12_bottom_left_v1.plane_material_instance_type_14_part_12_bottom_left_v1"));
    material_asset_type_14_part_12_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_12_bottom_middle_v1.plane_material_instance_type_14_part_12_bottom_middle_v1"));
    material_asset_type_14_part_12_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_12_bottom_right_v1.plane_material_instance_type_14_part_12_bottom_right_v1"));
    material_asset_type_14_part_13_bottom_left = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_13_bottom_left_v1.plane_material_instance_type_14_part_13_bottom_left_v1"));
    material_asset_type_14_part_13_bottom_middle = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_13_bottom_middle_v1.plane_material_instance_type_14_part_13_bottom_middle_v1"));
    material_asset_type_14_part_13_bottom_right = LoadObject<UMaterialInterface>(world, TEXT("/Game/materials/plane_material_instance_type_14_part_13_bottom_right_v1.plane_material_instance_type_14_part_13_bottom_right_v1"));
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_0, material_asset_type_14_part_0_bottom_left, material_asset_type_14_part_0_bottom_middle, material_asset_type_14_part_0_bottom_right, material_asset_type_14_part_0_middle_left, material_asset_type_14_part_0_middle_middle, material_asset_type_14_part_0_middle_right, material_asset_type_14_part_0_top_left, material_asset_type_14_part_0_top_middle, material_asset_type_14_part_0_top_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_1, material_asset_type_14_part_1_bottom_left, material_asset_type_14_part_1_bottom_middle, material_asset_type_14_part_1_bottom_right, material_asset_type_14_part_1_middle_left, material_asset_type_14_part_1_middle_middle, material_asset_type_14_part_1_middle_right, material_asset_type_14_part_1_top_left, material_asset_type_14_part_1_top_middle, material_asset_type_14_part_1_top_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_2, material_asset_type_14_part_2_bottom_left, material_asset_type_14_part_2_bottom_middle, material_asset_type_14_part_2_bottom_right, material_asset_type_14_part_2_middle_left, material_asset_type_14_part_2_middle_middle, material_asset_type_14_part_2_middle_right, material_asset_type_14_part_2_top_left, material_asset_type_14_part_2_top_middle, material_asset_type_14_part_2_top_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_3, material_asset_type_14_part_3_bottom_left, material_asset_type_14_part_3_bottom_middle, material_asset_type_14_part_3_bottom_right, material_asset_type_14_part_3_bottom_left, material_asset_type_14_part_3_bottom_middle, material_asset_type_14_part_3_bottom_right, material_asset_type_14_part_3_bottom_left, material_asset_type_14_part_3_bottom_middle, material_asset_type_14_part_3_bottom_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_4, material_asset_type_14_part_4_bottom_middle, material_asset_type_14_part_4_bottom_middle, material_asset_type_14_part_4_bottom_middle, material_asset_type_14_part_4_middle_middle, material_asset_type_14_part_4_middle_middle, material_asset_type_14_part_4_middle_middle, material_asset_type_14_part_4_top_middle, material_asset_type_14_part_4_top_middle, material_asset_type_14_part_4_top_middle);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_5, material_asset_type_14_part_5_bottom_left, material_asset_type_14_part_5_bottom_middle, material_asset_type_14_part_5_bottom_right, material_asset_type_14_part_5_bottom_left, material_asset_type_14_part_5_bottom_middle, material_asset_type_14_part_5_bottom_right, material_asset_type_14_part_5_bottom_left, material_asset_type_14_part_5_bottom_middle, material_asset_type_14_part_5_bottom_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_6, material_asset_type_14_part_6_middle_middle, material_asset_type_14_part_6_middle_middle, material_asset_type_14_part_6_middle_middle, material_asset_type_14_part_6_middle_middle, material_asset_type_14_part_6_middle_middle, material_asset_type_14_part_6_middle_middle, material_asset_type_14_part_6_middle_middle, material_asset_type_14_part_6_middle_middle, material_asset_type_14_part_6_middle_middle);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_7, material_asset_type_14_part_7_bottom_left, material_asset_type_14_part_7_bottom_middle, material_asset_type_14_part_7_bottom_right, material_asset_type_14_part_7_middle_left, material_asset_type_14_part_7_middle_middle, material_asset_type_14_part_7_middle_right, material_asset_type_14_part_7_top_left, material_asset_type_14_part_7_top_middle, material_asset_type_14_part_7_top_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_8, material_asset_type_14_part_8_bottom_left, material_asset_type_14_part_8_bottom_middle, material_asset_type_14_part_8_bottom_right, material_asset_type_14_part_8_middle_left, material_asset_type_14_part_8_middle_middle, material_asset_type_14_part_8_middle_right, material_asset_type_14_part_8_top_left, material_asset_type_14_part_8_top_middle, material_asset_type_14_part_8_top_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_9, material_asset_type_14_part_9_bottom_left, material_asset_type_14_part_9_bottom_middle, material_asset_type_14_part_9_bottom_right, material_asset_type_14_part_9_bottom_left, material_asset_type_14_part_9_bottom_middle, material_asset_type_14_part_9_bottom_right, material_asset_type_14_part_9_bottom_left, material_asset_type_14_part_9_bottom_middle, material_asset_type_14_part_9_bottom_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_10, material_asset_type_14_part_10_bottom_left, material_asset_type_14_part_10_bottom_middle, material_asset_type_14_part_10_bottom_right, material_asset_type_14_part_10_middle_left, material_asset_type_14_part_10_middle_middle, material_asset_type_14_part_10_middle_right, material_asset_type_14_part_10_top_left, material_asset_type_14_part_10_top_middle, material_asset_type_14_part_10_top_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_11, material_asset_type_14_part_11_bottom_middle, material_asset_type_14_part_11_bottom_middle, material_asset_type_14_part_11_bottom_middle, material_asset_type_14_part_11_middle_middle, material_asset_type_14_part_11_middle_middle, material_asset_type_14_part_11_middle_middle, material_asset_type_14_part_11_top_middle, material_asset_type_14_part_11_top_middle, material_asset_type_14_part_11_top_middle);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_12, material_asset_type_14_part_12_bottom_left, material_asset_type_14_part_12_bottom_middle, material_asset_type_14_part_12_bottom_right, material_asset_type_14_part_12_bottom_left, material_asset_type_14_part_12_bottom_middle, material_asset_type_14_part_12_bottom_right, material_asset_type_14_part_12_bottom_left, material_asset_type_14_part_12_bottom_middle, material_asset_type_14_part_12_bottom_right);
    assign_materials_to_packs(material_asset_struct_pack_type_14_part_13, material_asset_type_14_part_13_bottom_left, material_asset_type_14_part_13_bottom_middle, material_asset_type_14_part_13_bottom_right, material_asset_type_14_part_13_bottom_left, material_asset_type_14_part_13_bottom_middle, material_asset_type_14_part_13_bottom_right, material_asset_type_14_part_13_bottom_left, material_asset_type_14_part_13_bottom_middle, material_asset_type_14_part_13_bottom_right);
    assign_material_packs_to_faces(material_asset_struct_room_0, material_asset_struct_pack_type_14_part_10, material_asset_struct_pack_type_14_part_10, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1);
    assign_material_packs_to_faces(material_asset_struct_stair_0, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_12);
    assign_material_packs_to_faces(material_asset_struct_stair_1, material_asset_struct_pack_type_14_part_13, material_asset_struct_pack_type_14_part_13, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_6);
    assign_material_packs_to_faces(material_asset_struct_stair_2, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_12);
    assign_material_packs_to_faces(material_asset_struct_stair_3, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_12);
    assign_material_packs_to_faces(material_asset_struct_stair_4, material_asset_struct_pack_type_14_part_13, material_asset_struct_pack_type_14_part_13, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_6);
    assign_material_packs_to_faces(material_asset_struct_stair_5, material_asset_struct_pack_type_14_part_13, material_asset_struct_pack_type_14_part_13, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_6);
    assign_material_packs_to_faces(material_asset_struct_stair_6, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_12);
    assign_material_packs_to_faces(material_asset_struct_stair_7, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_11, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_6, material_asset_struct_pack_type_14_part_12, material_asset_struct_pack_type_14_part_12);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_0, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_1, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_3, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_4, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_5, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_6, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_7, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_8, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_9, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_10, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_11, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_junction_12, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_2, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_0, material_asset_struct_pack_type_14_part_7, material_asset_struct_pack_type_14_part_7, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_1, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9);
    assign_material_packs_to_faces(material_asset_struct_floor_2, material_asset_struct_pack_type_14_part_7, material_asset_struct_pack_type_14_part_7, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_3, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9);
    assign_material_packs_to_faces(material_asset_struct_floor_4, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9);
    assign_material_packs_to_faces(material_asset_struct_floor_5, material_asset_struct_pack_type_14_part_7, material_asset_struct_pack_type_14_part_7, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_6, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9);
    assign_material_packs_to_faces(material_asset_struct_floor_7, material_asset_struct_pack_type_14_part_7, material_asset_struct_pack_type_14_part_7, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3);
    assign_material_packs_to_faces(material_asset_struct_floor_8, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9);
    assign_material_packs_to_faces(material_asset_struct_floor_9, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_8, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_3, material_asset_struct_pack_type_14_part_9, material_asset_struct_pack_type_14_part_9);
    assign_material_packs_to_faces(material_asset_struct_pillar_0, material_asset_struct_pack_type_14_part_0, material_asset_struct_pack_type_14_part_0, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1);
    assign_material_packs_to_faces(material_asset_struct_pillar_1, material_asset_struct_pack_type_14_part_0, material_asset_struct_pack_type_14_part_0, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1);
    assign_material_packs_to_faces(material_asset_struct_pillar_2, material_asset_struct_pack_type_14_part_0, material_asset_struct_pack_type_14_part_0, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1);
    assign_material_packs_to_faces(material_asset_struct_pillar_3, material_asset_struct_pack_type_14_part_0, material_asset_struct_pack_type_14_part_0, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1, material_asset_struct_pack_type_14_part_1);
}
void Agame_mode_base_level_arena::BeginPlay() {
    Super::BeginPlay();
    FTransform local_to_world;
    temp_static_mesh_plane = world->SpawnActor<Astatic_mesh_plane>();
    plane_size = ((temp_static_mesh_plane->GetStaticMeshComponent()->CalcBounds(local_to_world).BoxExtent).X) * 2; // plane_size = 100
    temp_static_mesh_plane->Destroy();
    set_num(room_0_array, 6, room_0_xyz); // Starting to create Room 0.
    spawn_box(room_0_array, initial_room_0_location, room_xy_scale, room_xz_scale, room_yz_scale, room_0_xyz, plane_size, true, room_0_direction);
    design_prism(room_0_array, 6, room_0_xyz, material_asset_struct_room_0, true, room_0_direction);
    set_num(stair_0_array, 6, stair_0_xyz); // Starting to create Stair 0.
    initial_stair_0_location = FVector(room_0_array[0].row[floor_junction_xyz.X].column[0]->GetActorLocation().X, 0.0f, 0.0f);
    spawn_stair(stair_0_array, initial_stair_0_location, plane_size, stair_0_xyz, stair_scale, stair_0_direction);
    design_stair(stair_0_array, 6, stair_0_xyz, material_asset_struct_stair_0, stair_0_direction);
    set_num(floor_junction_0_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 0.
    initial_floor_junction_0_location = FVector(stair_0_array[0].row[stair_0_xyz.X - 1].column[0]->GetActorLocation().X + plane_size, stair_0_array[0].row[stair_0_xyz.X - 1].column[0]->GetActorLocation().Y, stair_0_array[0].row[stair_0_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_junction_0_array, initial_floor_junction_0_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_0_direction);
    design_prism(floor_junction_0_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_0, false, floor_junction_0_direction);
    spawning_locations.Add(FVector(floor_junction_0_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_0_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_0_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    floor_0_xyz = FIntVector(room_0_xyz.X - floor_junction_xyz.X - stair_0_xyz.X - floor_junction_xyz.X * 2, floor_junction_xyz.Y,  1); // Starting to create Floor 0.
    set_num(floor_0_array, 6, floor_0_xyz);
    initial_floor_0_location = FVector(floor_junction_0_array[0].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().X + plane_size, floor_junction_0_array[0].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().Y, floor_junction_0_array[0].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_0_array, initial_floor_0_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_0_xyz, plane_size, false, floor_0_direction);
    design_prism(floor_0_array, 6, floor_0_xyz, material_asset_struct_floor_0, false, floor_0_direction);
    set_num(floor_junction_1_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 1.
    initial_floor_junction_1_location = FVector(floor_0_array[0].row[floor_0_xyz.X - 1].column[0]->GetActorLocation().X + plane_size, floor_0_array[0].row[floor_0_xyz.X - 1].column[0]->GetActorLocation().Y, floor_0_array[0].row[floor_0_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_junction_1_array, initial_floor_junction_1_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_1_direction);
    design_prism(floor_junction_1_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_1, false, floor_junction_1_direction);
    spawning_locations.Add(FVector(floor_junction_1_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_1_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_1_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    floor_1_xyz = FIntVector(floor_junction_xyz.X, room_0_xyz.Y - floor_junction_xyz.Y * 3 - stair_1_xyz.Y, 1); // Starting to create Floor 1.
    set_num(floor_1_array, 6, floor_1_xyz);
    initial_floor_1_location = FVector(floor_junction_1_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X, floor_junction_1_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y + plane_size, floor_junction_1_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_1_array, initial_floor_1_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_1_xyz, plane_size, false, floor_1_direction);
    design_prism(floor_1_array, 6, floor_1_xyz, material_asset_struct_floor_1, false, floor_1_direction);
    set_num(floor_junction_2_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 2.
    initial_floor_junction_2_location = FVector(floor_1_array[0].row[0].column[floor_1_xyz.Y - 1]->GetActorLocation().X, floor_1_array[0].row[0].column[floor_1_xyz.Y - 1]->GetActorLocation().Y + plane_size, floor_1_array[0].row[0].column[floor_1_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_junction_2_array, initial_floor_junction_2_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_2_direction);
    design_prism(floor_junction_2_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_2, false, floor_junction_2_direction);
    spawning_locations.Add(FVector(floor_junction_2_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_2_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_2_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    set_num(stair_1_array, 6, stair_1_xyz); // Starting to create Stair 1.
    initial_stair_1_location = FVector(floor_junction_2_array[1].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().X, floor_junction_2_array[1].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y  + plane_size, floor_junction_2_array[1].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_stair(stair_1_array, initial_stair_1_location, plane_size, stair_1_xyz, stair_scale, stair_1_direction);
    design_stair(stair_1_array, 6, stair_1_xyz, material_asset_struct_stair_1, stair_1_direction);
    set_num(floor_junction_3_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 3.
    initial_floor_junction_3_location = FVector(stair_1_array[0].row[0].column[stair_1_xyz.Y - 1]->GetActorLocation().X, stair_1_array[0].row[0].column[stair_1_xyz.Y - 1]->GetActorLocation().Y + plane_size, stair_1_array[0].row[0].column[stair_1_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_junction_3_array, initial_floor_junction_3_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_2_direction);
    design_prism(floor_junction_3_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_3, false, floor_junction_3_direction);
    spawning_locations.Add(FVector(floor_junction_3_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_3_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_3_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    floor_2_xyz = FIntVector(room_0_xyz.X - floor_junction_xyz.X * 3 - stair_2_xyz.X,  floor_junction_xyz.Y, 1); // Starting to create Floor 2.
    set_num(floor_2_array, 6, floor_2_xyz);
    initial_floor_2_location = FVector(floor_junction_3_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X - plane_size, floor_junction_3_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y, floor_junction_3_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_2_array, initial_floor_2_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_2_xyz, plane_size, false, floor_2_direction);
    design_prism(floor_2_array, 6, floor_2_xyz, material_asset_struct_floor_2, false, floor_2_direction);
    set_num(floor_junction_4_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 4.
    initial_floor_junction_4_location = FVector(floor_2_array[0].row[floor_2_xyz.X - 1].column[0]->GetActorLocation().X - plane_size, floor_2_array[0].row[floor_2_xyz.X - 1].column[0]->GetActorLocation().Y, floor_2_array[0].row[floor_2_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_junction_4_array, initial_floor_junction_4_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_4_direction);
    design_prism(floor_junction_4_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_4, false, floor_junction_4_direction);
    spawning_locations.Add(FVector(floor_junction_4_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_4_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_4_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    set_num(stair_2_array, 6, stair_2_xyz); // Starting to create Stair 2.
    initial_stair_2_location = FVector(floor_junction_4_array[1].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().X - plane_size, floor_junction_4_array[1].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().Y, floor_junction_4_array[1].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_stair(stair_2_array, initial_stair_2_location, plane_size, stair_2_xyz, stair_scale, stair_2_direction);
    design_stair(stair_2_array, 6, stair_2_xyz, material_asset_struct_stair_2, stair_2_direction);
    set_num(floor_junction_5_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 5.
    initial_floor_junction_5_location = FVector(stair_2_array[0].row[stair_2_xyz.X - 1].column[0]->GetActorLocation().X - plane_size, stair_2_array[0].row[stair_2_xyz.X - 1].column[0]->GetActorLocation().Y, stair_2_array[0].row[stair_2_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_junction_5_array, initial_floor_junction_5_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_5_direction);
    design_prism(floor_junction_5_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_5, false, floor_junction_5_direction);
    spawning_locations.Add(FVector(floor_junction_5_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_5_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_5_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    floor_3_xyz = FIntVector(floor_junction_xyz.X, stair_1_xyz.Y, 1); // Starting to create Floor 3.
    set_num(floor_3_array, 6, floor_3_xyz);
    initial_floor_3_location = FVector(floor_junction_5_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X, floor_junction_5_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_junction_5_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_3_array, initial_floor_3_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_3_xyz, plane_size, false, floor_3_direction);
    design_prism(floor_3_array, 6, floor_3_xyz, material_asset_struct_floor_3, false, floor_3_direction);
    set_num(floor_junction_6_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 6.
    initial_floor_junction_6_location = FVector(floor_3_array[0].row[0].column[floor_3_xyz.Y - 1]->GetActorLocation().X, floor_3_array[0].row[0].column[floor_3_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_3_array[0].row[floor_3_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_junction_6_array, initial_floor_junction_6_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_6_direction);
    design_prism(floor_junction_6_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_6, false, floor_junction_6_direction);
    spawning_locations.Add(FVector(floor_junction_6_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_6_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_6_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    floor_4_xyz = FIntVector(floor_junction_xyz.X, room_0_xyz.Y - floor_junction_xyz.Y * 3 - floor_3_xyz.Y, 1); // Starting to create Floor 4.
    set_num(floor_4_array, 6, floor_4_xyz);
    initial_floor_4_location = FVector(floor_junction_6_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().X, floor_junction_6_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_junction_6_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_4_array, initial_floor_4_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_4_xyz, plane_size, false, floor_4_direction);
    design_prism(floor_4_array, 6, floor_4_xyz, material_asset_struct_floor_4, false, floor_4_direction);
    set_num(floor_junction_7_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 7.
    initial_floor_junction_7_location = FVector(floor_4_array[0].row[0].column[floor_4_xyz.Y - 1]->GetActorLocation().X, floor_4_array[0].row[0].column[floor_4_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_4_array[0].row[0].column[floor_4_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_junction_7_array, initial_floor_junction_7_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_7_direction);
    design_prism(floor_junction_7_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_7, false, floor_junction_7_direction);
    spawning_locations.Add(FVector(floor_junction_7_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_7_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_7_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    floor_5_xyz = FIntVector(floor_0_xyz.X, floor_junction_xyz.Y, 1); // Starting to create Floor 5.
    set_num(floor_5_array, 6, floor_5_xyz);
    initial_floor_5_location = FVector(floor_junction_2_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X - plane_size, floor_junction_2_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y, floor_junction_2_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_5_array, initial_floor_5_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_5_xyz, plane_size, false, floor_5_direction);
    design_prism(floor_5_array, 6, floor_5_xyz, material_asset_struct_floor_5, false, floor_5_direction);
    set_num(floor_junction_8_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 8.
    initial_floor_junction_8_location = FVector(floor_5_array[0].row[floor_5_xyz.X - 1].column[0]->GetActorLocation().X - plane_size, floor_5_array[0].row[floor_5_xyz.X - 1].column[0]->GetActorLocation().Y, floor_5_array[0].row[floor_5_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_junction_8_array, initial_floor_junction_8_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_8_direction);
    design_prism(floor_junction_8_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_8, false, floor_junction_8_direction);
    spawning_locations.Add(FVector(floor_junction_8_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_8_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_8_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    set_num(stair_3_array, 6, stair_3_xyz); // Starting to create Stair 3.
    initial_stair_3_location = FVector(floor_junction_8_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X - plane_size * stair_3_xyz.X, floor_junction_8_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y, 0.0f);
    spawn_stair(stair_3_array, initial_stair_3_location, plane_size, stair_3_xyz, stair_scale, stair_3_direction);
    design_stair(stair_3_array, 6, stair_0_xyz, material_asset_struct_stair_3, stair_3_direction);
    floor_6_xyz = FIntVector(floor_junction_xyz.X, floor_1_xyz.Y, 1); // Starting to create Floor 6.
    set_num(floor_6_array, 6, floor_6_xyz);
    initial_floor_6_location = FVector(floor_junction_8_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X, floor_junction_8_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_junction_8_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_6_array, initial_floor_6_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_6_xyz, plane_size, false, floor_6_direction);
    design_prism(floor_6_array, 6, floor_6_xyz, material_asset_struct_floor_6, false, floor_6_direction);
    set_num(stair_4_array, 6, stair_4_xyz); // Starting to create Stair 4.
    initial_stair_4_location = FVector(floor_junction_8_array[1].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().X, floor_junction_8_array[1].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().Y + plane_size * stair_4_xyz.Y, 0.0f);
    spawn_stair(stair_4_array, initial_stair_4_location, plane_size, stair_4_xyz, stair_scale, stair_4_direction);
    design_stair(stair_4_array, 6, stair_4_xyz, material_asset_struct_stair_4, stair_4_direction);
    set_num(stair_5_array, 6, stair_5_xyz); // Starting to create Stair 5.
    initial_stair_5_location = FVector(floor_junction_4_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X, floor_junction_4_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_junction_4_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_stair(stair_5_array, initial_stair_5_location, plane_size, stair_5_xyz, stair_scale, stair_5_direction);
    design_stair(stair_5_array, 6, stair_5_xyz, material_asset_struct_stair_5, stair_5_direction);
    set_num(floor_junction_9_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 9.
    initial_floor_junction_9_location = FVector(stair_5_array[0].row[0].column[stair_5_xyz.Y - 1]->GetActorLocation().X, stair_5_array[0].row[0].column[stair_5_xyz.Y - 1]->GetActorLocation().Y - plane_size, stair_5_array[0].row[0].column[stair_5_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_junction_9_array, initial_floor_junction_9_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_9_direction);
    design_prism(floor_junction_9_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_9, false, floor_junction_9_direction);
    spawning_locations.Add(FVector(floor_junction_9_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_9_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_9_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    floor_7_xyz = FIntVector(floor_junction_9_array[0].row[0].column[0]->GetActorLocation().X / 100 - floor_junction_xyz.X, floor_junction_xyz.Y, 1); // Starting to create Floor 7.
    set_num(floor_7_array, 6, floor_7_xyz);
    initial_floor_7_location = FVector(floor_junction_9_array[0].row[0].column[0]->GetActorLocation().X - plane_size, floor_junction_9_array[0].row[0].column[0]->GetActorLocation().Y, floor_junction_9_array[0].row[0].column[0]->GetActorLocation().Z);
    spawn_box(floor_7_array, initial_floor_7_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_7_xyz, plane_size, false, floor_7_direction);
    design_prism(floor_7_array, 6, floor_7_xyz, material_asset_struct_floor_7, false, floor_7_direction);
    floor_8_xyz = FIntVector(floor_junction_xyz.X, floor_junction_9_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y / 100 - floor_junction_xyz.Y, 1); // Starting to create Floor 8.
    set_num(floor_8_array, 6, floor_8_xyz);
    initial_floor_8_location = FVector(floor_junction_9_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().X, floor_junction_9_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_junction_9_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_8_array, initial_floor_8_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_8_xyz, plane_size, false, floor_8_direction);
    design_prism(floor_8_array, 6, floor_8_xyz, material_asset_struct_floor_8, false, floor_8_direction);
    set_num(stair_6_array, 6, stair_6_xyz); // Starting to create Stair 6.
    initial_stair_6_location = FVector(floor_junction_9_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X + plane_size, floor_junction_9_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y, floor_junction_9_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_stair(stair_6_array, initial_stair_6_location, plane_size, stair_6_xyz, stair_scale, stair_6_direction);
    design_stair(stair_6_array, 6, stair_6_xyz, material_asset_struct_stair_6, stair_6_direction);
    set_num(floor_junction_10_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 10.
    initial_floor_junction_10_location = FVector(floor_8_array[0].row[0].column[floor_8_xyz.Y - 1]->GetActorLocation().X, floor_8_array[0].row[0].column[floor_8_xyz.Y - 1]->GetActorLocation().Y - plane_size, floor_8_array[0].row[0].column[floor_8_xyz.Y - 1]->GetActorLocation().Z);
    spawn_box(floor_junction_10_array, initial_floor_junction_10_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_10_direction);
    design_prism(floor_junction_10_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_10, false, floor_junction_10_direction);
    spawning_locations.Add(FVector(floor_junction_10_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_10_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_10_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    set_num(stair_7_array, 6, stair_7_xyz); // Starting to create Stair 7.
    initial_stair_7_location = FVector(floor_junction_10_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X + plane_size, floor_junction_10_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y, floor_junction_10_array[1].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Z);
    spawn_stair(stair_7_array, initial_stair_7_location, plane_size, stair_7_xyz, stair_scale, stair_7_direction);
    design_stair(stair_7_array, 6, stair_7_xyz, material_asset_struct_stair_7, stair_7_direction);
    set_num(floor_junction_11_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 11.
    initial_floor_junction_11_location = FVector(stair_7_array[0].row[stair_7_xyz.X - 1].column[0]->GetActorLocation().X + plane_size, stair_7_array[0].row[stair_7_xyz.X - 1].column[0]->GetActorLocation().Y, stair_7_array[0].row[stair_7_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_junction_11_array, initial_floor_junction_11_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_11_direction);
    design_prism(floor_junction_11_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_11, false, floor_junction_11_direction);
    spawning_locations.Add(FVector(floor_junction_11_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_11_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_11_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    set_num(floor_junction_12_array, 6, floor_junction_xyz);  // Starting to create Floor Junction 12.
    initial_floor_junction_12_location = FVector(stair_6_array[0].row[stair_6_xyz.X - 1].column[0]->GetActorLocation().X + plane_size, stair_6_array[0].row[stair_6_xyz.X - 1].column[0]->GetActorLocation().Y, stair_6_array[0].row[stair_6_xyz.X - 1].column[0]->GetActorLocation().Z);
    spawn_box(floor_junction_12_array, initial_floor_junction_12_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_junction_xyz, plane_size, false, floor_junction_12_direction);
    design_prism(floor_junction_12_array, 6, floor_junction_xyz, material_asset_struct_floor_junction_12, false, floor_junction_12_direction);
    spawning_locations.Add(FVector(floor_junction_12_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().X, floor_junction_12_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Y, floor_junction_12_array[1].row[floor_junction_xyz.X / 2].column[floor_junction_xyz.Y / 2]->GetActorLocation().Z + plane_size * 2));
    floor_9_xyz = FIntVector(floor_junction_xyz.X, floor_junction_12_array[0].row[0].column[0]->GetActorLocation().Y / 100 - floor_junction_xyz.Y, 1); // Starting to create Floor 9.
    set_num(floor_9_array, 6, floor_9_xyz);
    initial_floor_9_location = FVector(floor_junction_12_array[0].row[0].column[0]->GetActorLocation().X, floor_junction_12_array[0].row[0].column[0]->GetActorLocation().Y - plane_size, floor_junction_12_array[0].row[0].column[0]->GetActorLocation().Z);
    spawn_box(floor_9_array, initial_floor_9_location, floor_xy_scale, floor_xz_scale, floor_yz_scale, floor_9_xyz, plane_size, false, floor_9_direction);
    design_prism(floor_9_array, 6, floor_9_xyz, material_asset_struct_floor_9, false, floor_9_direction);
    pillar_0_xyz = FIntVector(floor_7_xyz.X, floor_8_xyz.Y, room_0_xyz.Z); // Starting to create Pillar 0.
    set_num(pillar_0_array, 6, pillar_0_xyz);
    initial_pillar_0_location = FVector(floor_junction_9_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().X - plane_size, floor_junction_9_array[0].row[0].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y - plane_size, 0.0f);
    spawn_box(pillar_0_array, initial_pillar_0_location, pillar_xy_scale, pillar_xz_scale, pillar_yz_scale, pillar_0_xyz, plane_size, false, pillar_0_direction);
    design_prism(pillar_0_array, 6, pillar_0_xyz, material_asset_struct_pillar_0, false, pillar_0_direction);
    pillar_1_xyz = FIntVector(stair_7_xyz.X, floor_8_xyz.Y, room_0_xyz.Z); // Starting to create Pillar 1.
    set_num(pillar_1_array, 6, pillar_1_xyz);
    initial_pillar_1_location = FVector(floor_junction_9_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().X + plane_size, floor_junction_9_array[0].row[floor_junction_xyz.X - 1].column[floor_junction_xyz.Y - 1]->GetActorLocation().Y - plane_size, 0.0f);
    spawn_box(pillar_1_array, initial_pillar_1_location, pillar_xy_scale, pillar_xz_scale, pillar_yz_scale, pillar_1_xyz, plane_size, false, pillar_1_direction);
    design_prism(pillar_1_array, 6, pillar_1_xyz, material_asset_struct_pillar_1, false, pillar_1_direction);
    pillar_2_xyz = FIntVector(stair_7_xyz.X, stair_5_xyz.Y, room_0_xyz.Z); // Starting to create Pillar 2.
    set_num(pillar_2_array, 6, pillar_2_xyz);
    initial_pillar_2_location = FVector(floor_junction_9_array[0].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().X + plane_size, floor_junction_9_array[0].row[floor_junction_xyz.X - 1].column[0]->GetActorLocation().Y + plane_size, 0.0f);
    spawn_box(pillar_2_array, initial_pillar_2_location, pillar_xy_scale, pillar_xz_scale, pillar_yz_scale, pillar_2_xyz, plane_size, false, pillar_2_direction);
    design_prism(pillar_2_array, 6, pillar_2_xyz, material_asset_struct_pillar_3, false, pillar_2_direction);
    pillar_3_xyz = FIntVector(floor_7_xyz.X, stair_5_xyz.Y, room_0_xyz.Z); // Starting to create Pillar 3.
    set_num(pillar_3_array, 6, pillar_3_xyz);
    initial_pillar_3_location = FVector(floor_junction_9_array[0].row[0].column[0]->GetActorLocation().X - plane_size, floor_junction_9_array[0].row[0].column[0]->GetActorLocation().Y + plane_size, 0.0f);
    spawn_box(pillar_3_array, initial_pillar_3_location, pillar_xy_scale, pillar_xz_scale, pillar_yz_scale, pillar_3_xyz, plane_size, false, pillar_3_direction);
    design_prism(pillar_3_array, 6, pillar_3_xyz, material_asset_struct_pillar_3, false, pillar_3_direction);
    default_player_start_PIE = UGameplayStatics::GetActorOfClass(world, APlayerStartPIE::StaticClass());
    if(default_player_start_PIE) default_player_start_PIE->Destroy();
    actor = UGameplayStatics::GetActorOfClass(world, ANavMeshBoundsVolume::StaticClass());
    nav_mesh_bounds_voulume = Cast<ANavMeshBoundsVolume>(actor);
    navigation_system = FNavigationSystem::GetCurrent<UNavigationSystemV1>(world);
    if (nav_mesh_bounds_voulume) {
        nav_mesh_bounds_voulume->GetRootComponent()->SetMobility(EComponentMobility::Movable);
        nav_mesh_bounds_voulume->SetActorLocation(FVector(room_0_array[0].row[room_0_xyz.X - 1].column[0]->GetActorLocation().X / 2, room_0_array[0].row[0].column[room_0_xyz.Y - 1]->GetActorLocation().Y / 2, room_0_array[2].row[0].column[room_0_xyz.Z - 1]->GetActorLocation().Z / 2));
        nav_mesh_bounds_voulume->SetActorRelativeScale3D(FVector(room_0_xyz.X / 2, room_0_xyz.Y / 2, room_0_xyz.Z / 2));
        nav_mesh_bounds_voulume->GetRootComponent()->UpdateBounds();
        nav_mesh_bounds_voulume->GetRootComponent()->SetMobility(EComponentMobility::Static);
        navigation_system->OnNavigationBoundsUpdated(nav_mesh_bounds_voulume);
    }
    player_controller = UGameplayStatics::GetPlayerController(world, 0);
}
AActor* Agame_mode_base_level_arena::ChoosePlayerStart_Implementation(AController* player) {
    player_start = world->SpawnActor<Aplayer_start>(FVector(300.0f, 300.0f, 10.0f), FRotator(0.0f));
    return player_start;
}
void Agame_mode_base_level_arena::StartPlay() {
    Super::StartPlay();
    time_start = world->GetTimeSeconds();
    paper_player = Cast<Apaper_player>(player_controller->GetPawn());
}
void Agame_mode_base_level_arena::Tick(float delta_time) {
    Super::Tick(delta_time);
    FActorSpawnParameters enemy_spawn_parameters;
    current_time = world->GetTimeSeconds();
    seconds = calculate_time(current_time - time_start);
    if (seconds != 0 && seconds != previous_seconds && seconds % 1 == 0) {
        previous_seconds = seconds;
        enemy_spawn_parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
        paper_player = Cast<Apaper_player>(player_controller->GetPawn());
        if (paper_player) {
            disallowed_spawn_count = 0;
            allowed_spawn = true;
            while ((paper_player->GetActorLocation() - spawning_locations[spawning_index]).Size2D() <= disallowed_spawning_distance) {
                disallowed_spawn_count++;
                spawning_index++;
                if (spawning_index == spawning_locations.Num()) spawning_index = 0;
                if (disallowed_spawn_count == spawning_locations.Num()) {
                    allowed_spawn = false;
                    break;
                }
            }
            if (allowed_spawn) {
                world->SpawnActor<Aenemy>(spawning_locations[spawning_index++], FRotator(0.0f), enemy_spawn_parameters);
                if (spawning_index == spawning_locations.Num()) spawning_index = 0;
            }
        }
    }
}
void Agame_mode_base_level_arena::EndPlay(EEndPlayReason::Type reason) {
    Super::EndPlay(reason);
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
void Agame_mode_base_level_arena::spawn_box(TArray<Fplane_struct>& box_array, FVector initial_location, FVector scale_xy, FVector scale_xz, FVector scale_yz, FIntVector xyz, float distance, bool inside, TEnumAsByte<direction> plane_direction) {
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
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance, location.Z += distance / 4) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance, location.Z += distance / 4) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - distance / 2, initial_location.Z + distance / 4 / 2);
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - distance / 2 + xyz.Y * distance, initial_location.Z + distance / 4 / 2);
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X - distance / 2, initial_location.Y, initial_location.Z + distance / 4 / 2);
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.X += distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + distance / 2, initial_location.Y, initial_location.Z + distance / 4 / 2);
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.X += distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
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
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + distance / 4);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y += distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y - distance / 2, initial_location.Z + distance / 4 / 2);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Y += distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y + distance / 2, initial_location.Z + distance / 4 / 2);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Y += distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X + distance / 2, initial_location.Y, initial_location.Z + distance / 4 / 2);
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X + distance / 2 - distance * xyz.X, initial_location.Y, initial_location.Z + distance / 4 / 2);
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y += distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
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
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance, location.Z += distance / 4) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + (distance / 4));
                temp_location.Y = location.Y;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance, location.Z += distance / 4) {
                    location.Y = temp_location.Y;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y + distance / 2, initial_location.Z + distance / 4 / 2);
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y + distance / 2 - distance * xyz.Y, initial_location.Z + distance / 4 / 2);
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X + distance / 2, initial_location.Y, initial_location.Z + distance / 4 / 2);
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.X -= distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X - distance / 2, initial_location.Y, initial_location.Z + distance / 4 / 2);
                temp_location.X = location.X;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    location.X = temp_location.X;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.X -= distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
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
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, ceiling_rotation);
                    }
                }
            }
            else if (face_number == 1) {
                location = FVector(initial_location.X, initial_location.Y, initial_location.Z + distance / 4);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Y; column_number++, location.Y -= distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, floor_rotation);
                    }
                }
            }
            else if (face_number == 2) {
                location = FVector(initial_location.X, initial_location.Y + distance / 2, initial_location.Z + distance / 4 / 2);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Y -= distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_left_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 3) {
                location = FVector(initial_location.X, initial_location.Y - distance / 2, initial_location.Z + distance / 4 / 2);
                temp_location.Y = location.Y;
                temp_location.Z = location.Z;
                for (int32 row_number = 0; row_number < xyz.X; row_number++, location.X += distance) {
                    location.Y = temp_location.Y;
                    location.Z = temp_location.Z;
                    for (int32 column_number = 0; column_number < xyz.Z; column_number++, location.Y -= distance, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_right_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 4) {
                location = FVector(initial_location.X - distance / 2, initial_location.Y, initial_location.Z + distance / 4 / 2);
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_front_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
            else if (face_number == 5) {
                location = FVector(initial_location.X - distance / 2 + distance * xyz.X, initial_location.Y, initial_location.Z + distance / 4 / 2);
                for (int32 row_number = 0; row_number < xyz.Y; row_number++, location.Y -= distance) {
                    for (int32 column_number = 0; column_number < 1; column_number++, location.Z += distance / 4) {
                        stair_array[face_number].row[row_number].column[column_number] = world->SpawnActor<Astatic_mesh_plane>(static_mesh_plane_class, location, wall_back_rotation);
                        if (stair_array[face_number].row[row_number].column[column_number]) {
                            stair_array[face_number].row[row_number].column[column_number]->SetActorScale3D(scale);
                        }
                    }
                }
            }
        }
    }
}
void Agame_mode_base_level_arena::assign_materials_to_packs(Fmaterial_asset_struct_pack& material_asset_struct_pack, UMaterialInterface* bottom_left, UMaterialInterface* bottom_middle, UMaterialInterface* bottom_right, UMaterialInterface* middle_left, UMaterialInterface* middle_middle, UMaterialInterface* middle_right, UMaterialInterface* top_left, UMaterialInterface* top_middle, UMaterialInterface* top_right) {
    material_asset_struct_pack.bottom_left = bottom_left;
    material_asset_struct_pack.bottom_middle = bottom_middle;
    material_asset_struct_pack.bottom_right = bottom_right;
    material_asset_struct_pack.middle_left = middle_left;
    material_asset_struct_pack.middle_middle = middle_middle;
    material_asset_struct_pack.middle_right = middle_right;
    material_asset_struct_pack.top_left = top_left;
    material_asset_struct_pack.top_middle = top_middle;
    material_asset_struct_pack.top_right = top_right;
}
void Agame_mode_base_level_arena::assign_material_packs_to_faces(Fmaterial_asset_struct &material_asset_struct, Fmaterial_asset_struct_pack material_asset_struct_pack_0, Fmaterial_asset_struct_pack material_asset_struct_pack_1, Fmaterial_asset_struct_pack material_asset_struct_pack_2, Fmaterial_asset_struct_pack material_asset_struct_pack_3, Fmaterial_asset_struct_pack material_asset_struct_pack_4, Fmaterial_asset_struct_pack material_asset_struct_pack_5) {
    material_asset_struct.face_0_bottom_left = material_asset_struct_pack_0.bottom_left;
    material_asset_struct.face_0_bottom_middle = material_asset_struct_pack_0.bottom_middle;
    material_asset_struct.face_0_bottom_right = material_asset_struct_pack_0.bottom_right;
    material_asset_struct.face_0_middle_left = material_asset_struct_pack_0.middle_left;
    material_asset_struct.face_0_middle_middle = material_asset_struct_pack_0.middle_middle;
    material_asset_struct.face_0_middle_right = material_asset_struct_pack_0.middle_right;
    material_asset_struct.face_0_top_left = material_asset_struct_pack_0.top_left;
    material_asset_struct.face_0_top_middle = material_asset_struct_pack_0.top_middle;
    material_asset_struct.face_0_top_right = material_asset_struct_pack_0.top_right;
    material_asset_struct.face_1_bottom_left = material_asset_struct_pack_1.bottom_left;
    material_asset_struct.face_1_bottom_middle = material_asset_struct_pack_1.bottom_middle;
    material_asset_struct.face_1_bottom_right = material_asset_struct_pack_1.bottom_right;
    material_asset_struct.face_1_middle_left = material_asset_struct_pack_1.middle_left;
    material_asset_struct.face_1_middle_middle = material_asset_struct_pack_1.middle_middle;
    material_asset_struct.face_1_middle_right = material_asset_struct_pack_1.middle_right;
    material_asset_struct.face_1_top_left = material_asset_struct_pack_1.top_left;
    material_asset_struct.face_1_top_middle = material_asset_struct_pack_1.top_middle;
    material_asset_struct.face_1_top_right = material_asset_struct_pack_1.top_right;
    material_asset_struct.face_2_bottom_left = material_asset_struct_pack_2.bottom_left;
    material_asset_struct.face_2_bottom_middle = material_asset_struct_pack_2.bottom_middle;
    material_asset_struct.face_2_bottom_right = material_asset_struct_pack_2.bottom_right;
    material_asset_struct.face_2_middle_left = material_asset_struct_pack_2.middle_left;
    material_asset_struct.face_2_middle_middle = material_asset_struct_pack_2.middle_middle;
    material_asset_struct.face_2_middle_right = material_asset_struct_pack_2.middle_right;
    material_asset_struct.face_2_top_left = material_asset_struct_pack_2.top_left;
    material_asset_struct.face_2_top_middle = material_asset_struct_pack_2.top_middle;
    material_asset_struct.face_2_top_right = material_asset_struct_pack_2.top_right;
    material_asset_struct.face_3_bottom_left = material_asset_struct_pack_3.bottom_left;
    material_asset_struct.face_3_bottom_middle = material_asset_struct_pack_3.bottom_middle;
    material_asset_struct.face_3_bottom_right = material_asset_struct_pack_3.bottom_right;
    material_asset_struct.face_3_middle_left = material_asset_struct_pack_3.middle_left;
    material_asset_struct.face_3_middle_middle = material_asset_struct_pack_3.middle_middle;
    material_asset_struct.face_3_middle_right = material_asset_struct_pack_3.middle_right;
    material_asset_struct.face_3_top_left = material_asset_struct_pack_3.top_left;
    material_asset_struct.face_3_top_middle = material_asset_struct_pack_3.top_middle;
    material_asset_struct.face_3_top_right = material_asset_struct_pack_3.top_right;
    material_asset_struct.face_4_bottom_left = material_asset_struct_pack_4.bottom_left;
    material_asset_struct.face_4_bottom_middle = material_asset_struct_pack_4.bottom_middle;
    material_asset_struct.face_4_bottom_right = material_asset_struct_pack_4.bottom_right;
    material_asset_struct.face_4_middle_left = material_asset_struct_pack_4.middle_left;
    material_asset_struct.face_4_middle_middle = material_asset_struct_pack_4.middle_middle;
    material_asset_struct.face_4_middle_right = material_asset_struct_pack_4.middle_right;
    material_asset_struct.face_4_top_left = material_asset_struct_pack_4.top_left;
    material_asset_struct.face_4_top_middle = material_asset_struct_pack_4.top_middle;
    material_asset_struct.face_4_top_right = material_asset_struct_pack_4.top_right;
    material_asset_struct.face_5_bottom_left = material_asset_struct_pack_5.bottom_left;
    material_asset_struct.face_5_bottom_middle = material_asset_struct_pack_5.bottom_middle;
    material_asset_struct.face_5_bottom_right = material_asset_struct_pack_5.bottom_right;
    material_asset_struct.face_5_middle_left = material_asset_struct_pack_5.middle_left;
    material_asset_struct.face_5_middle_middle = material_asset_struct_pack_5.middle_middle;
    material_asset_struct.face_5_middle_right = material_asset_struct_pack_5.middle_right;
    material_asset_struct.face_5_top_left = material_asset_struct_pack_5.top_left;
    material_asset_struct.face_5_top_middle = material_asset_struct_pack_5.top_middle;
    material_asset_struct.face_5_top_right = material_asset_struct_pack_5.top_right;
}
void Agame_mode_base_level_arena::design_prism(TArray<Fplane_struct>& prism_array, int32 face_count, FIntVector xyz_prism, Fmaterial_asset_struct material_asset_struct, bool inside, TEnumAsByte<direction> prism_direction) {
    for (int32 face_number = 0; face_number < face_count; face_number++) {
        if (face_number == 0) {
            for (int32 row_number = 0; row_number < xyz_prism.X; row_number++) {
                for (int32 column_number = 0; column_number < xyz_prism.Y; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_0_top_left : prism_direction == right ? material_asset_struct.face_0_top_right : prism_direction == back ? material_asset_struct.face_0_bottom_right : material_asset_struct.face_0_bottom_left): (prism_direction == front ? material_asset_struct.face_0_top_right : prism_direction == right ? material_asset_struct.face_0_top_left : prism_direction == back ? material_asset_struct.face_0_bottom_left : material_asset_struct.face_0_bottom_right));
                        else if (column_number != xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_0_middle_left : prism_direction == right ? material_asset_struct.face_0_middle_right : prism_direction == back ? material_asset_struct.face_0_middle_right : material_asset_struct.face_0_middle_left): (prism_direction == front ? material_asset_struct.face_0_middle_right : prism_direction == right ? material_asset_struct.face_0_middle_left : prism_direction == back ? material_asset_struct.face_0_middle_left : material_asset_struct.face_0_middle_right));
                        else if (column_number == xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_0_bottom_left : prism_direction == right ? material_asset_struct.face_0_bottom_right : prism_direction == back ? material_asset_struct.face_0_top_right : material_asset_struct.face_0_top_left) : (prism_direction == front ? material_asset_struct.face_0_bottom_right : prism_direction == right ? material_asset_struct.face_0_bottom_left : prism_direction == back ? material_asset_struct.face_0_top_left : material_asset_struct.face_0_top_right));
                    }
                    else if (row_number != xyz_prism.X - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, prism_direction == front ? material_asset_struct.face_0_top_middle : prism_direction == right ? material_asset_struct.face_0_top_middle : prism_direction == back ? material_asset_struct.face_0_bottom_middle : material_asset_struct.face_0_bottom_middle);
                        else if (column_number != xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_0_middle_middle);
                        else if (column_number == xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, prism_direction == front ? material_asset_struct.face_0_bottom_middle : prism_direction == right ? material_asset_struct.face_0_bottom_middle : prism_direction == back ? material_asset_struct.face_0_top_middle : material_asset_struct.face_0_top_middle);
                    }
                    else if (row_number == xyz_prism.X - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_0_top_right : prism_direction == right ? material_asset_struct.face_0_top_left : prism_direction == back ? material_asset_struct.face_0_bottom_left : material_asset_struct.face_0_bottom_right) : (prism_direction == front ? material_asset_struct.face_0_top_left : prism_direction == right ? material_asset_struct.face_0_top_right : prism_direction == back ? material_asset_struct.face_0_bottom_right : material_asset_struct.face_0_bottom_left));
                        else if (column_number != xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_0_middle_right : prism_direction == right ? material_asset_struct.face_0_middle_left : prism_direction == back ? material_asset_struct.face_0_middle_left : material_asset_struct.face_0_middle_right) : (prism_direction == front ? material_asset_struct.face_0_middle_left : prism_direction == right ? material_asset_struct.face_0_middle_right : prism_direction == back ? material_asset_struct.face_0_middle_right : material_asset_struct.face_0_middle_left));
                        else if (column_number == xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_0_bottom_right : prism_direction == right ? material_asset_struct.face_0_bottom_left : prism_direction == back ? material_asset_struct.face_0_top_left : material_asset_struct.face_0_top_right) : (prism_direction == front ? material_asset_struct.face_0_bottom_left : prism_direction == right ? material_asset_struct.face_0_bottom_right : prism_direction == back ? material_asset_struct.face_0_top_right : material_asset_struct.face_0_top_left));
                    }
                }
            }
        }
        else if (face_number == 1) {
            for (int32 row_number = 0; row_number < xyz_prism.X; row_number++) {
                for (int32 column_number = 0; column_number < xyz_prism.Y; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_1_top_right : prism_direction == right ? material_asset_struct.face_1_top_left : prism_direction == back ? material_asset_struct.face_1_bottom_left : material_asset_struct.face_1_bottom_right) : (prism_direction == front ? material_asset_struct.face_1_top_left : prism_direction == right ? material_asset_struct.face_1_top_right : prism_direction == back ? material_asset_struct.face_1_bottom_right : material_asset_struct.face_1_bottom_left));
                        else if (column_number != xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_1_middle_right : prism_direction == right ? material_asset_struct.face_1_middle_left : prism_direction == back ? material_asset_struct.face_1_middle_left : material_asset_struct.face_1_middle_right) : (prism_direction == front ? material_asset_struct.face_1_middle_left : prism_direction == right ? material_asset_struct.face_1_middle_right : prism_direction == back ? material_asset_struct.face_1_middle_right : material_asset_struct.face_1_middle_left));
                        else if (column_number == xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_1_bottom_right : prism_direction == right ? material_asset_struct.face_1_bottom_left : prism_direction == back ? material_asset_struct.face_1_top_left : material_asset_struct.face_1_top_right) : (prism_direction == front ? material_asset_struct.face_1_bottom_left : prism_direction == right ? material_asset_struct.face_1_bottom_right : prism_direction == back ? material_asset_struct.face_1_top_right : material_asset_struct.face_1_top_left));
                    }
                    else if (row_number != xyz_prism.X - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, prism_direction == front ? material_asset_struct.face_1_top_middle : prism_direction == right ? material_asset_struct.face_1_top_middle : prism_direction == back ? material_asset_struct.face_1_bottom_middle : material_asset_struct.face_1_bottom_middle);
                        else if (column_number != xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_1_middle_middle);
                        else if (column_number == xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, prism_direction == front ? material_asset_struct.face_1_bottom_middle : prism_direction == right ? material_asset_struct.face_1_bottom_middle : prism_direction == back ? material_asset_struct.face_1_top_middle : material_asset_struct.face_1_top_middle);
                    }
                    else if (row_number == xyz_prism.X - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_1_top_left : prism_direction == right ? material_asset_struct.face_1_top_right : prism_direction == back ? material_asset_struct.face_1_bottom_right : material_asset_struct.face_1_bottom_left) : (prism_direction == front ? material_asset_struct.face_1_top_right : prism_direction == right ? material_asset_struct.face_1_top_left : prism_direction == back ? material_asset_struct.face_1_bottom_left : material_asset_struct.face_1_bottom_right));
                        else if (column_number != xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_1_middle_left : prism_direction == right ? material_asset_struct.face_1_middle_right : prism_direction == back ? material_asset_struct.face_1_middle_right : material_asset_struct.face_1_middle_left) : (prism_direction == front ? material_asset_struct.face_1_middle_right : prism_direction == right ? material_asset_struct.face_1_middle_left : prism_direction == back ? material_asset_struct.face_1_middle_left : material_asset_struct.face_1_middle_right));
                        else if (column_number == xyz_prism.Y - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_1_bottom_left : prism_direction == right ? material_asset_struct.face_1_bottom_right : prism_direction == back ? material_asset_struct.face_1_top_right : material_asset_struct.face_1_top_left) : (prism_direction == front ? material_asset_struct.face_1_bottom_right : prism_direction == right ? material_asset_struct.face_1_bottom_left : prism_direction == back ? material_asset_struct.face_1_top_left : material_asset_struct.face_1_top_right));
                    }
                }
            }
        }
        else if (face_number == 2) {
            for (int32 row_number = 0; row_number < xyz_prism.X; row_number++) {
                for (int32 column_number = 0; column_number < xyz_prism.Z; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_2_bottom_left : prism_direction == right ? material_asset_struct.face_2_bottom_right : prism_direction == back ? material_asset_struct.face_2_bottom_left : material_asset_struct.face_2_bottom_right) : (prism_direction == front ? material_asset_struct.face_2_bottom_right : prism_direction == right ? material_asset_struct.face_2_bottom_left : prism_direction == back ? material_asset_struct.face_2_bottom_right : material_asset_struct.face_2_bottom_left));
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_2_middle_left : prism_direction == right ? material_asset_struct.face_2_middle_right : prism_direction == back ? material_asset_struct.face_2_middle_left : material_asset_struct.face_2_middle_right) : (prism_direction == front ? material_asset_struct.face_2_middle_right : prism_direction == right ? material_asset_struct.face_2_middle_left : prism_direction == back ? material_asset_struct.face_2_middle_right : material_asset_struct.face_2_middle_left));
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_2_top_left : prism_direction == right ? material_asset_struct.face_2_top_right : prism_direction == back ? material_asset_struct.face_2_top_left : material_asset_struct.face_2_top_right) : (prism_direction == front ? material_asset_struct.face_2_top_right : prism_direction == right ? material_asset_struct.face_2_top_left : prism_direction == back ? material_asset_struct.face_2_top_right : material_asset_struct.face_2_top_left));
                    }
                    else if (row_number != xyz_prism.X - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_2_bottom_middle);
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_2_middle_middle);
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_2_top_middle);
                    }
                    else if (row_number == xyz_prism.X - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_2_bottom_right : prism_direction == right ? material_asset_struct.face_2_bottom_left : prism_direction == back ? material_asset_struct.face_2_bottom_right : material_asset_struct.face_2_bottom_left) : (prism_direction == front ? material_asset_struct.face_2_bottom_left : prism_direction == right ? material_asset_struct.face_2_bottom_right : prism_direction == back ? material_asset_struct.face_2_bottom_left : material_asset_struct.face_2_bottom_right));
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_2_middle_right : prism_direction == right ? material_asset_struct.face_2_middle_left : prism_direction == back ? material_asset_struct.face_2_middle_right : material_asset_struct.face_2_middle_left) : (prism_direction == front ? material_asset_struct.face_2_middle_left : prism_direction == right ? material_asset_struct.face_2_middle_right : prism_direction == back ? material_asset_struct.face_2_middle_left : material_asset_struct.face_2_middle_right));
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_2_top_right : prism_direction == right ? material_asset_struct.face_2_top_left : prism_direction == back ? material_asset_struct.face_2_top_right : material_asset_struct.face_2_top_left) : (prism_direction == front ? material_asset_struct.face_2_top_left : prism_direction == right ? material_asset_struct.face_2_top_right : prism_direction == back ? material_asset_struct.face_2_top_left : material_asset_struct.face_2_top_right));
                    }
                }
            }
        }
        else if (face_number == 3) {
            for (int32 row_number = 0; row_number < xyz_prism.X; row_number++) {
                for (int32 column_number = 0; column_number < xyz_prism.Z; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_3_bottom_right : prism_direction == right ? material_asset_struct.face_3_bottom_left : prism_direction == back ? material_asset_struct.face_3_bottom_right : material_asset_struct.face_3_bottom_left) : (prism_direction == front ? material_asset_struct.face_3_bottom_left : prism_direction == right ? material_asset_struct.face_2_bottom_right : prism_direction == back ? material_asset_struct.face_3_bottom_left : material_asset_struct.face_3_bottom_right));
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_3_middle_right : prism_direction == right ? material_asset_struct.face_3_middle_left : prism_direction == back ? material_asset_struct.face_3_middle_right : material_asset_struct.face_3_middle_left) : (prism_direction == front ? material_asset_struct.face_3_middle_left : prism_direction == right ? material_asset_struct.face_3_middle_right : prism_direction == back ? material_asset_struct.face_3_middle_left : material_asset_struct.face_3_middle_right));
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_3_top_right : prism_direction == right ? material_asset_struct.face_3_top_left : prism_direction == back ? material_asset_struct.face_3_top_right : material_asset_struct.face_3_top_left) : (prism_direction == front ? material_asset_struct.face_3_top_left : prism_direction == right ? material_asset_struct.face_3_top_right : prism_direction == back ? material_asset_struct.face_3_top_left : material_asset_struct.face_3_top_right));
                    }
                    else if (row_number != xyz_prism.X - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_3_bottom_middle);
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_3_middle_middle);
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_3_top_middle);
                    }
                    else if (row_number == xyz_prism.X - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_3_bottom_left : prism_direction == right ? material_asset_struct.face_3_bottom_right : prism_direction == back ? material_asset_struct.face_3_bottom_left : material_asset_struct.face_3_bottom_right) : (prism_direction == front ? material_asset_struct.face_3_bottom_right : prism_direction == right ? material_asset_struct.face_3_bottom_left : prism_direction == back ? material_asset_struct.face_3_bottom_right : material_asset_struct.face_3_bottom_left));
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_3_middle_left : prism_direction == right ? material_asset_struct.face_3_middle_right : prism_direction == back ? material_asset_struct.face_3_middle_left : material_asset_struct.face_3_middle_right) : (prism_direction == front ? material_asset_struct.face_3_middle_right : prism_direction == right ? material_asset_struct.face_3_middle_left : prism_direction == back ? material_asset_struct.face_3_middle_right : material_asset_struct.face_3_middle_left));
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_3_top_left : prism_direction == right ? material_asset_struct.face_3_top_right : prism_direction == back ? material_asset_struct.face_3_top_left : material_asset_struct.face_3_top_right) : (prism_direction == front ? material_asset_struct.face_3_top_right : prism_direction == right ? material_asset_struct.face_3_top_left : prism_direction == back ? material_asset_struct.face_3_top_right : material_asset_struct.face_3_top_left));
                    }
                }
            }
        }
        else if (face_number == 4) {
            for (int32 row_number = 0; row_number < xyz_prism.Y; row_number++) {
                for (int32 column_number = 0; column_number < xyz_prism.Z; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_4_bottom_right : prism_direction == right ? material_asset_struct.face_4_bottom_left : prism_direction == back ? material_asset_struct.face_4_bottom_right : material_asset_struct.face_4_bottom_left) : (prism_direction == front ? material_asset_struct.face_4_bottom_left : prism_direction == right ? material_asset_struct.face_4_bottom_right : prism_direction == back ? material_asset_struct.face_4_bottom_left : material_asset_struct.face_4_bottom_right));
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_4_middle_right : prism_direction == right ? material_asset_struct.face_4_middle_left : prism_direction == back ? material_asset_struct.face_4_middle_right : material_asset_struct.face_4_middle_left) : (prism_direction == front ? material_asset_struct.face_4_middle_left : prism_direction == right ? material_asset_struct.face_4_middle_right : prism_direction == back ? material_asset_struct.face_4_middle_left : material_asset_struct.face_4_middle_right));
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_4_top_right : prism_direction == right ? material_asset_struct.face_4_top_left : prism_direction == back ? material_asset_struct.face_4_top_right : material_asset_struct.face_4_top_left): (prism_direction == front ? material_asset_struct.face_4_top_left : prism_direction == right ? material_asset_struct.face_4_top_right : prism_direction == back ? material_asset_struct.face_4_top_left : material_asset_struct.face_4_top_right));
                    }
                    else if (row_number != xyz_prism.Y - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_4_bottom_middle);
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_4_middle_middle);
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_4_top_middle);
                    }
                    else if (row_number == xyz_prism.Y - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_4_bottom_left : prism_direction == right ? material_asset_struct.face_4_bottom_right : prism_direction == back ? material_asset_struct.face_4_bottom_left : material_asset_struct.face_4_bottom_right) : (prism_direction == front ? material_asset_struct.face_4_bottom_right : prism_direction == right ? material_asset_struct.face_4_bottom_left : prism_direction == back ? material_asset_struct.face_4_bottom_right : material_asset_struct.face_4_bottom_left));
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_4_middle_left : prism_direction == right ? material_asset_struct.face_4_middle_right : prism_direction == back ? material_asset_struct.face_4_middle_left : material_asset_struct.face_4_middle_right) : (prism_direction == front ? material_asset_struct.face_4_middle_right : prism_direction == right ? material_asset_struct.face_4_middle_left : prism_direction == back ? material_asset_struct.face_4_middle_right : material_asset_struct.face_4_middle_left));
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_4_top_left : prism_direction == right ? material_asset_struct.face_4_top_right : prism_direction == back ? material_asset_struct.face_4_top_left : material_asset_struct.face_4_top_right) : (prism_direction == front ? material_asset_struct.face_4_top_right : prism_direction == right ? material_asset_struct.face_4_top_left : prism_direction == back ? material_asset_struct.face_4_top_right : material_asset_struct.face_4_top_left));
                    }
                }
            }
        }
        else if (face_number == 5) {
            for (int32 row_number = 0; row_number < xyz_prism.Y; row_number++) {
                for (int32 column_number = 0; column_number < xyz_prism.Z; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_5_bottom_left : prism_direction == right ? material_asset_struct.face_5_bottom_right : prism_direction == back ? material_asset_struct.face_5_bottom_left : material_asset_struct.face_5_bottom_right) : (prism_direction == front ? material_asset_struct.face_5_bottom_right : prism_direction == right ? material_asset_struct.face_5_bottom_left : prism_direction == back ? material_asset_struct.face_5_bottom_right : material_asset_struct.face_5_bottom_left));
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_5_middle_left : prism_direction == right ? material_asset_struct.face_5_middle_right : prism_direction == back ? material_asset_struct.face_5_middle_left : material_asset_struct.face_5_middle_right) : (prism_direction == front ? material_asset_struct.face_5_middle_right : prism_direction == right ? material_asset_struct.face_5_middle_left : prism_direction == back ? material_asset_struct.face_5_middle_right : material_asset_struct.face_5_middle_left));
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_5_top_left : prism_direction == right ? material_asset_struct.face_5_top_right : prism_direction == back ? material_asset_struct.face_5_top_left : material_asset_struct.face_5_top_right) : (prism_direction == front ? material_asset_struct.face_5_top_right : prism_direction == right ? material_asset_struct.face_5_top_left : prism_direction == back ? material_asset_struct.face_5_top_right : material_asset_struct.face_5_top_left));
                    }
                    else if (row_number != xyz_prism.Y - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_5_bottom_middle);
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_5_middle_middle);
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_5_top_middle);
                    }
                    else if (row_number == xyz_prism.Y - 1) {
                        if (column_number == 0) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_5_bottom_right : prism_direction == right ? material_asset_struct.face_5_bottom_left : prism_direction == back ? material_asset_struct.face_5_bottom_right : material_asset_struct.face_5_bottom_left) : (prism_direction == front ? material_asset_struct.face_5_bottom_left : prism_direction == right ? material_asset_struct.face_5_bottom_right : prism_direction == back ? material_asset_struct.face_5_bottom_left : material_asset_struct.face_5_bottom_right));
                        else if (column_number != xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_5_middle_right : prism_direction == right ? material_asset_struct.face_5_middle_left : prism_direction == back ? material_asset_struct.face_5_middle_right : material_asset_struct.face_5_middle_left) : (prism_direction == front ? material_asset_struct.face_5_middle_left : prism_direction == right ? material_asset_struct.face_5_middle_right : prism_direction == back ? material_asset_struct.face_5_middle_left : material_asset_struct.face_5_middle_right));
                        else if (column_number == xyz_prism.Z - 1) prism_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, inside ? (prism_direction == front ? material_asset_struct.face_5_top_right : prism_direction == right ? material_asset_struct.face_5_top_left : prism_direction == back ? material_asset_struct.face_5_top_right : material_asset_struct.face_5_top_left) : (prism_direction == front ? material_asset_struct.face_5_top_left : prism_direction == right ? material_asset_struct.face_5_top_right : prism_direction == back ? material_asset_struct.face_5_top_left : material_asset_struct.face_5_top_right));
                    }
                }
            }
        }
    }
}
void Agame_mode_base_level_arena::design_stair(TArray<Fplane_struct>& stair_array, int32 face_count, FIntVector xyz_stair, Fmaterial_asset_struct material_asset_struct, TEnumAsByte<direction> stair_direction) {
    for (int32 face_number = 0; face_number < face_count; face_number++) {
        if (face_number == 0) {
            for (int32 row_number = 0; row_number < xyz_stair.X; row_number++) {
                for (int32 column_number = 0; column_number < xyz_stair.Y; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_0_top_right : stair_direction == right ? material_asset_struct.face_0_top_left : stair_direction == back ? material_asset_struct.face_0_bottom_left : material_asset_struct.face_0_bottom_right);
                        else if (column_number != xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_0_middle_right : stair_direction == right ? material_asset_struct.face_0_middle_left : stair_direction == back ? material_asset_struct.face_0_middle_left : material_asset_struct.face_0_middle_right);
                        else if (column_number == xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_0_bottom_right : stair_direction == right ? material_asset_struct.face_0_bottom_left : stair_direction == back ? material_asset_struct.face_0_top_left : material_asset_struct.face_0_top_right);
                    }
                    else if (row_number != xyz_stair.X - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_0_top_middle : stair_direction == right ? material_asset_struct.face_0_top_middle : stair_direction == back ? material_asset_struct.face_0_bottom_middle : material_asset_struct.face_0_bottom_middle);
                        else if (column_number != xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_0_middle_middle);
                        else if (column_number == xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_0_bottom_middle : stair_direction == right ? material_asset_struct.face_0_bottom_middle : stair_direction == back ? material_asset_struct.face_0_top_middle : material_asset_struct.face_0_top_middle);
                    }
                    else if (row_number == xyz_stair.X - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_0_top_left : stair_direction == right ? material_asset_struct.face_0_top_right : stair_direction == back ? material_asset_struct.face_0_bottom_right : material_asset_struct.face_0_bottom_left);
                        else if (column_number != xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_0_middle_left : stair_direction == right ? material_asset_struct.face_0_middle_right : stair_direction == back ? material_asset_struct.face_0_middle_right : material_asset_struct.face_0_middle_left);
                        else if (column_number == xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_0_bottom_left : stair_direction == right ? material_asset_struct.face_0_bottom_right : stair_direction == back ? material_asset_struct.face_0_top_right : material_asset_struct.face_0_top_left);
                    }
                }
            }
        }
        else if (face_number == 1) {
            for (int32 row_number = 0; row_number < xyz_stair.X; row_number++) {
                for (int32 column_number = 0; column_number < xyz_stair.Y; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_1_top_left : stair_direction == right ? material_asset_struct.face_1_top_right : stair_direction == back ? material_asset_struct.face_1_bottom_right : material_asset_struct.face_1_bottom_left);
                        else if (column_number != xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_1_middle_left : stair_direction == right ? material_asset_struct.face_1_middle_right : stair_direction == back ? material_asset_struct.face_1_middle_right : material_asset_struct.face_1_middle_left);
                        else if (column_number == xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_1_bottom_left : stair_direction == right ? material_asset_struct.face_1_bottom_right : stair_direction == back ? material_asset_struct.face_1_top_right : material_asset_struct.face_1_top_left);
                    }
                    else if (row_number != xyz_stair.X - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_1_top_middle : stair_direction == right ? material_asset_struct.face_1_top_middle : stair_direction == back ? material_asset_struct.face_1_bottom_middle : material_asset_struct.face_1_bottom_middle);
                        else if (column_number != xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_1_middle_middle);
                        else if (column_number == xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_1_bottom_middle : stair_direction == right ? material_asset_struct.face_1_bottom_middle : stair_direction == back ? material_asset_struct.face_1_top_middle : material_asset_struct.face_1_top_middle);
                    }
                    else if (row_number == xyz_stair.X - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_1_top_right : stair_direction == right ? material_asset_struct.face_1_top_left : stair_direction == back ? material_asset_struct.face_1_bottom_left : material_asset_struct.face_1_bottom_right);
                        else if (column_number != xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_1_middle_right : stair_direction == right ? material_asset_struct.face_1_middle_left : stair_direction == back ? material_asset_struct.face_1_middle_left : material_asset_struct.face_1_middle_right);
                        else if (column_number == xyz_stair.Y - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_1_bottom_right : stair_direction == right ? material_asset_struct.face_1_bottom_left : stair_direction == back ? material_asset_struct.face_1_top_left : material_asset_struct.face_1_top_right);
                    }
                }
            }
        }
        else if (face_number == 2) {
            for (int32 row_number = 0; row_number < xyz_stair.X; row_number++) {
                for (int32 column_number = 0; stair_direction == front || stair_direction == back ? column_number < 1: column_number < xyz_stair.Z; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_2_bottom_right : stair_direction == right ? material_asset_struct.face_2_bottom_left : stair_direction == back ? material_asset_struct.face_2_bottom_right : material_asset_struct.face_2_bottom_left);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_2_middle_right : stair_direction == right ? material_asset_struct.face_2_middle_left : stair_direction == back ? material_asset_struct.face_2_middle_right : material_asset_struct.face_2_middle_left);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_2_top_right : stair_direction == right ? material_asset_struct.face_2_top_left : stair_direction == back ? material_asset_struct.face_2_top_right : material_asset_struct.face_2_top_left);
                    }
                    else if (row_number != xyz_stair.X - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_2_bottom_middle);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_2_middle_middle);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_2_top_middle);
                    }
                    else if (row_number == xyz_stair.X - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_2_bottom_left : stair_direction == right ? material_asset_struct.face_2_bottom_right : stair_direction == back ? material_asset_struct.face_2_bottom_left : material_asset_struct.face_2_bottom_right);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_2_middle_left : stair_direction == right ? material_asset_struct.face_2_middle_right : stair_direction == back ? material_asset_struct.face_2_middle_left : material_asset_struct.face_2_middle_right);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_2_top_left : stair_direction == right ? material_asset_struct.face_2_top_right : stair_direction == back ? material_asset_struct.face_2_top_left : material_asset_struct.face_2_top_right);
                    }
                }
            }
        }
        else if (face_number == 3) {
            for (int32 row_number = 0; row_number < xyz_stair.X; row_number++) {
                for (int32 column_number = 0; stair_direction == front || stair_direction == back ? column_number < 1 : column_number < xyz_stair.Z; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_3_bottom_left : stair_direction == right ? material_asset_struct.face_2_bottom_right : stair_direction == back ? material_asset_struct.face_3_bottom_left : material_asset_struct.face_3_bottom_right);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_3_middle_left : stair_direction == right ? material_asset_struct.face_3_middle_right : stair_direction == back ? material_asset_struct.face_3_middle_left : material_asset_struct.face_3_middle_right);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_3_top_left : stair_direction == right ? material_asset_struct.face_3_top_right : stair_direction == back ? material_asset_struct.face_3_top_left : material_asset_struct.face_3_top_right);
                    }
                    else if (row_number != xyz_stair.X - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_3_bottom_middle);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_3_middle_middle);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_3_top_middle);
                    }
                    else if (row_number == xyz_stair.X - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_3_bottom_right : stair_direction == right ? material_asset_struct.face_3_bottom_left : stair_direction == back ? material_asset_struct.face_3_bottom_right : material_asset_struct.face_3_bottom_left);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_3_middle_right : stair_direction == right ? material_asset_struct.face_3_middle_left : stair_direction == back ? material_asset_struct.face_3_middle_right : material_asset_struct.face_3_middle_left);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_3_top_right : stair_direction == right ? material_asset_struct.face_3_top_left : stair_direction == back ? material_asset_struct.face_3_top_right : material_asset_struct.face_3_top_left);
                    }
                }
            }
        }
        else if (face_number == 4) {
            for (int32 row_number = 0; row_number < xyz_stair.Y; row_number++) {
                for (int32 column_number = 0; stair_direction == right || stair_direction == left ? column_number < 1 : column_number < xyz_stair.Z; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_4_bottom_left : stair_direction == right ? material_asset_struct.face_4_bottom_right : stair_direction == back ? material_asset_struct.face_4_bottom_left : material_asset_struct.face_4_bottom_right);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_4_middle_left : stair_direction == right ? material_asset_struct.face_4_middle_right : stair_direction == back ? material_asset_struct.face_4_middle_left : material_asset_struct.face_4_middle_right);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_4_top_left : stair_direction == right ? material_asset_struct.face_4_top_right : stair_direction == back ? material_asset_struct.face_4_top_left : material_asset_struct.face_4_top_right);
                    }
                    else if (row_number != xyz_stair.Y - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_4_bottom_middle);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_4_middle_middle);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_4_top_middle);
                    }
                    else if (row_number == xyz_stair.Y - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_4_bottom_right : stair_direction == right ? material_asset_struct.face_4_bottom_left : stair_direction == back ? material_asset_struct.face_4_bottom_right : material_asset_struct.face_4_bottom_left);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_4_middle_right : stair_direction == right ? material_asset_struct.face_4_middle_left : stair_direction == back ? material_asset_struct.face_4_middle_right : material_asset_struct.face_4_middle_left);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_4_top_right : stair_direction == right ? material_asset_struct.face_4_top_left : stair_direction == back ? material_asset_struct.face_4_top_right : material_asset_struct.face_4_top_left);
                    }
                }
            }
        }
        else if (face_number == 5) {
            for (int32 row_number = 0; row_number < xyz_stair.Y; row_number++) {
                for (int32 column_number = 0; stair_direction == right || stair_direction == left ? column_number < 1 : column_number < xyz_stair.Z; column_number++) {
                    if (row_number == 0) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_5_bottom_right : stair_direction == right ? material_asset_struct.face_5_bottom_left : stair_direction == back ? material_asset_struct.face_5_bottom_right : material_asset_struct.face_5_bottom_left);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_5_middle_right : stair_direction == right ? material_asset_struct.face_5_middle_left : stair_direction == back ? material_asset_struct.face_5_middle_right : material_asset_struct.face_5_middle_left);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_5_top_right : stair_direction == right ? material_asset_struct.face_5_top_left : stair_direction == back ? material_asset_struct.face_5_top_right : material_asset_struct.face_5_top_left);
                    }
                    else if (row_number != xyz_stair.Y - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_5_bottom_middle);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_5_middle_middle);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, material_asset_struct.face_5_top_middle);
                    }
                    else if (row_number == xyz_stair.Y - 1) {
                        if (column_number == 0) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_5_bottom_left : stair_direction == right ? material_asset_struct.face_5_bottom_right : stair_direction == back ? material_asset_struct.face_5_bottom_left : material_asset_struct.face_5_bottom_right);
                        else if (column_number != xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_5_middle_left : stair_direction == right ? material_asset_struct.face_5_middle_right : stair_direction == back ? material_asset_struct.face_5_middle_left : material_asset_struct.face_5_middle_right);
                        else if (column_number == xyz_stair.Z - 1) stair_array[face_number].row[row_number].column[column_number]->GetStaticMeshComponent()->SetMaterial(0, stair_direction == front ? material_asset_struct.face_5_top_left : stair_direction == right ? material_asset_struct.face_5_top_right : stair_direction == back ? material_asset_struct.face_5_top_left : material_asset_struct.face_5_top_right);
                    }
                }
            }
        }
    }
}
void Agame_mode_base_level_arena::implement_hud_ending() {
    player_controller->ClientSetHUD_Implementation(hud_ending_class);
}