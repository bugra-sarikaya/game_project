// Fill out your copyright notice in the Description page of Project Settings.

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
#include "enemy.generated.h"

class Apaper_player;
UCLASS()
class GAME_PROJECT_API Aenemy : public APaperCharacter
{
	GENERATED_BODY()
public:
	Aenemy();
	virtual void Tick(float delta_time) override;
	UPROPERTY(VisibleAnywhere) float capsule_radius = 105.0f;
	UPROPERTY(VisibleAnywhere) float capsule_half_height = 130.0f;
	UPROPERTY(VisibleAnywhere) float paper_location_x = 0.0f;
	UPROPERTY(VisibleAnywhere) float paper_location_y = 0.0f;
	UPROPERTY(VisibleAnywhere) float paper_location_z = 0.0f;
	UPROPERTY(VisibleAnywhere) float paper_scale = 0.6f;
	UPROPERTY(VisibleAnywhere) float play_rate;
	UPROPERTY() float health = 100.0;
	UPROPERTY() float damage_value = 15.0f;
	UPROPERTY(VisibleAnywhere) FRotator enemy_rotation;
	UPROPERTY(VisibleAnywhere) FVector base_location;
	UPROPERTY(VisibleAnywhere) FVector current_velocity;
	UPROPERTY(VisibleAnywhere) FVector temp_velocity;
	UPROPERTY(VisibleAnywhere) float movement_speed = 375.0f;
	UPROPERTY(VisibleAnywhere) bool back_to_base_location;
	UPROPERTY(VisibleAnywhere) FVector new_location;
	UPROPERTY(VisibleAnywhere) float distance_squared = BIG_NUMBER;
	UPROPERTY() bool did_attack = false;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbookComponent* paper_component;
	UPROPERTY(VisibleDefaultsOnly) UCapsuleComponent* capsule_component;
	UPROPERTY(VisibleDefaultsOnly) USphereComponent* attack_sphere_component;
	UPROPERTY(VisibleDefaultsOnly) UArrowComponent* arrow_component;
	UPROPERTY(VisibleDefaultsOnly) UCharacterMovementComponent* movement_component;
	UPROPERTY(VisibleDefaultsOnly) UAIPerceptionComponent* AI_perception_component;
	UPROPERTY(VisibleDefaultsOnly) UAISenseConfig_Sight* AI_sense_sight_config;
	UPROPERTY(VisibleDefaultsOnly) UAISenseConfig_Sight* AI_sense_attack_sight_config;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_idle_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_ready_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_chase_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_attack_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_calm_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_die_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_dead_asset;
	UPROPERTY() Apaper_player* paper_player;
	UFUNCTION() void change_flipbook(UPaperFlipbookComponent* flipbook_component, UPaperFlipbook* flipbook_asset, bool looping_status, float new_play_rate);
	UFUNCTION() void on_sight_sensed(const TArray<AActor*>& updated_actors);
	UFUNCTION() void on_begin_overlap(UPrimitiveComponent* overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index, bool b_from_sweep, const FHitResult& hit);
	UFUNCTION() void on_end_overlap(UPrimitiveComponent* overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index);
	UFUNCTION() void tick_AI(float delta_time);
	UFUNCTION() void attack(Apaper_player* attacked_player, float damage_amount);
protected:
	virtual void BeginPlay() override;

};
