// Fill out your copyright notice in the Description page of Project Settings.

#include "paper_player.h"


// Sets default values
Apaper_player::Apaper_player()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	fps_camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(fps_camera_component != nullptr);
	fps_camera_component->SetupAttachment(GetCapsuleComponent());
	fps_camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y, camera_location_z));
	fps_camera_component->bUsePawnControlRotation = true;
	paper_component = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper"));
	check(paper_component != nullptr);
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>plane_assset(TEXT("/Game/weapons/pistol_flipbook.pistol_flipbook"));
	if (plane_assset.Succeeded()) {
		paper_component->SetFlipbook(plane_assset.Object);
		paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y, weapon_location_z));
		paper_component->SetRelativeRotation(FRotator(weapon_rotation_pitch, weapon_rotation_yaw, weapon_rotation_roll));
		paper_component->SetWorldScale3D(FVector(weapon_scale));
		paper_component->SetOnlyOwnerSee(true);
		paper_component->SetupAttachment(fps_camera_component);
		paper_component->CastShadow = false;
	}
	camera_shake_walking = LoadClass<UMatineeCameraShake>(GetWorld(), TEXT("/Script/game_project.camera_shake_walking"));
}	

// Called when the game starts or when spawned
void Apaper_player::BeginPlay()
{
	Super::BeginPlay();

	//check(GEngine != nullptr);

		
}

void Apaper_player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	slide_weapon();
	oscillate_walking();
	//if (GetCharacterMovement()->IsMovingOnGround() && GetCharacterMovement()->Velocity.Size()) matinee_camera_shake->StartMatineeCameraShake(GetWorld()->GetFirstPlayerController()->PlayerCameraManager, camera_shake_walking, 1.0f);

}

