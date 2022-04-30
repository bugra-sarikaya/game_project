// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "enemy.generated.h"

/**
 * 
 */
UCLASS()
class GAME_PROJECT_API Aenemy : public APaperCharacter
{
	GENERATED_BODY()
public:
	Aenemy();
	virtual void Tick(float delta_time) override;
	UPROPERTY(VisibleAnywhere) float capsule_radius = 80.0f;
	UPROPERTY(VisibleAnywhere) float capsule_half_height = 130.0f;
	UPROPERTY(VisibleAnywhere) float paper_scale = 0.6f;
	UPROPERTY(VisibleAnywhere) float play_rate;
	UPROPERTY() float health = 100.0;
	UPROPERTY() float damage_value = 50.0f;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbookComponent* paper_component;
	UPROPERTY(VisibleDefaultsOnly) UCapsuleComponent* capsule_component;
	UPROPERTY(VisibleDefaultsOnly) UArrowComponent* arrow_component;
	UPROPERTY(VisibleDefaultsOnly) UCharacterMovementComponent* movement_component;
	UPROPERTY(VisibleDefaultsOnly) class UAIPerceptionComponent* AI_perception_component;
	UPROPERTY(VisibleDefaultsOnly) class UAISenseConfig_Sight* AI_sense_sight_config;
	UPROPERTY(VisibleAnywhere) FRotator enemy_rotation;
	UPROPERTY(VisibleAnywhere) FVector base_location;
	UPROPERTY(VisibleAnywhere) FVector current_velocity;
	UPROPERTY(VisibleAnywhere) float movement_speed = 375.0f;
	UPROPERTY(VisibleAnywhere) bool back_to_base_location;
	UPROPERTY(VisibleAnywhere) FVector new_location;
	UPROPERTY(VisibleAnywhere) float distance_squared = BIG_NUMBER;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_idle_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_ready_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_chase_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_attack_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_calm_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_die_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_dead_asset;
	UFUNCTION() void on_overlap(UPrimitiveComponent* hit_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index, bool b_from_sweep, const FHitResult& hit);
	UFUNCTION()	void on_hit(UPrimitiveComponent* hit_component, AActor* other_actor, UPrimitiveComponent* other_component, FVector normal_impulse, const FHitResult& hit);
	UFUNCTION() void on_sensed(const TArray<AActor*>& uppdated_actors);
	UFUNCTION() void deal_damage(float damage_amount);

protected:
	virtual void BeginPlay() override;

};
