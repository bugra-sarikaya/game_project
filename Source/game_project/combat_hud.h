// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Engine/Canvas.h"

#include "combat_hud.generated.h"

/**
 * 
 */
UCLASS()
class GAME_PROJECT_API Acombat_hud : public AHUD
{
	GENERATED_BODY()
	
public:
	Acombat_hud();
	virtual void DrawHUD() override;
protected:
	UPROPERTY(EditDefaultsOnly)
		UTexture2D* crosshair_texture;
};