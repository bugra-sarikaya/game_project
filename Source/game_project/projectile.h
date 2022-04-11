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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function that is called the projectile hits something.
	UFUNCTION()
		void on_hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	// Sphere collision component.
	UPROPERTY(VisibleAnywhere) float collision_sphere_radius;
	UPROPERTY(VisibleAnywhere) float initial_speed;
	UPROPERTY(VisibleAnywhere) float max_speed;
	UPROPERTY(VisibleAnywhere) bool following_velocity;
	UPROPERTY(VisibleAnywhere) float world_scale;
	UPROPERTY(VisibleAnywhere) float life_span;
	UPROPERTY(VisibleAnywhere) bool bouncing;
	UPROPERTY(VisibleAnywhere) float gravity_scale;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;
	// Projectile mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent* ProjectileMeshComponent;
	// Projectile material
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
		UMaterialInstanceDynamic* ProjectileMaterialInstance;
	// Function that initializes the projectile's velocity in the shoot direction.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) UPaperFlipbookComponent* paper_component;
	UFUNCTION()void FireInDirection(const FVector& ShootDirection);
};
