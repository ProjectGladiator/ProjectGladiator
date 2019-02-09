// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GunnerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AGunnerHUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CrossHairTexture, Meta = (AllowPrivateAccess = true))
		class UTexture2D* CrossHairUpDown; //화면 가운데의 조준점을 그려줄 텍스쳐
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CrossHairTexture, Meta = (AllowPrivateAccess = true))
		class UTexture2D* CrossHairLeftRight; //화면 가운데의 조준점을 그려줄 텍스쳐
	bool ShowCrossHair;
public:
	AGunnerHUD();
	UFUNCTION()
		virtual void DrawHUD() override;
};
