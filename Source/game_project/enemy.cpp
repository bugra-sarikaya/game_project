// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#include "enemy.h"
#include "paper_player.h"
#include "player_state.h"

Aenemy::Aenemy() {
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	RootComponent = capsule_component = GetCapsuleComponent();
	check(capsule_component != nullptr);
	capsule_component->InitCapsuleSize(capsule_radius, capsule_half_height);
	capsule_component->SetEnableGravity(true);
	capsule_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	capsule_component->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	attack_sphere_component = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Box Component"));
	check(attack_sphere_component != nullptr);
	attack_sphere_component->SetupAttachment(RootComponent);
	attack_sphere_component->SetSphereRadius(130.0f);
	attack_sphere_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	attack_sphere_component->OnComponentBeginOverlap.AddDynamic(this, &Aenemy::on_begin_overlap);
	attack_sphere_component->OnComponentEndOverlap.AddDynamic(this, &Aenemy::on_end_overlap);
	paper_component = (UPaperFlipbookComponent*)GetComponentByClass(UPaperFlipbookComponent::StaticClass());
	check(paper_component != nullptr);
	paper_component->SetupAttachment(capsule_component);
	world = GetWorld();
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
	audio_component_idle = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_idle"));
	check(audio_component_idle != nullptr);
	audio_component_idle->bAutoActivate = false;
	audio_component_idle->SetupAttachment(RootComponent);
	audio_component_idle->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	audio_component_ready= CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_ready"));
	check(audio_component_ready != nullptr);
	audio_component_ready->bAutoActivate = false;
	audio_component_ready->SetupAttachment(RootComponent);
	audio_component_ready->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	audio_component_chase = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_chase"));
	check(audio_component_chase != nullptr);
	audio_component_chase->bAutoActivate = false;
	audio_component_chase->SetupAttachment(RootComponent);
	audio_component_chase->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	audio_component_pain = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_pain"));
	check(audio_component_pain != nullptr);
	audio_component_pain->bAutoActivate = false;
	audio_component_pain->SetupAttachment(RootComponent);
	audio_component_pain->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	audio_component_claw_strike = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_claw_strike"));
	check(audio_component_claw_strike != nullptr);
	audio_component_claw_strike->bAutoActivate = false;
	audio_component_claw_strike->SetupAttachment(RootComponent);
	audio_component_claw_strike->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	audio_component_die = CreateDefaultSubobject<UAudioComponent>(TEXT("audio_component_die"));
	check(audio_component_die != nullptr);
	audio_component_die->bAutoActivate = false;
	audio_component_die->SetupAttachment(RootComponent);
	audio_component_die->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	paper_player_class = LoadClass<Apaper_player>(world, TEXT("/Script/game_project.paper_player"));
	check(paper_player_class != nullptr);
	enemy_idle_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_idle_v1.enemy_idle_v1"));
	enemy_ready_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_ready_v1.enemy_ready_v1"));
	enemy_chase_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_chase_v1.enemy_chase_v1"));
	enemy_attack_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_attack_v1.enemy_attack_v1"));
	enemy_calm_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_calm_v1.enemy_calm_v1"));
	enemy_die_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_die_v1.enemy_die_v1"));
	enemy_dead_asset = LoadObject<UPaperFlipbook>(world, TEXT("/Game/enemies/enemy_dead_v1.enemy_dead_v1"));
	sound_cue_asset_idle = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_idle.sound_cue_idle"));
	sound_cue_asset_ready = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_ready.sound_cue_ready"));
	sound_cue_asset_chase = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_chase.sound_cue_chase"));
	sound_cue_asset_pain = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_pain.sound_cue_pain"));
	sound_cue_asset_claw_strike = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_claw_strike.sound_cue_claw_strike"));
	sound_cue_asset_die = LoadObject<USoundCue>(world, TEXT("/Game/sounds/sound_cue_die.sound_cue_die"));
	change_flipbook(paper_component, enemy_idle_asset, true, 0.5f);
	GetCharacterMovement()->MaxWalkSpeed = movement_speed;
	GetCharacterMovement()->AirControl = 1;
	audio_component_idle->SetSound(sound_cue_asset_idle);
	audio_component_idle->SetVolumeMultiplier(volume_multiplier_ready);
	audio_component_ready->SetSound(sound_cue_asset_ready);
	audio_component_ready->SetVolumeMultiplier(volume_multiplier_ready);
	audio_component_chase->SetSound(sound_cue_asset_chase);
	audio_component_chase->SetVolumeMultiplier(volume_multiplier_chase);
	audio_component_pain->SetSound(sound_cue_asset_pain);
	audio_component_pain->SetVolumeMultiplier(volume_multiplier_pain);
	audio_component_claw_strike->SetSound(sound_cue_asset_claw_strike);
	audio_component_claw_strike->SetVolumeMultiplier(volume_multiplier_claw_strike);
	audio_component_die->SetSound(sound_cue_asset_die);
	audio_component_die->SetVolumeMultiplier(volume_multiplier_die);
}
void Aenemy::BeginPlay() {
	Super::BeginPlay();
	player_controller = UGameplayStatics::GetPlayerController(world, 0);
}
void Aenemy::Tick(float delta_time) {
	Super::Tick(delta_time);
	FRotator rotation = world->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	RootComponent->SetWorldRotation(FRotator(0.0f, rotation.Yaw + 90.0f, rotation.Pitch));
	if (!dead && attack_sphere_component->IsOverlappingActor(paper_player) && !did_attack && paper_component->GetFlipbook() == enemy_attack_asset && (paper_component->GetPlaybackPositionInFrames() == 0 || paper_component->GetPlaybackPositionInFrames() == 3)) {
		attack(paper_player, damage_value);
		audio_component_claw_strike->Play();
		did_attack = true;
	}
	else if (!dead && !attack_sphere_component->IsOverlappingActor(paper_player) || (paper_component->GetFlipbook() == enemy_attack_asset && !(paper_component->GetPlaybackPositionInFrames() == 0 || paper_component->GetPlaybackPositionInFrames() == 3))) did_attack = false;
	//if (!dead && paper_component->GetFlipbook() == enemy_chase_asset) {
	//	AI_controller = Cast<AAIController>(GetController());
	//	if (AI_controller && AI_controller->GetMoveStatus() == EPathFollowingStatus::Idle) {
	//		change_flipbook(paper_component, enemy_calm_asset, false, 1.0f);
	//		timer_delegate_idle.BindUFunction(this, FName("change_flipbook"), paper_component, enemy_idle_asset, true, 0.5f);
	//		GetWorldTimerManager().SetTimer(timer_handle_idle, timer_delegate_idle, paper_component->GetFlipbookLength(), false);
	//		sensed = false;
	//	}
	//}
	if (!dead && paper_component->GetFlipbook()) {
		paper_player = Cast<Apaper_player>(player_controller->GetPawn());
		if (!paper_player) {
			dead = true;
			Destroy();
		}
	}
	if (!dead && paper_component->GetFlipbook() == enemy_idle_asset && !audio_component_idle->IsActive()) audio_component_idle->Play();
	if (!dead && paper_component->GetFlipbook() == enemy_chase_asset && !audio_component_chase->IsActive() && audio_component_pain->IsActive()) audio_component_idle->Play();
	if (!dead && health <= 0.0f) {
		dead = true;
		sensed = false;
		paper_player = Cast<Apaper_player>(player_controller->GetPawn());
		if (paper_player) {
			player_state_pure = paper_player->GetPlayerState();
			if (player_state_pure) {
				player_state = Cast<Aplayer_state>(player_state_pure);
				player_state->set_player_score(player_state->get_player_score() + death_score);
			}
		}
		change_flipbook(paper_component, enemy_die_asset, false, 1.0f);
		capsule_component->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
		capsule_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
		AI_controller = Cast<AAIController>(GetController());
		if (AI_controller) {
			AI_controller->StopMovement();
			AI_perception_component->DestroyComponent();
			attack_sphere_component->DestroyComponent();
			audio_component_idle->DestroyComponent();
			audio_component_ready->DestroyComponent();
			audio_component_chase->DestroyComponent();
			audio_component_pain->DestroyComponent();
			audio_component_claw_strike->DestroyComponent();
			audio_component_die->Play();
			timer_delegate_destroy_audio_component_die.BindUFunction(this, FName("destroy_component"), audio_component_die);
			GetWorldTimerManager().SetTimer(timer_handle_destroy_audio_component_die, timer_delegate_destroy_audio_component_die, sound_cue_asset_die->GetDuration(), false);
		}
	}
	else if(dead && paper_component->GetFlipbook() == enemy_chase_asset) change_flipbook(paper_component, enemy_die_asset, false, 0.8f);
	else if (dead && paper_component->GetFlipbook() == enemy_die_asset && !paper_component->IsPlaying()) change_flipbook(paper_component, enemy_dead_asset, false, 1.0f);
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
			if (info_0.LastSensedStimuli[0].WasSuccessfullySensed() && updated_actors[i]->GetClass() == paper_player_class) {
				if (!sensed && paper_component->GetFlipbook() == enemy_idle_asset && paper_component->GetFlipbook() == enemy_idle_asset) {
					change_flipbook(paper_component, enemy_ready_asset, false, 1.0f);
					if(audio_component_idle->IsActive()) audio_component_idle->Stop();
					audio_component_ready->Play();
					timer_delegate_chase.BindUFunction(this, FName("chase"), updated_actors[i]);
					GetWorldTimerManager().SetTimer(timer_handle_chase, timer_delegate_chase, paper_component->GetFlipbookLength(), false);
					sensed = true;
				}
				else if (sensed && paper_component->GetFlipbook() == enemy_chase_asset) chase(updated_actors[i]);
			}
		}
	}
}
void Aenemy::on_begin_overlap(UPrimitiveComponent* overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index, bool b_from_sweep, const FHitResult& hit){
	if (!dead && other_actor) {
		paper_player = Cast<Apaper_player>(other_actor);
		if (paper_player) {
			change_flipbook(paper_component, enemy_attack_asset, true, 0.8f);
			GetCharacterMovement()->MaxWalkSpeed = movement_speed / 4.5f;
		}
	}
}
void Aenemy::on_end_overlap(UPrimitiveComponent* overlap_component, AActor* other_actor, UPrimitiveComponent* other_component, int32 other_body_index) {
	if (!dead && other_actor) {
		paper_player = Cast<Apaper_player>(other_actor);
		if (paper_player) {
			change_flipbook(paper_component, enemy_chase_asset, true, 1.0f);
			GetCharacterMovement()->MaxWalkSpeed = movement_speed;
			paper_player = nullptr;
		}
	}
}
void Aenemy::attack(Apaper_player* attacked_player, float damage_amount) {
	attacked_player->health -= damage_amount;
	if (!audio_component_claw_strike->IsActive()) {
		if (audio_component_chase->IsActive()) audio_component_chase->Stop();
		audio_component_claw_strike->Play();
	}
}
void Aenemy::chase(AActor* chased_actor) {
	AI_controller = Cast<AAIController>(GetController());
	if (AI_controller) {
		AI_controller->MoveToActor(chased_actor);
		paper_player = Cast<Apaper_player>(chased_actor);
		if (AI_controller->GetMoveStatus() == EPathFollowingStatus::Moving && paper_player->GetCharacterMovement()->IsMovingOnGround()) AI_controller->MoveToActor(chased_actor, -1.0f, false, true);
		else if (AI_controller->GetMoveStatus() == EPathFollowingStatus::Moving && !paper_player->GetCharacterMovement()->IsMovingOnGround()) AI_controller->MoveToActor(chased_actor, -1.0f, false, false);
		change_flipbook(paper_component, enemy_chase_asset, true, 1.0f);
		if (!audio_component_chase->IsActive()) {
			if (audio_component_idle->IsActive()) audio_component_idle->Stop();
			audio_component_chase->Play();
		}
	}
}
void Aenemy::destroy_component(USceneComponent* component) {
	component->DestroyComponent();
}
void Aenemy::play_sound_pain() {
	if (!dead) {
		if (audio_component_chase->IsActive()) audio_component_chase->Stop();
		audio_component_pain->Play();
	}
}