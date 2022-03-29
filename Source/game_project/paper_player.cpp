// Fill out your copyright notice in the Description page of Project Settings.


#include "paper_player.h"


// Sets default values
Apaper_player::Apaper_player()
{
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;
	paper_component = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper"));
	check(paper_component != nullptr);
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>plane_assset(TEXT("/Game/weapons/pistol_flipbook.pistol_flipbook"));
	if (plane_assset.Succeeded()) {
		paper_component->SetFlipbook(plane_assset.Object);
		paper_component->SetRelativeLocation(FVector(20.0f, 4.7f, -6.7f));
		paper_component->SetRelativeRotation(FRotator(0.0f, 90.0, 0.0f));
		paper_component->SetWorldScale3D(FVector(0.008f));
		paper_component->SetOnlyOwnerSee(true);
		paper_component->SetupAttachment(FPSCameraComponent);
		paper_component->CastShadow = false;
		UE_LOG(LogTemp, Warning, TEXT("Plane Succeeded"));
	}
	
	//GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void Apaper_player::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);
}

// Called every frame
void Apaper_player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Apaper_player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("move_forward", this, &Apaper_player::move_forward);
	PlayerInputComponent->BindAxis("move_right", this, &Apaper_player::move_right);
	PlayerInputComponent->BindAxis("turn", this, &Apaper_player::AddControllerYawInput);
	PlayerInputComponent->BindAxis("look_up", this, &Apaper_player::AddControllerPitchInput);
	PlayerInputComponent->BindAction("jump", IE_Pressed, this, &Apaper_player::start_jump);
	PlayerInputComponent->BindAction("jump", IE_Released, this, &Apaper_player::stop_jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &Apaper_player::fire);

}
void Apaper_player::move_forward(float value) {
	// Find out which way is "forward" and rectod that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}
void Apaper_player::move_right(float value) {
	// Find out which way is "right" and rectod that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}
void Apaper_player::start_jump() {
	bPressedJump = true;
}
void Apaper_player::stop_jump() {
	bPressedJump = false;
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