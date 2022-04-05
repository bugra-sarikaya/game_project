// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/Engine.h"
#include "game_projectGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class GAME_PROJECT_API Agame_projectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	Agame_projectGameModeBase();
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
};