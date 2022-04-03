// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperSpriteComponent.h"
#include "projectile.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "paper_player.generated.h"

UCLASS()
class GAME_PROJECT_API Apaper_player : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Apaper_player();

protected:
	virtual void BeginPlay() override;
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class Aprojectile> ProjectileClass;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() void start_jump();
	UFUNCTION() void stop_jump();
	UFUNCTION() void fire();
	UFUNCTION() void move_forward(float value);
	UFUNCTION() void move_backward(float value);
	UFUNCTION()	void move_right(float value);
	UFUNCTION() void move_left(float value);
	UFUNCTION() void look_right(float value);
	UFUNCTION() void look_up(float value);
	UPROPERTY(VisibleAnywhere) float look_right_rate = 45.f;
	UPROPERTY(VisibleAnywhere) float look_up_rate = 45.f;
	UPROPERTY(VisibleAnywhere) float location_x = 20.0f;
	UPROPERTY(VisibleAnywhere) float location_y = 6.0f;
	UPROPERTY(VisibleAnywhere) float location_z = -7.5f;
	UPROPERTY(VisibleAnywhere) float increment_limit = 0.5f;
	UPROPERTY(VisibleAnywhere) float location_x_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float location_y_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float location_z_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float location_x_increment_rate = 0.05f;
	UPROPERTY(VisibleAnywhere) float location_y_increment_rate = 0.05f;
	UPROPERTY(VisibleAnywhere) float location_z_increment_rate = 0.05f;
	UPROPERTY(VisibleAnywhere) float rotation_pitch = 0.0f;
	UPROPERTY(VisibleAnywhere) float rotation_yaw = 90.0f;
	UPROPERTY(VisibleAnywhere) float rotation_roll = 0.0f;
	UPROPERTY(VisibleAnywhere) float scale = 0.007f;
	UPROPERTY(VisibleAnywhere) UCameraComponent* FPSCameraComponent;
	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UPaperFlipbookComponent* paper_component;
	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;
};
