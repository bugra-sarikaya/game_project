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
#include "Math/Vector.h"
#include "MatineeCameraShake.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
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
		TSubclassOf<Aprojectile> projectile_class;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere) float look_right_rate;
	UPROPERTY(VisibleAnywhere) float look_up_rate;
	UPROPERTY(VisibleAnywhere) float tolerance;
	UPROPERTY(VisibleAnywhere) float camera_location_x;
	UPROPERTY(VisibleAnywhere) float camera_location_y;
	UPROPERTY(VisibleAnywhere) float camera_location_z;
	UPROPERTY(VisibleAnywhere) float weapon_location_x;
	UPROPERTY(VisibleAnywhere) float weapon_location_y;
	UPROPERTY(VisibleAnywhere) float weapon_location_z;
	UPROPERTY(VisibleAnywhere) float weapon_rotation_pitch;
	UPROPERTY(VisibleAnywhere) float weapon_rotation_yaw;
	UPROPERTY(VisibleAnywhere) float weapon_rotation_roll;
	UPROPERTY(VisibleAnywhere) float weapon_scale;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_increment_limit;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_x_increment;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_y_increment;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_z_increment;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_x_increment_rate;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_y_increment_rate;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_z_increment_rate;
	UPROPERTY(VisibleAnywhere) bool reached_positive_oscillating_walking_y_increment_limit;
	UPROPERTY(VisibleAnywhere) bool reached_negative_oscillating_walking_y_increment_limit;
	UPROPERTY(VisibleAnywhere) bool reached_positive_walking_z_increment_limit;
	UPROPERTY(VisibleAnywhere) bool reached_negative_walking_z_increment_limit;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_y_increment_limit;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_z_increment_limit;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_x_increment;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_y_increment;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_z_increment;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_x_increment_rate;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_y_increment_rate;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_z_increment_rate;
	UPROPERTY(VisibleAnywhere) UCameraComponent* fps_camera_component;
	UPROPERTY(VisibleAnywhere) UMatineeCameraShake* matinee_camera_shake;
	UPROPERTY(VisibleAnywhere) FVector MuzzleLocation;
	UPROPERTY(VisibleAnywhere) FRotator MuzzleRotation;
	UPROPERTY(VisibleAnywhere) FVector CameraLocation;
	UPROPERTY(VisibleAnywhere) FRotator CameraRotation;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) UPaperFlipbookComponent* paper_component;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* pistol_fire_assset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* pistol_idle_assset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector MuzzleOffset;
	UPROPERTY(EditAnywhere) TSubclassOf<UMatineeCameraShake> camera_shake_walking;
	//UPROPERTY(EditAnywhere) FTimerHandle MyHandle;
	UFUNCTION() void start_jump();
	UFUNCTION() void stop_jump();
	UFUNCTION() void move_forward(float value);
	UFUNCTION() void move_backward(float value);
	UFUNCTION()	void move_right(float value);
	UFUNCTION() void move_left(float value);
	UFUNCTION() void look_right(float value);
	UFUNCTION() void look_up(float value);
	UFUNCTION() void slide_weapon();
	UFUNCTION() void oscillate_walking();
	UFUNCTION() void fire();
	UFUNCTION() void change_flipbook(UPaperFlipbook* flipbook_asset);
	//UFUNCTION() void OnReleaseFire();
};
