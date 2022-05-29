// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "projectile.h"
#include "enemy.h"

Aprojectile::Aprojectile() {
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = collision_component = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
	check(collision_component != nullptr);
	collision_component->InitSphereRadius(collision_sphere_radius);
	collision_component->OnComponentHit.AddDynamic(this, &Aprojectile::on_hit);
	collision_component->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	collision_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	projectile_movement_component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	check(projectile_movement_component != nullptr);
	projectile_movement_component->SetUpdatedComponent(RootComponent);
	projectile_movement_component->InitialSpeed = initial_speed;
	projectile_movement_component->MaxSpeed = max_speed;
	projectile_movement_component->bRotationFollowsVelocity = following_velocity;
	projectile_movement_component->bShouldBounce = bouncing;
	projectile_movement_component->ProjectileGravityScale = gravity_scale;
	paper_component = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper Component"));
	check(paper_component != nullptr);
	paper_component->SetupAttachment(RootComponent);
	projectile_idle_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/projectiles/projectile_idle_v2.projectile_idle_v2"));
	paper_component->SetFlipbook(projectile_idle_asset);
	paper_component->SetWorldScale3D(FVector(world_scale));
	InitialLifeSpan = life_span;
}
void Aprojectile::BeginPlay(){
	Super::BeginPlay();
}
void Aprojectile::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	FRotator rotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	RootComponent->SetWorldRotation(FRotator(0.0f, rotation.Yaw + 90.0f, rotation.Pitch));
}
void Aprojectile::FireInDirection(const FVector& ShootDirection) {
	projectile_movement_component->Velocity = ShootDirection * projectile_movement_component->InitialSpeed;
}
void Aprojectile::on_hit(UPrimitiveComponent* hit_component, AActor* other_actor, UPrimitiveComponent* other_component, FVector normal_impulse, const FHitResult& hit) {
	enemy = Cast<Aenemy>(other_actor);
	if (enemy) deal_damage(enemy, damage_value);
	Destroy();
}
void Aprojectile::deal_damage(Aenemy* attack_enemy, float damage_amount) {
	attack_enemy->health -= damage_amount;
	attack_enemy->play_sound_pain();
}