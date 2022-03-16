// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "projectile.h"
#include "paper_character.generated.h"

/**
 * 
 */
UCLASS()
class GAME_PROJECT_API Apaper_character : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Apaper_character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class Aprojectile> ProjectileClass;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void move_forward(float value);
	// Handels input for moving right and left.
	UFUNCTION()
		void move_right(float value);
	// Sets jump flag when key is pressed.
	UFUNCTION()
		void start_jump();
	// Clears jump flag when key is released.
	UFUNCTION()
		void stop_jump();
	// Function that handles firing projectiles.
	UFUNCTION()
		void fire();
	// FPS camera
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;
	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UPaperFlipbookComponent* paper_component;
	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;
};
