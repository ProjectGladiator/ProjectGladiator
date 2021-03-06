﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacterNickNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UMyCharacterNickNameWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* CharacterNickNameText;
public:
	virtual void NativeConstruct() override;

	void SetCharacterNickNameToWidget(char* _MyCharacterNick);
};
