// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"

#include "Materials/MaterialInterface.h"

#include "struct_field_material_pack.generated.h"

UCLASS()
class GAME_PROJECT_API Ustruct_field_material_pack : public UUserDefinedStruct {
	GENERATED_BODY()
};
USTRUCT()
struct Fmaterial_asset_struct_pack {
	GENERATED_USTRUCT_BODY()
	UPROPERTY() UMaterialInterface* bottom_left = nullptr;
	UPROPERTY() UMaterialInterface* bottom_middle = nullptr;
	UPROPERTY() UMaterialInterface* bottom_right = nullptr;
	UPROPERTY() UMaterialInterface* middle_left = nullptr;
	UPROPERTY() UMaterialInterface* middle_middle = nullptr;
	UPROPERTY() UMaterialInterface* middle_right = nullptr;
	UPROPERTY() UMaterialInterface* top_left = nullptr;
	UPROPERTY() UMaterialInterface* top_middle = nullptr;
	UPROPERTY() UMaterialInterface* top_right = nullptr;
};