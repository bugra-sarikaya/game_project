// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "paper_player.h"
#include "enemy.h"
#include "projectile.h"
#include "game_mode_base_level_arena.h"
#include "player_state.h"

Apaper_player::Apaper_player(){
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = capsule_component = GetCapsuleComponent();
	capsule_component->InitCapsuleSize(capsule_radius, capsule_half_height);
	camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	check(camera_component != nullptr);
	camera_component->SetupAttachment(RootComponent);
	camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y, camera_location_z));
	camera_component->bUsePawnControlRotation = true;
	paper_component = (UPaperFlipbookComponent*)GetComponentByClass(UPaperFlipbookComponent::StaticClass());
	check(paper_component != nullptr);
	world = GetWorld();
	pistol_idle_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/weapons/pistol_idle_v1.pistol_idle_v1"));
	paper_component->SetupAttachment(camera_component);
	paper_component->SetFlipbook(pistol_idle_asset);
	paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y, weapon_location_z));
	paper_component->SetRelativeRotation(FRotator(weapon_rotation_pitch, weapon_rotation_yaw, weapon_rotation_roll));
	paper_component->SetWorldScale3D(FVector(weapon_scale));
	paper_component->SetOnlyOwnerSee(true);
	paper_component->CastShadow = false;
	projectile_class = LoadClass<Aprojectile>(world, TEXT("/Script/game_project.projectile"));
	enemy_class = LoadClass<Aenemy>(world, TEXT("/Script/game_project.enemy"));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(GetMovementComponent()->GetName()));

	pistol_fire_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/weapons/pistol_fire_v1.pistol_fire_v1"));

}	

// Called when the game starts or when spawned
void Apaper_player::BeginPlay()
{
	Super::BeginPlay();
	//FActorSpawnParameters enemy_spawn_parameters;
	//enemy_spawn_parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	//GetWorld()->SpawnActor<Aenemy>(enemy_class, FVector(1540.f, -450.0f, 150.0f), FRotator(0), enemy_spawn_parameters);
	time_start = world->GetTimeSeconds();
	player_state_pure = GetPlayerState();
	player_state = Cast<Aplayer_state>(player_state_pure);
	if (player_state) player_state->set_player_time_start(time_start);
}

void Apaper_player::Tick(float delta_time){
	Super::Tick(delta_time);
	time_end = world->GetTimeSeconds();
	if (player_state) {
		player_state->set_player_time_end(time_end);
		player_state->set_player_health(health);
	}
	slide_weapon();
	oscillate_walking();
	if (paper_component->GetFlipbook() == pistol_fire_asset && !paper_component->IsPlaying()) {
		paper_component->SetFlipbook(pistol_idle_asset);
		paper_component->SetLooping(true);
		paper_component->Play();
	}
	const APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller->IsInputKeyDown(FKey(TEXT("LeftMouseButton")))) fire();
	if (health <= 0.0f) Destroy();
}

// Called to bind functionality to input
void Apaper_player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("jump", IE_Pressed, this, &Apaper_player::start_jump);
	PlayerInputComponent->BindAction("jump", IE_Released, this, &Apaper_player::stop_jump);
	PlayerInputComponent->BindAction("fire", IE_Pressed, this, &Apaper_player::fire);
	//PlayerInputComponent->BindAction("fire", IE_Released, this, &Apaper_player::OnReleaseFire);
	PlayerInputComponent->BindAxis("move_forward", this, &Apaper_player::move_forward);
	PlayerInputComponent->BindAxis("move_backward", this, &Apaper_player::move_backward);
	PlayerInputComponent->BindAxis("move_right", this, &Apaper_player::move_right);
	PlayerInputComponent->BindAxis("move_left", this, &Apaper_player::move_left);
	PlayerInputComponent->BindAxis("look_right", this, &Apaper_player::look_right);
	PlayerInputComponent->BindAxis("look_up", this, &Apaper_player::look_up);

}
void Apaper_player::EndPlay(EEndPlayReason::Type reason) {
	Super::EndPlay(reason);
	if (reason == EEndPlayReason::Destroyed) {
		AGameModeBase* game_mode_base = world->GetAuthGameMode();
		Agame_mode_base_level_arena* game_mode_base_level_arena = Cast<Agame_mode_base_level_arena>(game_mode_base);
		game_mode_base_level_arena->implement_hud_ending();
	}
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
	camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y + oscillating_walking_y_increment * 20, camera_location_z + oscillating_walking_z_increment * 20));
}
void Apaper_player::move_backward(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), -value);
	}
	paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y + sliding_weapon_y_increment + oscillating_walking_y_increment, weapon_location_z + sliding_weapon_z_increment + oscillating_walking_z_increment));
	camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y + oscillating_walking_y_increment * 20, camera_location_z + oscillating_walking_z_increment * 20));
}
void Apaper_player::move_right(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorRightVector(), value);
	}
	paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y + sliding_weapon_y_increment + oscillating_walking_y_increment, weapon_location_z + sliding_weapon_z_increment + oscillating_walking_z_increment));
	camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y + oscillating_walking_y_increment * 20, camera_location_z + oscillating_walking_z_increment * 20));
}
void Apaper_player::move_left(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorRightVector(), -value);
	}
	paper_component->SetRelativeLocation(FVector(weapon_location_x, weapon_location_y + sliding_weapon_y_increment + oscillating_walking_y_increment, weapon_location_z + sliding_weapon_z_increment + oscillating_walking_z_increment));
	camera_component->SetRelativeLocation(FVector(camera_location_x, camera_location_y + oscillating_walking_y_increment * 20, camera_location_z + oscillating_walking_z_increment * 20));
}
void Apaper_player::look_right(float value) {
	if (value != 0.0f) {
		AddControllerYawInput(value * look_right_rate * world->GetDeltaSeconds());
	}
}
void Apaper_player::look_up(float value) {
	if (value != 0.0f) {
		AddControllerPitchInput(value * look_up_rate * world->GetDeltaSeconds());
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
	//GetWorldTimerManager().SetTimer(MyHandle, this, &Apaper_player::fire, 0.5f, true);
	if (projectile_class && paper_component->GetFlipbook() == pistol_idle_asset) {
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		MuzzleOffset.Set(200.0f, 45.0f, -30.0f);
		MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		MuzzleRotation = CameraRotation;
		if (world) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			Aprojectile* projectile = world->SpawnActor<Aprojectile>(projectile_class, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (projectile) {
				paper_component->SetFlipbook(pistol_fire_asset);
				paper_component->SetLooping(false);
				paper_component->Play();
				FVector LaunchDirection = MuzzleRotation.Vector();
				projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}