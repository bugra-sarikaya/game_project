// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "enemy.generated.h"

/**
 * 
 */
UCLASS()
class GAME_PROJECT_API Aenemy : public APaperCharacter
{
	GENERATED_BODY()
public:
	Aenemy();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere) float capsule_radius;
	UPROPERTY(VisibleAnywhere) float capsule_half_height;
	UPROPERTY(VisibleAnywhere) float paper_scale;
	UPROPERTY(VisibleAnywhere) float play_rate;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbookComponent* paper_component;
	UPROPERTY(VisibleDefaultsOnly) UCapsuleComponent* capsule_component;
	UPROPERTY(VisibleDefaultsOnly) UArrowComponent* arrow_component;
	UPROPERTY(VisibleDefaultsOnly) UCharacterMovementComponent* movement_component;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_idle_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_ready_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_chase_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_attack_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_calm_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_die_asset;
	UPROPERTY(VisibleDefaultsOnly) UPaperFlipbook* enemy_dead_asset;
protected:
	virtual void BeginPlay() override;

};
