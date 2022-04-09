// Fill out your copyright notice in the Description page of Project Settings.


#include "projectile.h"

// Sets default values
Aprojectile::Aprojectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent) {
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision profile name to "Projectile".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// Even called when component hits something.
		CollisionComponent->OnComponentHit.AddDynamic(this, &Aprojectile::on_hit);
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}
	if (!ProjectileMovementComponent) {
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 4000.0f;
		ProjectileMovementComponent->MaxSpeed = 4000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
		//ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		paper_component = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper"));
		check(paper_component != nullptr);
		static ConstructorHelpers::FObjectFinder<UPaperFlipbook>paper(TEXT("/Game/projectiles/projectile_v1_flipbook.projectile_v1_flipbook"));
		if (paper.Succeeded()) {
			paper_component->SetFlipbook(paper.Object);
			paper_component->SetWorldScale3D(FVector(1.0f));
			paper_component->SetupAttachment(RootComponent);
		//	//ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		//}
		//static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/sphere_material.sphere_material'"));
		//if (Material.Succeeded()) {
		//	ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		//paper_component->SetMaterial(0, ProjectileMaterialInstance);

	// Delete the projectile after 3 seconds.
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void Aprojectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aprojectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FRotator rotation = GetActorRotation();
	//paper_component->SetRelativeRotation(FRotator(0.0f, -rotation.Yaw, 0.0f));
	//class USceneComponent* ThisComponent;
	//FVector actor_location = ThisComponent->GetRelativeTransform().GetTranslation();
	//FVector actor_location = GetActorLocation();
	//FRotator rotation = UKismetMathLibrary::FindLookAtRotation(camera_location, actor_location);
	//FVector camera_location = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	//FVector actor_location = GetActorLocation();
	FRotator rotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	paper_component->SetWorldRotation(FRotator(0.0f, rotation.Yaw + 90.0f, rotation.Pitch));


}

// Function that initializes the projectile's velocity in the shoot direction.
void Aprojectile::FireInDirection(const FVector& ShootDirection) {
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
// Function that is called when the projectile hits something.
void Aprojectile::on_hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor != this && OtherComponent->IsAnySimulatingPhysics()) {
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
	Destroy();
}