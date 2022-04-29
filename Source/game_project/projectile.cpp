// Fill out your copyright notice in the Description page of Project Settings.


#include "projectile.h"

// Sets default values
Aprojectile::Aprojectile()
{
	collision_sphere_radius = 10.0f;
	initial_speed = 4000.0f;
	max_speed = 4000.0f;
	following_velocity = true;
	world_scale = 0.6f;
	life_span = 3.0f;
	bouncing = false;
	gravity_scale = 0.0f;
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent) {
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &Aprojectile::on_hit);
		CollisionComponent->InitSphereRadius(collision_sphere_radius);
		CollisionComponent->bIgnoreRadialImpulse = true;
		CollisionComponent->bIgnoreRadialForce = true;
		RootComponent = CollisionComponent;
	}
	if (!ProjectileMovementComponent) {
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = initial_speed;
		ProjectileMovementComponent->MaxSpeed = max_speed;
		ProjectileMovementComponent->bRotationFollowsVelocity = following_velocity;
		ProjectileMovementComponent->bShouldBounce = bouncing;
		ProjectileMovementComponent->ProjectileGravityScale = gravity_scale;
	}
		//ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		paper_component = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper"));
		check(paper_component != nullptr);
		static ConstructorHelpers::FObjectFinder<UPaperFlipbook>paper(TEXT("/Game/projectiles/projectile_idle_v2.projectile_idle_v2"));
		if (paper.Succeeded()) {
			paper_component->SetFlipbook(paper.Object);
			paper_component->SetWorldScale3D(FVector(world_scale));
			paper_component->SetupAttachment(RootComponent);
		//	//ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		//}
		//static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/sphere_material.sphere_material'"));
		//if (Material.Succeeded()) {
		//	ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		//paper_component->SetMaterial(0, ProjectileMaterialInstance);

		InitialLifeSpan = life_span;
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
	//if (OtherActor != this && OtherComponent->IsAnySimulatingPhysics()) {
	//	OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	//}
	Destroy();
}