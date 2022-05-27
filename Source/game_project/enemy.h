// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Components/AudioComponent.h"
#include "AudioDevice.h"

#include "enemy.generated.h"

class Apaper_player;
class Aplayer_state;

UCLASS()
class GAME_PROJECT_API Aenemy : public APaperCharacter
{
	GENERATED_BODY()
public:
	Aenemy();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;
	UFUNCTION() void change_flipbook(UPaperFlipbookComponent* flipbook_component, UPaperFlipbook* flipbook_asset, bool looping_status, float new_play_rate);
	UFUNCTION() void on_sight_sensed(const TArray<AActor*>& updated_actors);
	UFUNCTION() void on_begin_overlap(UPrimitiveComponent* overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index, bool b_from_sweep, const FHitResult& hit);
	UFUNCTION() void on_end_overlap(UPrimitiveComponent* overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index);
	UFUNCTION() void tick_AI(float delta_time);
	UFUNCTION() void attack(Apaper_player* attacked_player, float damage_amount);
	UPROPERTY() UWorld* world;
	UPROPERTY() FRotator enemy_rotation;
	UPROPERTY() FVector base_location;
	UPROPERTY() FVector current_velocity;
	UPROPERTY() FVector temp_velocity;
	UPROPERTY() FVector new_location;
	UPROPERTY() FVector attenuation_shape_extents_audio_angry = FVector(900.0f, 0.0f, 0.0f);
	UPROPERTY() FVector attenuation_shape_extents_audio_growl = FVector(900.0f, 0.0f, 0.0f);
	UPROPERTY() FVector attenuation_shape_extents_audio_claw_strike = FVector(900.0f, 0.0f, 0.0f);
	UPROPERTY() UPaperFlipbookComponent* paper_component;
	UPROPERTY() UCapsuleComponent* capsule_component;
	UPROPERTY() USphereComponent* attack_sphere_component;
	UPROPERTY() UArrowComponent* arrow_component;
	UPROPERTY() UCharacterMovementComponent* movement_component;
	UPROPERTY() UAIPerceptionComponent* AI_perception_component;
	UPROPERTY() UAISenseConfig_Sight* AI_sense_sight_config;
	UPROPERTY() UAISenseConfig_Sight* AI_sense_attack_sight_config;
	UPROPERTY() AAIController* AI_controller;
	UPROPERTY() UPaperFlipbook* enemy_idle_asset;
	UPROPERTY() UPaperFlipbook* enemy_ready_asset;
	UPROPERTY() UPaperFlipbook* enemy_chase_asset;
	UPROPERTY() UPaperFlipbook* enemy_attack_asset;
	UPROPERTY() UPaperFlipbook* enemy_calm_asset;
	UPROPERTY() UPaperFlipbook* enemy_die_asset;
	UPROPERTY() UPaperFlipbook* enemy_dead_asset;
	UPROPERTY() USoundBase* sound_asset_angry;
	UPROPERTY() USoundBase* sound_asset_growl;
	UPROPERTY() USoundBase* sound_asset_claw_strike;
	UPROPERTY() UAudioComponent* audio_component_angry;
	UPROPERTY() UAudioComponent* audio_component_growl;
	UPROPERTY() UAudioComponent* audio_component_claw_strike;
	UPROPERTY() Apaper_player* paper_player;
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() APlayerState* player_state_pure;
	UPROPERTY() Aplayer_state* player_state;
	UPROPERTY() TSubclassOf<Apaper_player> paper_player_class;
	UPROPERTY() int32 death_score = 10;
	UPROPERTY() float movement_speed = 650.0f; //375.0f;
	UPROPERTY() float AI_sense_sight_radius_value = 2250.0f; //1250.0f;
	UPROPERTY() float AI_sense_sight_lose_sight_radius_value = 2280.0f; //1280.0f;
	UPROPERTY() float AI_sense_sight_peripheral_vision_angle_degrees_value = 360.0f;
	UPROPERTY() float distance_squared = BIG_NUMBER;
	UPROPERTY() float capsule_radius = 105.0f;
	UPROPERTY() float capsule_half_height = 130.0f;
	UPROPERTY() float paper_location_x = 0.0f;
	UPROPERTY() float paper_location_y = 0.0f;
	UPROPERTY() float paper_location_z = 0.0f;
	UPROPERTY() float paper_scale = 0.6f;
	UPROPERTY() float play_rate;
	UPROPERTY() float health = 100.0;
	UPROPERTY() float damage_value = 15.0f;
	UPROPERTY() float volume_multiplier_value_angry_sound = 0.5f;
	UPROPERTY() float volume_multiplier_value_growl_sound = 0.5f;
	UPROPERTY() float volume_multiplier_value_claw_miss_sound = 0.5f;
	UPROPERTY() float volume_multiplier_value_claw_strike_sound = 0.5f;
	UPROPERTY() float pitch_multiplier_value_audio_angry = 1.0f;
	UPROPERTY() float pitch_multiplier_value_audio_growl = 1.0f;
	UPROPERTY() float pitch_multiplier_value_audio_claw_strike = 1.0f;
	UPROPERTY() float attenuation_falloff_distance_audio_angry = 3000.0f;
	UPROPERTY() float attenuation_falloff_distance_audio_growl = 3000.0f;
	UPROPERTY() float attenuation_falloff_distance_audio_claw_strike = 3000.0f;
	UPROPERTY() float attenuation_binaural_radius_audio_angry = 0.0f;
	UPROPERTY() float attenuation_binaural_radius_audio_growl = 0.0f;
	UPROPERTY() float attenuation_binaural_radius_audio_claw_strike = 0.0f;
	UPROPERTY() float attenuation_omni_radius_audio_angry = 0.0f;
	UPROPERTY() float attenuation_omni_radius_audio_growl = 0.0f;
	UPROPERTY() float attenuation_omni_radius_audio_claw_strike = 0.0f;
	UPROPERTY() float attenuation_stereo_spread_audio_angry = 200.0f;
	UPROPERTY() float attenuation_stereo_spread_audio_growl = 200.0f;
	UPROPERTY() float attenuation_stereo_spread_audio_claw_strike = 200.0f;
	UPROPERTY() float attenuation_reverb_wet_level_min_audio_angry = 0.3f;
	UPROPERTY() float attenuation_reverb_wet_level_min_audio_growl = 0.3f;
	UPROPERTY() float attenuation_reverb_wet_level_min_audio_claw_strike = 0.3f;
	UPROPERTY() float attenuation_reverb_wet_level_max_audio_angry = 0.95f;
	UPROPERTY() float attenuation_reverb_wet_level_max_audio_growl = 0.95f;
	UPROPERTY() float attenuation_reverb_wet_level_max_audio_claw_strike = 0.95f;
	UPROPERTY() float attenuation_reverb_distance_min_audio_angry = 400.0f;
	UPROPERTY() float attenuation_reverb_distance_min_audio_growl = 400.0f;
	UPROPERTY() float attenuation_reverb_distance_min_audio_claw_strike = 400.0f;
	UPROPERTY() float attenuation_reverb_distance_max_audio_angry = 4000.0f;
	UPROPERTY() float attenuation_reverb_distance_max_audio_growl = 4000.0f;
	UPROPERTY() float attenuation_reverb_distance_max_audio_claw_strike = 4000.0f;
	UPROPERTY() bool back_to_base_location;
	UPROPERTY() bool did_attack = false;
	UPROPERTY() bool dead = false;
	UPROPERTY() bool attenuation_override_attenuation_audio_angry = true;
	UPROPERTY() bool attenuation_override_attenuation_audio_growl = true;
	UPROPERTY() bool attenuation_override_attenuation_audio_claw_strike = true;
	UPROPERTY() bool attenuation_attenuate_audio_angry = true;
	UPROPERTY() bool attenuation_attenuate_audio_growl = true;
	UPROPERTY() bool attenuation_attenuate_audio_claw_strike = true;
	UPROPERTY() bool attenuation_spatialize_audio_angry = true;
	UPROPERTY() bool attenuation_spatialize_audio_growl = true;
	UPROPERTY() bool attenuation_spatialize_audio_claw_strike = true;
	UPROPERTY() bool attenuation_enable_reverb_send_audio_angry = true;
	UPROPERTY() bool attenuation_enable_reverb_send_audio_growl = true;
	UPROPERTY() bool attenuation_enable_reverb_send_audio_claw_strike = true;
	UPROPERTY() EAttenuationDistanceModel attenuation_distance_algorithm_audio_angry = EAttenuationDistanceModel::Linear;
	UPROPERTY() EAttenuationDistanceModel attenuation_distance_algorithm_audio_growl = EAttenuationDistanceModel::Linear;
	UPROPERTY() EAttenuationDistanceModel attenuation_distance_algorithm_audio_claw_strike = EAttenuationDistanceModel::Linear;
	UPROPERTY() EReverbSendMethod attenuation_reverb_send_method_audio_angry = EReverbSendMethod::Linear;
	UPROPERTY() EReverbSendMethod attenuation_reverb_send_method_audio_growl = EReverbSendMethod::Linear;
	UPROPERTY() EReverbSendMethod attenuation_reverb_send_method_audio_claw_strike = EReverbSendMethod::Linear;
};