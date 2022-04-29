// Fill out your copyright notice in the Description page of Project Settings.


#include "enemy.h"
Aenemy::Aenemy() {
	capsule_half_height = 130.0f;
	capsule_radius = 80.0f;
	paper_scale = 0.6f;
	play_rate = 0.5f;
	PrimaryActorTick.bCanEverTick = true;
	//bSimulatePhysics = true;
	capsule_component = GetCapsuleComponent();
	check(capsule_component != nullptr);
	capsule_component->InitCapsuleSize(capsule_radius, capsule_half_height);
	//capsule_component->SetSimulatePhysics(true);
	//capsule_component->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	//capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	//capsule_component->SetUseCCD(true);
	capsule_component->SetEnableGravity(true);
	RootComponent = capsule_component;
	paper_component = (UPaperFlipbookComponent*)GetComponentByClass(UPaperFlipbookComponent::StaticClass());
	check(paper_component != nullptr);
	enemy_idle_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_idle_v1.enemy_idle_v1"));
	paper_component->SetFlipbook(enemy_idle_asset);
	paper_component->CastShadow = false;
	paper_component->SetWorldScale3D(FVector(paper_scale));
	paper_component->SetPlayRate(play_rate);
	paper_component->SetupAttachment(capsule_component);
	//movement_component = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("Movement Component"));
	//check(movement_component != nullptr);
	//movement_component->RepulsionForce = 0.0f;
	//movement_component->TouchForceFactor = 0.0f;
	//movement_component->MinTouchForce = 0.0f;
	//movement_component->MaxTouchForce = 0.0f;
	//movement_component->GravityScale = 1.0f;
	//movement_component->SetUpdatedComponent(capsule_component);


}
void Aenemy::BeginPlay() {
	Super::BeginPlay();
}
void Aenemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FRotator rotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	paper_component->SetWorldRotation(FRotator(0.0f, rotation.Yaw + 90.0f, rotation.Pitch));
}