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
#include "Sound/SoundCue.h"

#include "enemy.generated.h"

class Apaper_player;
class Aplayer_state;

UCLASS()
class GAME_PROJECT_API Aenemy : public APaperCharacter {
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
	UFUNCTION() void attack(Apaper_player* attacked_player, float damage_amount);
	UFUNCTION() void chase(AActor* chased_actor);
	UFUNCTION() void destroy_component(USceneComponent* component);
	UFUNCTION() void play_sound_pain();
	UPROPERTY() AActor* sensed_actor;
	UPROPERTY() AAIController* AI_controller;
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() APlayerState* player_state_pure;
	UPROPERTY() Aplayer_state* player_state;
	UPROPERTY() Apaper_player* paper_player;
	UPROPERTY() FRotator enemy_rotation;
	UPROPERTY() FTimerHandle timer_handle_chase;
	UPROPERTY() FTimerHandle timer_handle_idle;
	UPROPERTY() FTimerHandle timer_handle_destroy_audio_component_die;
	UPROPERTY() TSubclassOf<Apaper_player> paper_player_class;
	UPROPERTY() UWorld* world;
	UPROPERTY() UAIPerceptionComponent* AI_perception_component;
	UPROPERTY() UAISenseConfig_Sight* AI_sense_sight_config;
	UPROPERTY() UAISenseConfig_Sight* AI_sense_attack_sight_config;
	UPROPERTY() UArrowComponent* arrow_component;
	UPROPERTY() UAudioComponent* audio_component_idle;
	UPROPERTY() UAudioComponent* audio_component_ready;
	UPROPERTY() UAudioComponent* audio_component_chase;
	UPROPERTY() UAudioComponent* audio_component_pain;
	UPROPERTY() UAudioComponent* audio_component_claw_strike;
	UPROPERTY() UAudioComponent* audio_component_die;
	UPROPERTY() UCapsuleComponent* capsule_component;
	UPROPERTY() UCharacterMovementComponent* movement_component;
	UPROPERTY() UPaperFlipbook* enemy_idle_asset;
	UPROPERTY() UPaperFlipbook* enemy_ready_asset;
	UPROPERTY() UPaperFlipbook* enemy_chase_asset;
	UPROPERTY() UPaperFlipbook* enemy_attack_asset;
	UPROPERTY() UPaperFlipbook* enemy_calm_asset;
	UPROPERTY() UPaperFlipbook* enemy_die_asset;
	UPROPERTY() UPaperFlipbook* enemy_dead_asset;
	UPROPERTY() UPaperFlipbookComponent* paper_component;
	UPROPERTY() USoundCue* sound_cue_asset_idle;
	UPROPERTY() USoundCue* sound_cue_asset_ready;
	UPROPERTY() USoundCue* sound_cue_asset_chase;
	UPROPERTY() USoundCue* sound_cue_asset_pain;
	UPROPERTY() USoundCue* sound_cue_asset_claw_strike;
	UPROPERTY() USoundCue* sound_cue_asset_die;
	UPROPERTY() USphereComponent* attack_sphere_component;
	UPROPERTY() int32 death_score = 10;
	UPROPERTY() float movement_speed = 630.0f; // 600;
	UPROPERTY() float AI_sense_sight_radius_value = 4250.0f; //1250.0f;
	UPROPERTY() float AI_sense_sight_lose_sight_radius_value = 4280.0f; //1280.0f;
	UPROPERTY() float AI_sense_sight_peripheral_vision_angle_degrees_value = 360.0f;
	UPROPERTY() float capsule_radius = 105.0f;
	UPROPERTY() float capsule_half_height = 130.0f;
	UPROPERTY() float paper_location_x = 0.0f;
	UPROPERTY() float paper_location_y = 0.0f;
	UPROPERTY() float paper_location_z = 0.0f;
	UPROPERTY() float paper_scale = 0.6f;
	UPROPERTY() float play_rate;
	UPROPERTY() float health = 100.0;
	UPROPERTY() float damage_value = 5.0f;
	UPROPERTY() float volume_multiplier_idle = 0.3f;
	UPROPERTY() float volume_multiplier_ready = 0.48f;
	UPROPERTY() float volume_multiplier_chase = 0.19f;
	UPROPERTY() float volume_multiplier_pain = 0.45f;
	UPROPERTY() float volume_multiplier_claw_strike = 0.5f;
	UPROPERTY() float volume_multiplier_die = 1.6f;
	UPROPERTY() bool back_to_base_location;
	UPROPERTY() bool did_attack = false;
	UPROPERTY() bool dead = false;
	UPROPERTY() bool sensed = false;
	FTimerDelegate timer_delegate_chase;
	FTimerDelegate timer_delegate_idle;
	FTimerDelegate timer_delegate_destroy_audio_component_die;
};