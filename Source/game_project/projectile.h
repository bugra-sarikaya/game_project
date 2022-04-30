// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "projectile.generated.h"

UCLASS()
class GAME_PROJECT_API Aprojectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aprojectile();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere) float collision_sphere_radius = 10.0f;
	UPROPERTY(VisibleAnywhere) float initial_speed = 4000.0f;
	UPROPERTY(VisibleAnywhere) float max_speed = 4000.0f;
	UPROPERTY(VisibleAnywhere) bool following_velocity = true;
	UPROPERTY(VisibleAnywhere) float world_scale = 0.6f;
	UPROPERTY(VisibleAnywhere) float life_span = 3.0f;
	UPROPERTY(VisibleAnywhere) bool bouncing = false;
	UPROPERTY(VisibleAnywhere) float gravity_scale = 0.0f;
	UPROPERTY(VisibleAnywhere) float damage_value = 50.0f;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile) USphereComponent* collision_component;
	UPROPERTY(VisibleAnywhere, Category = Movement) UProjectileMovementComponent* projectile_movement_component;
	UPROPERTY() UPaperFlipbookComponent* paper_component;
	UPROPERTY() UPaperFlipbook* projectile_idle_asset;
	UFUNCTION() void FireInDirection(const FVector& ShootDirection);
	UFUNCTION() void on_overlap(UPrimitiveComponent* hit_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_indecx, bool b_from_sweep, const FHitResult& hit);
	UFUNCTION()	void on_hit(UPrimitiveComponent* hit_component, AActor* other_actor, UPrimitiveComponent* other_component, FVector normal_impulse, const FHitResult& hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
