// Fill out your copyright notice in the Description page of Project Settings.


#include "enemy.h"
#include "paper_player.h"

Aenemy::Aenemy() {
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = capsule_component = GetCapsuleComponent();
	check(capsule_component != nullptr);
	capsule_component->InitCapsuleSize(capsule_radius, capsule_half_height);
	capsule_component->SetEnableGravity(true);
	capsule_component->OnComponentBeginOverlap.AddDynamic(this, &Aenemy::on_overlap);
	//capsule_component->OnComponentHit.AddDynamic(this, &Aenemy::on_hit);
	capsule_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	paper_component = (UPaperFlipbookComponent*)GetComponentByClass(UPaperFlipbookComponent::StaticClass());
	check(paper_component != nullptr);
	paper_component->SetupAttachment(capsule_component);
	enemy_idle_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_idle_v1.enemy_idle_v1"));
	paper_component->SetFlipbook(enemy_idle_asset);
	paper_component->CastShadow = false;
	paper_component->SetWorldScale3D(FVector(paper_scale));
	paper_component->SetPlayRate(0.5f);
	AI_perception_component = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	AI_sense_sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sense Sight Config"));
	AI_sense_sight_config->SightRadius = 1250.0f;
	AI_sense_sight_config->LoseSightRadius = 1280.0f;
	AI_sense_sight_config->PeripheralVisionAngleDegrees = 360.0f;
	AI_sense_sight_config->DetectionByAffiliation.bDetectEnemies = true;
	AI_sense_sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	AI_sense_sight_config->DetectionByAffiliation.bDetectNeutrals = true;
	AI_sense_sight_config->SetMaxAge(0.1f);
	AI_perception_component->ConfigureSense(*AI_sense_sight_config);
	AI_perception_component->SetDominantSense(*AI_sense_sight_config->GetSenseImplementation());
	AI_perception_component->OnPerceptionUpdated.AddDynamic(this, &Aenemy::on_sensed);
	current_velocity = FVector::ZeroVector;
	enemy_ready_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_ready_v1.enemy_ready_v1"));
	enemy_chase_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_chase_v1.enemy_chase_v1"));
	enemy_attack_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_attack_v1.enemy_attack_v1"));
	enemy_calm_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_calm_v1.enemy_calm_v1"));
	enemy_die_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_die_v1.enemy_die_v1"));
	enemy_dead_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_dead_v1.enemy_dead_v1"));
}
void Aenemy::BeginPlay() {
	Super::BeginPlay();
	base_location = GetActorLocation();
}
void Aenemy::Tick(float delta_time) {
	Super::Tick(delta_time);
	FRotator rotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	paper_component->SetWorldRotation(FRotator(0.0f, rotation.Yaw + 90.0f, rotation.Pitch));
	if (!current_velocity.IsZero() && paper_component->GetFlipbook() == enemy_idle_asset){
		paper_component->SetFlipbook(enemy_ready_asset);
		paper_component->SetLooping(false);
		paper_component->SetPlayRate(1.0f);
		paper_component->Play();
	}
	if (!current_velocity.IsZero() && paper_component->GetFlipbook() == enemy_ready_asset && !paper_component->IsPlaying()) {
		paper_component->SetFlipbook(enemy_chase_asset);
		paper_component->SetLooping(true);
		paper_component->SetPlayRate(1.0f);
		paper_component->Play();
	}
	if (!current_velocity.IsZero() && paper_component->GetFlipbook() == enemy_chase_asset) {
		new_location = GetActorLocation() + current_velocity * delta_time;
		if (back_to_base_location) {
			if ((new_location - base_location).SizeSquared2D() < distance_squared) {
				distance_squared = (new_location - base_location).SizeSquared2D();
			}
			else {
				current_velocity = FVector::ZeroVector;
				distance_squared = BIG_NUMBER;
				paper_component->SetFlipbook(enemy_calm_asset);
				paper_component->SetLooping(false);
				paper_component->Play();
				paper_component->SetPlayRate(1.0f);
				back_to_base_location = false;
			}
		}
		SetActorLocation(new_location);
	}
	if (paper_component->GetFlipbook() == enemy_calm_asset && !paper_component->IsPlaying()) {
		paper_component->SetFlipbook(enemy_idle_asset);
		paper_component->SetLooping(true);
		paper_component->SetPlayRate(0.5f);
		paper_component->Play();
	}
}
void Aenemy::on_overlap(UPrimitiveComponent* hit_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index, bool b_from_sweep, const FHitResult& hit){
	Apaper_player* player = Cast<Apaper_player>(other_actor);
	if (player) {
		paper_component->SetFlipbook(enemy_attack_asset);
		paper_component->SetLooping(true);
		paper_component->SetPlayRate(1.0f);
		paper_component->Play();
		current_velocity = FVector::ZeroVector;
		player->deal_damage(damage_value);
	}
}
void Aenemy::on_hit(UPrimitiveComponent* hit_component, AActor* other_actor, UPrimitiveComponent* other_component, FVector normal_impulse, const FHitResult& hit) {
	Apaper_player* player = Cast<Apaper_player>(other_actor);
	if (player) {
		paper_component->SetFlipbook(enemy_attack_asset);
		paper_component->SetLooping(true);
		paper_component->SetPlayRate(1.0f);
		paper_component->Play();
		current_velocity = FVector::ZeroVector;
		player->deal_damage(damage_value);
	}
}
void Aenemy::on_sensed(const TArray<AActor*>&uppdated_actors) {
	for (int i = 0; i < uppdated_actors.Num(); i++) {
		FActorPerceptionBlueprintInfo info;
		AI_perception_component->GetActorsPerception(uppdated_actors[i], info);
		if (info.LastSensedStimuli[0].WasSuccessfullySensed() && paper_component->GetFlipbook() != enemy_attack_asset) {
			FVector direction = uppdated_actors[i]->GetActorLocation() - GetActorLocation();
			direction.Z = 0.0f;
			current_velocity = direction.GetSafeNormal() * movement_speed;
		}
		else {
			FVector direction = base_location - GetActorLocation();
			direction.Z = 0.0f;
			if (direction.SizeSquared2D() > 1.0f) {
				current_velocity = direction.GetSafeNormal() * movement_speed;
				back_to_base_location = true;
			}
		}
	}
}
void Aenemy::deal_damage(float damage_amount) {
	health -= damage_amount;
	if (health <= 0.0f) {
		Destroy();
	}
}