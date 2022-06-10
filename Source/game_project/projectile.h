// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

#include "projectile.generated.h"

class Aenemy;

UCLASS()
class GAME_PROJECT_API Aprojectile : public AActor {
	GENERATED_BODY()
public:	
	Aprojectile();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UFUNCTION() void FireInDirection(const FVector& ShootDirection);
	UFUNCTION()	void on_hit(UPrimitiveComponent* hit_component, AActor* other_actor, UPrimitiveComponent* other_component, FVector normal_impulse, const FHitResult& hit);
	UFUNCTION() void deal_damage(Aenemy* attack_enemy, float damage_amount);
	UPROPERTY() Aenemy* enemy;
	UPROPERTY() UPaperFlipbook* projectile_idle_asset;
	UPROPERTY() UPaperFlipbookComponent* paper_component;
	UPROPERTY() UProjectileMovementComponent* projectile_movement_component;
	UPROPERTY() USphereComponent* collision_component;
	UPROPERTY() float collision_sphere_radius = 10.0f;
	UPROPERTY() float damage_value = 25.0f;
	UPROPERTY() float gravity_scale = 0.0f;
	UPROPERTY() float initial_speed = 4500.0f;
	UPROPERTY() float life_span = 4.0f;
	UPROPERTY() float max_speed = 4500.0f;
	UPROPERTY() float world_scale = 0.6f;
	UPROPERTY() bool bouncing = false;
	UPROPERTY() bool following_velocity = true;
};
