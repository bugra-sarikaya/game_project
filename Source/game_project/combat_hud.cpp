// Fill out your copyright notice in the Description page of Project Settings.


#include "combat_hud.h"
Acombat_hud::Acombat_hud(){
	static ConstructorHelpers::FObjectFinder<UTexture2D> crosshair_texture_object(TEXT("/Game/hud/crosshair_v1.crosshair_v1"));
	crosshair_texture = crosshair_texture_object.Object;
}
void Acombat_hud::DrawHUD() {
	Super::DrawHUD();
	if (crosshair_texture) {
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D CrossHairDrawPosition(Center.X - (crosshair_texture->GetSurfaceWidth() * 0.5f), Center.Y - (crosshair_texture->GetSurfaceHeight() * 0.5f));
		FCanvasTileItem TileItem(CrossHairDrawPosition, crosshair_texture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}