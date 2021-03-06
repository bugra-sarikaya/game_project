// Unreal® Engine, Copyright 1998 – 2022, Epic Games, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "static_mesh.h"
#include "static_mesh_plane.generated.h"

UCLASS()
class GAME_PROJECT_API Astatic_mesh_plane : public Astatic_mesh {
	GENERATED_BODY()
public:
	Astatic_mesh_plane();
	UPROPERTY() FString static_mesh_asset_reference = "/Game/meshes/Plane.plane";
	UPROPERTY() UStaticMesh* static_mesh_asset;
	UPROPERTY() UStaticMeshComponent* static_mesh_component;
};
