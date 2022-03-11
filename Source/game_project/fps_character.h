// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "fps_character.generated.h"


UCLASS()
class GAME_PROJECT_API Afps_character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Afps_character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	// FPS camera
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;
	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;
};
