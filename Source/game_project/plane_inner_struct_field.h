// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "plane_inner_struct_field.generated.h"

class Astatic_mesh_plane;

UCLASS()
class GAME_PROJECT_API Uplane_inner_struct_field : public UUserDefinedStruct {
	GENERATED_BODY()
};
USTRUCT()
struct Fplane_inner_struct {
	GENERATED_USTRUCT_BODY()
	UPROPERTY() TArray<Astatic_mesh_plane*> column;
};