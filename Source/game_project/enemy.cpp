// Unreal� Engine, Copyright 1998 � 2022, Epic Games, Inc. All rights reserved.


#include "enemy.h"
#include "paper_player.h"
#include "player_state.h"

Aenemy::Aenemy() {
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = capsule_component = GetCapsuleComponent();
	check(capsule_component != nullptr);
	capsule_component->InitCapsuleSize(capsule_radius, capsule_half_height);
	capsule_component->SetEnableGravity(true);
	//capsule_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//capsule_component->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	attack_sphere_component = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Box Component"));
	check(attack_sphere_component != nullptr);
	attack_sphere_component->SetupAttachment(RootComponent);
	//attack_sphere_component->SetRelativeLocation(FVector(120.0f, 0.0f, 0.0f));
	attack_sphere_component->SetSphereRadius(130.0f);
	attack_sphere_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
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
	world = GetWorld();
	enemy_idle_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_idle_v1.enemy_idle_v1"));
	change_flipbook(paper_component, enemy_idle_asset, true, 0.5f);
	paper_component->SetCastShadow(false);
	paper_component->SetRelativeLocation(FVector(paper_location_x, paper_location_y, paper_location_z));
	paper_component->SetWorldScale3D(FVector(paper_scale));
	AI_perception_component = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	AI_sense_sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sense Sight Config"));
	AI_sense_sight_config->SightRadius = AI_sense_sight_radius_value;
	AI_sense_sight_config->LoseSightRadius = AI_sense_sight_lose_sight_radius_value;
	AI_sense_sight_config->PeripheralVisionAngleDegrees = AI_sense_sight_peripheral_vision_angle_degrees_value;
	AI_sense_sight_config->DetectionByAffiliation.bDetectEnemies = true;
	AI_sense_sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	AI_sense_sight_config->DetectionByAffiliation.bDetectNeutrals = true;
	AI_sense_sight_config->SetMaxAge(0.1f);
	AI_perception_component->ConfigureSense(*AI_sense_sight_config);
	AI_perception_component->SetDominantSense(*AI_sense_sight_config->GetSenseImplementation());
	AI_perception_component->OnPerceptionUpdated.AddDynamic(this, &Aenemy::on_sight_sensed);
	current_velocity = FVector::ZeroVector;
	enemy_ready_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_ready_v1.enemy_ready_v1"));
	enemy_chase_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_chase_v1.enemy_chase_v1"));
	enemy_attack_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_attack_v1.enemy_attack_v1"));
	enemy_calm_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_calm_v1.enemy_calm_v1"));
	enemy_die_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_die_v1.enemy_die_v1"));
	enemy_dead_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_dead_v1.enemy_dead_v1"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	paper_player_class = LoadClass<Apaper_player>(world, TEXT("/Script/game_project.paper_player"));
	check(paper_player_class != nullptr);
}
void Aenemy::BeginPlay() {
	Super::BeginPlay();
	base_location = GetActorLocation();
	//SpawnDefaultController();
}
void Aenemy::Tick(float delta_time) {
	Super::Tick(delta_time);
	FRotator rotation = world->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	RootComponent->SetWorldRotation(FRotator(0.0f, rotation.Yaw + 90.0f, rotation.Pitch));
	if(!dead) tick_AI(delta_time);
	if (!dead && health <= 0.0f) {
		player_controller = UGameplayStatics::GetPlayerController(world, 0);
		paper_player = Cast<Apaper_player>(player_controller->GetPawn());
		if (paper_player) {
			player_state_pure = paper_player->GetPlayerState();
			if (player_state_pure) {
				player_state = Cast<Aplayer_state>(player_state_pure);
				player_state->set_player_score(player_state->get_player_score() + death_score);
				//UE_LOG(LogTemp, Warning, TEXT("sdsd"))
				//UE_LOG(LogTemp, Warning, TEXT("%d"), lol_2->test_variable);
			}
		}
		//Destroy();
		change_flipbook(paper_component, enemy_die_asset, false, 1.0f);
		capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		dead = true;
	}
	if(paper_component->GetFlipbook() == enemy_die_asset && !paper_component->IsPlaying()) change_flipbook(paper_component, enemy_dead_asset, false, 1.0f);
}
void Aenemy::EndPlay(EEndPlayReason::Type reason) {
	Super::EndPlay(reason);
}
void Aenemy::change_flipbook(UPaperFlipbookComponent* flipbook_component, UPaperFlipbook* flipbook_asset, bool looping_status, float new_play_rate) {
	flipbook_component->SetFlipbook(flipbook_asset);
	flipbook_component->SetLooping(looping_status);
	flipbook_component->SetPlayRate(new_play_rate);
	flipbook_component->Play();
}
void Aenemy::on_sight_sensed(const TArray<AActor*>& updated_actors) {
	if (!dead) {
		for (int i = 0; i < updated_actors.Num(); i++) {
			FActorPerceptionBlueprintInfo info_0;
			AI_perception_component->GetActorsPerception(updated_actors[i], info_0);
			if (info_0.LastSensedStimuli[0].WasSuccessfullySensed() && updated_actors[i]->GetClass() == paper_player_class && paper_component->GetFlipbook() != enemy_attack_asset) {
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
}
void Aenemy::on_begin_overlap(UPrimitiveComponent*  overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index, bool b_from_sweep, const FHitResult& hit){
	if (other_actor && !dead) {
		paper_player = Cast<Apaper_player>(other_actor);
		if (paper_player) {
			change_flipbook(paper_component, enemy_attack_asset, true, 0.8f);
		}
	}
}
void Aenemy::on_end_overlap(UPrimitiveComponent* overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index) {
	if (other_actor && !dead) {
		paper_player = Cast<Apaper_player>(other_actor);
		if (paper_player) {
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
