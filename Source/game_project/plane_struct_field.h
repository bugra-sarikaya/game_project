// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"

#include "plane_inner_struct_field.h"

#include "plane_struct_field.generated.h"

UCLASS()
class GAME_PROJECT_API Uplane_struct_field : public UUserDefinedStruct {
	GENERATED_BODY()
};
USTRUCT()
struct Fplane_struct {
	GENERATED_USTRUCT_BODY()
	UPROPERTY() TArray<Fplane_inner_struct> row;
};