// Called to bind functionality to input
void Apaper_player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("jump", IE_Pressed, this, &Apaper_player::start_jump);
	PlayerInputComponent->BindAction("jump", IE_Released, this, &Apaper_player::stop_jump);
	PlayerInputComponent->BindAction("fire", IE_Pressed, this, &Apaper_player::fire);
	PlayerInputComponent->BindAxis("move_forward", this, &Apaper_player::move_forward);
	PlayerInputComponent->BindAxis("move_backward", this, &Apaper_player::move_backward);
	PlayerInputComponent->BindAxis("move_right", this, &Apaper_player::move_right);
	PlayerInputComponent->BindAxis("move_left", this, &Apaper_player::move_left);
	PlayerInputComponent->BindAxis("look_right", this, &Apaper_player::look_right);
	PlayerInputComponent->BindAxis("look_up", this, &Apaper_player::look_up);

}
void Apaper_player::start_jump() {
	bPressedJump = true;
}
void Apaper_player::stop_jump() {
	bPressedJump = false;
}
void Apaper_player::move_forward(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), value);
	}
	paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y + sliding_weapon_y_increment + oscillating_walking_y_increment, weapon_location_z + sliding_weapon_z_increment + oscillating_walking_z_increment));
	fps_camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y + oscillating_walking_y_increment * 20, camera_location_z + oscillating_walking_z_increment * 20));
}
void Apaper_player::move_backward(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), -value);
	}
	paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y + sliding_weapon_y_increment + oscillating_walking_y_increment, weapon_location_z + sliding_weapon_z_increment + oscillating_walking_z_increment));
	fps_camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y + oscillating_walking_y_increment * 20, camera_location_z + oscillating_walking_z_increment * 20));
}
void Apaper_player::move_right(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorRightVector(), value);
	}
	paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y + sliding_weapon_y_increment + oscillating_walking_y_increment, weapon_location_z + sliding_weapon_z_increment + oscillating_walking_z_increment));
	fps_camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y + oscillating_walking_y_increment * 20, camera_location_z + oscillating_walking_z_increment * 20));
}
void Apaper_player::move_left(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorRightVector(), -value);
	}
	paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y + sliding_weapon_y_increment + oscillating_walking_y_increment, weapon_location_z + sliding_weapon_z_increment + oscillating_walking_z_increment));
	fps_camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y + oscillating_walking_y_increment * 20, camera_location_z + oscillating_walking_z_increment * 20));
}
void Apaper_player::look_right(float value) {
	if (value != 0.0f) {
		AddControllerYawInput(value * look_right_rate * GetWorld()->GetDeltaSeconds());
	}
}
void Apaper_player::look_up(float value) {
	if (value != 0.0f) {
		AddControllerPitchInput(value * look_up_rate * GetWorld()->GetDeltaSeconds());
	}
}
void Apaper_player::slide_weapon() {
	FVector unrotated_last_vector = GetActorRotation().UnrotateVector(GetVelocity());
	if (unrotated_last_vector.X < tolerance && unrotated_last_vector.X > -tolerance) unrotated_last_vector.X = 0.0f;
	if (unrotated_last_vector.Y < tolerance && unrotated_last_vector.Y > -tolerance) unrotated_last_vector.Y = 0.0f;
	if (unrotated_last_vector.X > 0.0f) { // Beginning of the X slide.
		if (sliding_weapon_z_increment > -sliding_weapon_increment_limit) {
			sliding_weapon_z_increment = sliding_weapon_z_increment - sliding_weapon_z_increment_rate;
			if (sliding_weapon_z_increment < -sliding_weapon_increment_limit) sliding_weapon_z_increment = -sliding_weapon_increment_limit;
		}
	}
	else {
		if (sliding_weapon_z_increment < 0.0f) {
			sliding_weapon_z_increment = sliding_weapon_z_increment + sliding_weapon_z_increment_rate;
			if(sliding_weapon_z_increment > 0.0f) sliding_weapon_z_increment = 0.0f;
		}
	}
	if (unrotated_last_vector.X < 0.0f) {
		if (sliding_weapon_z_increment < sliding_weapon_increment_limit) {
			sliding_weapon_z_increment = sliding_weapon_z_increment + sliding_weapon_z_increment_rate;
			if (sliding_weapon_z_increment > sliding_weapon_increment_limit) sliding_weapon_z_increment = sliding_weapon_increment_limit;
		}
	}
	else {
		if (sliding_weapon_z_increment > 0.0f) {
			sliding_weapon_z_increment = sliding_weapon_z_increment - sliding_weapon_z_increment_rate;
			if (sliding_weapon_z_increment < 0.0f) sliding_weapon_z_increment = 0.0f;
		}
	}
	if (unrotated_last_vector.Y > 0.0f) { // Beginning of the Y slide.
		if (sliding_weapon_y_increment > -sliding_weapon_increment_limit) {
			sliding_weapon_y_increment = sliding_weapon_y_increment - sliding_weapon_y_increment_rate;
			if (sliding_weapon_y_increment < -sliding_weapon_increment_limit) sliding_weapon_y_increment = -sliding_weapon_increment_limit;
		}
	}
	else {
		if (sliding_weapon_y_increment < 0.0f) {
			sliding_weapon_y_increment = sliding_weapon_y_increment + sliding_weapon_y_increment_rate;
			if (sliding_weapon_y_increment > 0.0f) sliding_weapon_y_increment = 0.0f;
		}
	}
	if (unrotated_last_vector.Y < 0.0f) {
		if (sliding_weapon_y_increment < sliding_weapon_increment_limit) {
			sliding_weapon_y_increment = sliding_weapon_y_increment + sliding_weapon_y_increment_rate;
			if (sliding_weapon_y_increment > sliding_weapon_increment_limit) sliding_weapon_y_increment = sliding_weapon_increment_limit;
		}
	}
	else {
		if (sliding_weapon_y_increment > 0.0f) {
			sliding_weapon_y_increment = sliding_weapon_y_increment - sliding_weapon_y_increment_rate;
			if (sliding_weapon_y_increment < 0.0f) sliding_weapon_y_increment = 0.0f;
		}
	}
}
void Apaper_player::oscillate_walking() {
	if (GetCharacterMovement()->IsMovingOnGround() && GetCharacterMovement()->Velocity.Size() > 0.0f) {
		if (oscillating_walking_y_increment >= 0 && oscillating_walking_y_increment < oscillating_walking_y_increment_limit && !reached_positive_oscillating_walking_y_increment_limit && !reached_negative_oscillating_walking_y_increment_limit) { // Beginning of the Y loop.
			oscillating_walking_y_increment = oscillating_walking_y_increment + oscillating_walking_y_increment_rate;
			if (oscillating_walking_y_increment > oscillating_walking_y_increment_limit) {
				oscillating_walking_y_increment = oscillating_walking_y_increment_limit;
				reached_positive_oscillating_walking_y_increment_limit = true;
			}
		}
		if (oscillating_walking_y_increment <= oscillating_walking_y_increment_limit && reached_positive_oscillating_walking_y_increment_limit && !reached_negative_oscillating_walking_y_increment_limit) {
			oscillating_walking_y_increment = oscillating_walking_y_increment - oscillating_walking_y_increment_rate;
			if (oscillating_walking_y_increment < -oscillating_walking_y_increment_limit) {
				oscillating_walking_y_increment = -oscillating_walking_y_increment_limit;
				reached_negative_oscillating_walking_y_increment_limit = true;
			}
		}
		if (oscillating_walking_y_increment >= -oscillating_walking_y_increment_limit && reached_positive_oscillating_walking_y_increment_limit && reached_negative_oscillating_walking_y_increment_limit) {
			oscillating_walking_y_increment = oscillating_walking_y_increment + oscillating_walking_y_increment_rate;
			if (oscillating_walking_y_increment > 0) {
				reached_positive_oscillating_walking_y_increment_limit = false;
				reached_negative_oscillating_walking_y_increment_limit = false;
			}
		}
		if (oscillating_walking_z_increment >= 0 && oscillating_walking_z_increment < oscillating_walking_z_increment_limit && !reached_positive_walking_z_increment_limit && !reached_negative_walking_z_increment_limit) { // Beginning of the Z loop.
			oscillating_walking_z_increment = oscillating_walking_z_increment + oscillating_walking_y_increment_rate;
			if (oscillating_walking_z_increment > oscillating_walking_z_increment_limit) {
				oscillating_walking_z_increment = oscillating_walking_z_increment_limit;
				reached_positive_walking_z_increment_limit = true;
			}
		}
		if (oscillating_walking_z_increment <= oscillating_walking_z_increment_limit && reached_positive_walking_z_increment_limit && !reached_negative_walking_z_increment_limit) {
			oscillating_walking_z_increment = oscillating_walking_z_increment - oscillating_walking_y_increment_rate;
			if (oscillating_walking_z_increment < -oscillating_walking_z_increment_limit) {
				oscillating_walking_z_increment = -oscillating_walking_z_increment_limit;
				reached_negative_walking_z_increment_limit = true;
			}
		}
		if (oscillating_walking_z_increment >= -oscillating_walking_z_increment_limit && reached_positive_walking_z_increment_limit && reached_negative_walking_z_increment_limit) {
			oscillating_walking_z_increment = oscillating_walking_z_increment + oscillating_walking_y_increment_rate;
			if (oscillating_walking_z_increment > 0) {
				reached_positive_walking_z_increment_limit = false;
				reached_negative_walking_z_increment_limit = false;
			}
		}
	}
	else if (GetCharacterMovement()->IsMovingOnGround() && GetCharacterMovement()->Velocity.Size() == 0.0f) {
		if (oscillating_walking_y_increment > 0.0f) {
			oscillating_walking_y_increment = oscillating_walking_y_increment - oscillating_walking_y_increment_rate;
			if (oscillating_walking_y_increment < 0.0f) oscillating_walking_y_increment = 0.0f;
		}
		else if (oscillating_walking_y_increment < 0.0f) {
			oscillating_walking_y_increment = oscillating_walking_y_increment + oscillating_walking_y_increment_rate;
			if (oscillating_walking_y_increment > 0.0f) oscillating_walking_y_increment = 0.0f;
		}
		if (oscillating_walking_z_increment > 0.0f) {
			oscillating_walking_z_increment = oscillating_walking_z_increment - oscillating_walking_z_increment_rate;
			if (oscillating_walking_z_increment < 0.0f) oscillating_walking_z_increment = 0.0f;
		}
		else if (oscillating_walking_z_increment < 0.0f) {
			oscillating_walking_z_increment = oscillating_walking_z_increment + oscillating_walking_z_increment_rate;
			if (oscillating_walking_z_increment > 0.0f) oscillating_walking_z_increment = 0.0f;
		}
		if (reached_positive_oscillating_walking_y_increment_limit && reached_negative_oscillating_walking_y_increment_limit) {
			reached_positive_oscillating_walking_y_increment_limit = false;
			reached_negative_oscillating_walking_y_increment_limit = false;
		}
	}

}
void Apaper_player::fire() {
	// Attempt to fire a projectile.
	if (ProjectileClass) {
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		// Set MuzzleOffset projectiles slightly in front of the camera.
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);
		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			// Spawn the projectile at the muzzle.
			Aprojectile* projectile = World->SpawnActor<Aprojectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (projectile) {
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}