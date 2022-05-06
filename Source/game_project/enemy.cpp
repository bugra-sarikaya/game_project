// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.


#include "enemy.h"
#include "paper_player.h"

Aenemy::Aenemy() {
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = capsule_component = GetCapsuleComponent();
	check(capsule_component != nullptr);
	capsule_component->InitCapsuleSize(capsule_radius, capsule_half_height);
	capsule_component->SetEnableGravity(true);
	//capsule_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	attack_sphere_component = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Box Component"));
	check(attack_sphere_component != nullptr);
	attack_sphere_component->SetupAttachment(RootComponent);
	//attack_sphere_component->SetRelativeLocation(FVector(120.0f, 0.0f, 0.0f));
	attack_sphere_component->SetSphereRadius(130.0f);
	attack_sphere_component->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	//attack_sphere_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//attack_sphere_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	attack_sphere_component->OnComponentBeginOverlap.AddDynamic(this, &Aenemy::on_begin_overlap);
	attack_sphere_component->OnComponentEndOverlap.AddDynamic(this, &Aenemy::on_end_overlap);
	//attack_box_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//attack_box_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	//attack_box_component->OnComponentBeginOverlap.AddDynamic(this, &Aenemy::on_overlap);
	paper_component = (UPaperFlipbookComponent*)GetComponentByClass(UPaperFlipbookComponent::StaticClass());
	check(paper_component != nullptr);
	paper_component->SetupAttachment(capsule_component);
	enemy_idle_asset = LoadObject<UPaperFlipbook>(GetWorld(), TEXT("/Game/enemies/enemy_idle_v1.enemy_idle_v1"));
	change_flipbook(paper_component, enemy_idle_asset, true, 0.5f);
	paper_component->SetCastShadow(false);
	paper_component->SetRelativeLocation(FVector(paper_location_x, paper_location_y, paper_location_z));
	paper_component->SetWorldScale3D(FVector(paper_scale));
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
	AI_perception_component->OnPerceptionUpdated.AddDynamic(this, &Aenemy::on_sight_sensed);
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
	RootComponent->SetWorldRotation(FRotator(0.0f, rotation.Yaw + 90.0f, rotation.Pitch));
	tick_AI(delta_time);
	if (health <= 0.0f) Destroy();
}
void Aenemy::change_flipbook(UPaperFlipbookComponent* flipbook_component, UPaperFlipbook* flipbook_asset, bool looping_status, float new_play_rate) {
	flipbook_component->SetFlipbook(flipbook_asset);
	flipbook_component->SetLooping(looping_status);
	flipbook_component->SetPlayRate(new_play_rate);
	flipbook_component->Play();
}
void Aenemy::on_sight_sensed(const TArray<AActor*>& updated_actors) {
	for (int i = 0; i < updated_actors.Num(); i++) {
		FActorPerceptionBlueprintInfo info_0;
		AI_perception_component->GetActorsPerception(updated_actors[i], info_0);
		if (info_0.LastSensedStimuli[0].WasSuccessfullySensed() && paper_component->GetFlipbook() != enemy_attack_asset) {
			FVector direction = updated_actors[i]->GetActorLocation() - GetActorLocation();
			direction.Z = 0.0f;
			current_velocity = direction.GetSafeNormal() * movement_speed;
		}
		else if (!info_0.LastSensedStimuli[0].WasSuccessfullySensed() && paper_component->GetFlipbook() != enemy_attack_asset) {
			FVector direction = base_location - GetActorLocation();
			direction.Z = 0.0f;
			if (direction.SizeSquared2D() > 1.0f) {
				current_velocity = direction.GetSafeNormal() * movement_speed;
				back_to_base_location = true;
			}
		}
		else if (info_0.LastSensedStimuli[0].WasSuccessfullySensed() && paper_component->GetFlipbook() == enemy_attack_asset) {
			current_velocity = FVector::ZeroVector;
		}
	}
}
void Aenemy::on_begin_overlap(UPrimitiveComponent*  overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index, bool b_from_sweep, const FHitResult& hit){
	if (other_actor) {
		paper_player = Cast<Apaper_player>(other_actor);
		if (paper_player) {
			//UE_LOG(LogTemp, Warning, TEXT("Begin Overlapping player."))
			change_flipbook(paper_component, enemy_attack_asset, true, 0.8f);
		}
	}
}
void Aenemy::on_end_overlap(UPrimitiveComponent* overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index) {
	if (other_actor) {
		paper_player = Cast<Apaper_player>(other_actor);
		if (paper_player) {
			//UE_LOG(LogTemp, Warning, TEXT("End Overlapping player."))
			change_flipbook(paper_component, enemy_chase_asset, true, 1.0f);
			paper_player = nullptr;
		}
	}
}
void Aenemy::tick_AI(float delta_time) {
	if (!current_velocity.IsZero() && paper_component->GetFlipbook() == enemy_idle_asset) {
		change_flipbook(paper_component, enemy_ready_asset, false, 1.0f);
	}
	else if (!current_velocity.IsZero() && paper_component->GetFlipbook() == enemy_ready_asset && !paper_component->IsPlaying()) {
		change_flipbook(paper_component, enemy_chase_asset, true, 1.0f);
	}
	else if (!current_velocity.IsZero() && paper_component->GetFlipbook() == enemy_chase_asset) {
		new_location = GetActorLocation() + current_velocity * delta_time;
		if (back_to_base_location) {
			if ((new_location - base_location).SizeSquared2D() < distance_squared) {
				distance_squared = (new_location - base_location).SizeSquared2D();
			}
			else {
				current_velocity = FVector::ZeroVector;
				distance_squared = BIG_NUMBER;
				change_flipbook(paper_component, enemy_calm_asset, false, 1.0f);
				back_to_base_location = false;
			}
		}
		SetActorLocation(new_location);
	}
	if (paper_component->GetFlipbook() == enemy_calm_asset && !paper_component->IsPlaying()) {
		change_flipbook(paper_component, enemy_idle_asset, true, 0.5f);
	}
	if (attack_sphere_component->IsOverlappingActor(paper_player) && !did_attack && paper_component->GetFlipbook() == enemy_attack_asset && (paper_component->GetPlaybackPositionInFrames() == 2 || paper_component->GetPlaybackPositionInFrames() == 5)) {
		attack(paper_player, damage_value);
		did_attack = true;
	}
	else if (!attack_sphere_component->IsOverlappingActor(paper_player) || (paper_component->GetFlipbook() == enemy_attack_asset && !(paper_component->GetPlaybackPositionInFrames() == 2 || paper_component->GetPlaybackPositionInFrames() == 5))) {
		did_attack = false;
	}
}
void Aenemy::attack(Apaper_player* attacked_player, float damage_amount) {
	attacked_player->health -= damage_amount;
}
