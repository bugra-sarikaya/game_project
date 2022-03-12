// Fill out your copyright notice in the Description page of Project Settings.


#include "fps_character.h"

// Sets default values
Afps_character::Afps_character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);
	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// Enable the pawn to control camera rotoation.
	FPSCameraComponent->bUsePawnControlRotation = true;
	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);
	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);
	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCameraComponent);
	// Disable some environmental shadows to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void Afps_character::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);
	// Display a debug message for five seconds.
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using fps_character."));
}

// Called every frame
void Afps_character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Afps_character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("move_forward", this, &Afps_character::move_forward);
	PlayerInputComponent->BindAxis("move_right", this, &Afps_character::move_right);
	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("turn", this, &Afps_character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("look_up", this, &Afps_character::AddControllerPitchInput);
	// Set up "action" bindings.
	PlayerInputComponent->BindAction("jump", IE_Pressed, this, &Afps_character::start_jump);
	PlayerInputComponent->BindAction("jump", IE_Released, this, &Afps_character::stop_jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &Afps_character::fire);

}
void Afps_character::move_forward(float value) {
	// Find out which way is "forward" and rectod that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller -> GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}
void Afps_character::move_right(float value) {
	// Find out which way is "right" and rectod that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}
void Afps_character::start_jump() {
	bPressedJump = true;
}
void Afps_character::stop_jump() {
	bPressedJump = false;
}
void Afps_character::fire() {
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