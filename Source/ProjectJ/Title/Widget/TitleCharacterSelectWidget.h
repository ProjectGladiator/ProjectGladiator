// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleCharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UTitleCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	class ATitlePlayerController* PC;
	virtual void NativeConstruct() override;
};
