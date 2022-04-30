// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Math/Vector.h"
#include "MatineeCameraShake.h"
#include "TimerManager.h"
#include "projectile.h"
#include "paper_player.generated.h"

UCLASS()
class GAME_PROJECT_API Apaper_player : public APaperCharacter
{
	GENERATED_BODY()

public:
	Apaper_player();
	virtual void Tick(float delta_time) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere) float capsule_radius = 34.0f;
	UPROPERTY(VisibleAnywhere) float capsule_half_height = 88.0f;;
	UPROPERTY(VisibleAnywhere) float look_right_rate = 45.f;
	UPROPERTY(VisibleAnywhere) float look_up_rate = 45.f;
	UPROPERTY(VisibleAnywhere) float tolerance = 0.010000f;
	UPROPERTY(VisibleAnywhere) float camera_location_x = 0.0f;
	UPROPERTY(VisibleAnywhere) float camera_location_y = 0.0f;
	UPROPERTY(VisibleAnywhere) float camera_location_z = 65.0f;
	UPROPERTY(VisibleAnywhere) float weapon_location_x = 20.0f;
	UPROPERTY(VisibleAnywhere) float weapon_location_y = 7.5f;
	UPROPERTY(VisibleAnywhere) float weapon_location_z = -6.9f;
	UPROPERTY(VisibleAnywhere) float weapon_rotation_pitch = 0.0f;
	UPROPERTY(VisibleAnywhere) float weapon_rotation_yaw = 90.0f;
	UPROPERTY(VisibleAnywhere) float weapon_rotation_roll = 0.0f;
	UPROPERTY(VisibleAnywhere) float weapon_scale = 0.05f;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_increment_limit = 0.2f;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_x_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_y_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_z_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_x_increment_rate = 0.05f;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_y_increment_rate = 0.05f;
	UPROPERTY(VisibleAnywhere) float sliding_weapon_z_increment_rate = 0.05f;
	UPROPERTY(VisibleAnywhere) bool reached_positive_oscillating_walking_y_increment_limit = false;
	UPROPERTY(VisibleAnywhere) bool reached_negative_oscillating_walking_y_increment_limit = false;
	UPROPERTY(VisibleAnywhere) bool reached_positive_walking_z_increment_limit = false;
	UPROPERTY(VisibleAnywhere) bool reached_negative_walking_z_increment_limit = false;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_y_increment_limit = 0.6f;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_z_increment_limit = 0.6f;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_x_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_y_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_z_increment = 0.0f;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_x_increment_rate = 0.05f;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_y_increment_rate = 0.05f;
	UPROPERTY(VisibleAnywhere) float oscillating_walking_z_increment_rate = 0.05f;
	UPROPERTY() float health = 100.0f;
	UPROPERTY(VisibleAnywhere) UCameraComponent* camera_component;
	UPROPERTY(VisibleDefaultsOnly) UCapsuleComponent* capsule_component;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbookComponent* paper_component;
	UPROPERTY(VisibleDefaultsOnly) UCharacterMovementComponent* movement_component;
	UPROPERTY(VisibleDefaultsOnly) UArrowComponent* arrow_component;
	UPROPERTY(VisibleAnywhere) UMatineeCameraShake* matinee_camera_shake;
	UPROPERTY(VisibleAnywhere) FVector MuzzleLocation;
	UPROPERTY(VisibleAnywhere) FRotator MuzzleRotation;
	UPROPERTY(VisibleAnywhere) FVector CameraLocation;
	UPROPERTY(VisibleAnywhere) FRotator CameraRotation;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* pistol_fire_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* pistol_idle_asset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector MuzzleOffset;
	UPROPERTY(EditAnywhere) TSubclassOf<UMatineeCameraShake> camera_shake_walking;
	UPROPERTY() TSubclassOf<Aprojectile> projectile_class;
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
	UFUNCTION() void deal_damage(float damage_amount);
protected:
	virtual void BeginPlay() override;
};
