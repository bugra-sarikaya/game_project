// Fill out your copyright notice in the Description page of Project Settings.


#include "paper_player.h"


// Sets default values
Apaper_player::Apaper_player()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
	FPSCameraComponent->bUsePawnControlRotation = true;
	paper_component = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper"));
	check(paper_component != nullptr);
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>plane_assset(TEXT("/Game/weapons/pistol_flipbook.pistol_flipbook"));
	if (plane_assset.Succeeded()) {
		paper_component->SetFlipbook(plane_assset.Object);
		paper_component->SetRelativeLocation(FVector(location_x, location_y, location_z));
		paper_component->SetRelativeRotation(FRotator(rotation_pitch, rotation_yaw, rotation_roll));
		paper_component->SetWorldScale3D(FVector(scale));
		paper_component->SetOnlyOwnerSee(true);
		paper_component->SetupAttachment(FPSCameraComponent);
		paper_component->CastShadow = false;
	}
	//GetMesh()->SetOwnerNoSee(true);

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
	const APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller->IsInputKeyDown(FKey(TEXT("W")))) {
		if (location_z_increment >= -increment_limit) location_z_increment = location_z_increment - location_z_increment_rate;
	}
	else {
		if (location_z_increment <= 0.0f) location_z_increment = location_z_increment + location_z_increment_rate;
	}
	if (controller->IsInputKeyDown(FKey(TEXT("S")))) {
		if (location_z_increment <= increment_limit) location_z_increment = location_z_increment + location_z_increment_rate;
	}
	else {
		if (location_z_increment >= 0.0f) location_z_increment = location_z_increment - location_z_increment_rate;
	}
	if (controller->IsInputKeyDown(FKey(TEXT("D")))) {
		if (location_y_increment >= -increment_limit) location_y_increment = location_y_increment - location_y_increment_rate;
	}
	else {
		if (location_y_increment <= 0.0f) location_y_increment = location_y_increment + location_y_increment_rate;
	}
	if (controller->IsInputKeyDown(FKey(TEXT("A")))) {
		if (location_y_increment <= increment_limit) location_y_increment = location_y_increment + location_y_increment_rate;
	}
	else {
		if (location_y_increment >= 0.0f) location_y_increment = location_y_increment - location_y_increment_rate;
	}
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
	paper_component->SetRelativeLocation(FVector(location_x, location_y + location_y_increment, location_z + location_z_increment));
}
void Apaper_player::move_backward(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), -value);
	}
	paper_component->SetRelativeLocation(FVector(location_x, location_y + location_y_increment, location_z + location_z_increment));
}
void Apaper_player::move_right(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorRightVector(), value);
	}
	paper_component->SetRelativeLocation(FVector(location_x, location_y + location_y_increment, location_z + location_z_increment));
}
void Apaper_player::move_left(float value) {
	if (value != 0.0f) {
		AddMovementInput(GetActorRightVector(), -value);
	}
	paper_component->SetRelativeLocation(FVector(location_x, location_y + location_y_increment, location_z + location_z_increment));
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