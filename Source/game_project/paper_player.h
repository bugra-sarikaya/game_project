// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

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
#include "Components/AudioComponent.h"

#include "paper_player.generated.h"

class Aprojectile;
class Aenemy;
class Aplayer_state;

UCLASS()
class GAME_PROJECT_API Apaper_player : public APaperCharacter {
	GENERATED_BODY()

public:
	Apaper_player();
	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void EndPlay(EEndPlayReason::Type reason) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
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
	UFUNCTION() void quit();
	UFUNCTION() void enable_input();
	UPROPERTY() APlayerController* player_controller;
	UPROPERTY() APlayerState* player_state_pure;
	UPROPERTY() Aplayer_state* player_state;
	UPROPERTY() FRotator CameraRotation;
	UPROPERTY() FRotator MuzzleRotation;
	UPROPERTY() FTimerHandle timer_handle_chase;
	UPROPERTY() FVector CameraLocation;
	UPROPERTY() FVector MuzzleLocation;
	UPROPERTY() FVector MuzzleOffset;
	UPROPERTY() TSubclassOf<Aenemy> enemy_class;
	UPROPERTY() TSubclassOf<Aprojectile> projectile_class;
	UPROPERTY() TSubclassOf<UMatineeCameraShake> camera_shake_walking;
	UPROPERTY() UArrowComponent* arrow_component;
	UPROPERTY() UAudioComponent* audio_component_pistol_fire;
	UPROPERTY() UCameraComponent* camera_component;
	UPROPERTY() UCapsuleComponent* capsule_component;
	UPROPERTY() UCharacterMovementComponent* movement_component;
	UPROPERTY() UMatineeCameraShake* matinee_camera_shake;
	UPROPERTY() UPaperFlipbook* pistol_fire_asset;
	UPROPERTY() UPaperFlipbook* pistol_idle_asset;
	UPROPERTY() UPaperFlipbookComponent* paper_component;
	UPROPERTY() USoundBase* sound_asset_pistol_fire;
	UPROPERTY() UWorld* world;
	UPROPERTY() int32 score = 0;
	UPROPERTY() float camera_location_x = 0.0f;
	UPROPERTY() float camera_location_y = 0.0f;
	UPROPERTY() float camera_location_z = 65.0f;
	UPROPERTY() float capsule_half_height = 88.0f;;
	UPROPERTY() float capsule_radius = 34.0f;
	UPROPERTY() float delay_enabling_inputs = 0.01f;
	UPROPERTY() float fire_rate_pistol = 1.15f;
	UPROPERTY() float health = 100.0f;
	UPROPERTY() float look_right_rate = 45.f;
	UPROPERTY() float look_up_rate = 45.f;
	UPROPERTY() float oscillating_walking_x_increment = 0.0f;
	UPROPERTY() float oscillating_walking_y_increment = 0.0f;
	UPROPERTY() float oscillating_walking_z_increment = 0.0f;
	UPROPERTY() float oscillating_walking_y_increment_limit = 0.6f;
	UPROPERTY() float oscillating_walking_z_increment_limit = 0.6f;
	UPROPERTY() float oscillating_walking_x_increment_rate = 0.05f;
	UPROPERTY() float oscillating_walking_y_increment_rate = 0.05f;
	UPROPERTY() float oscillating_walking_z_increment_rate = 0.05f;
	UPROPERTY() float sliding_weapon_increment_limit = 0.2f;
	UPROPERTY() float sliding_weapon_x_increment = 0.0f;
	UPROPERTY() float sliding_weapon_y_increment = 0.0f;
	UPROPERTY() float sliding_weapon_z_increment = 0.0f;
	UPROPERTY() float sliding_weapon_x_increment_rate = 0.05f;
	UPROPERTY() float sliding_weapon_y_increment_rate = 0.05f;
	UPROPERTY() float sliding_weapon_z_increment_rate = 0.05f;
	UPROPERTY() float time_end;
	UPROPERTY() float time_start;
	UPROPERTY() float tolerance = 0.010000f;
	UPROPERTY() float volume_multiplier_pistol_fire = 0.3f;
	UPROPERTY() float weapon_location_x = 20.0f;
	UPROPERTY() float weapon_location_y = 7.5f;
	UPROPERTY() float weapon_location_z = -6.9f;
	UPROPERTY() float weapon_rotation_pitch = 0.0f;
	UPROPERTY() float weapon_rotation_roll = 0.0f;
	UPROPERTY() float weapon_rotation_yaw = 90.0f;
	UPROPERTY() float weapon_scale = 0.05f;
	UPROPERTY() bool reached_negative_oscillating_walking_y_increment_limit = false;
	UPROPERTY() bool reached_negative_walking_z_increment_limit = false;
	UPROPERTY() bool reached_positive_oscillating_walking_y_increment_limit = false;
	UPROPERTY() bool reached_positive_walking_z_increment_limit = false;
};
