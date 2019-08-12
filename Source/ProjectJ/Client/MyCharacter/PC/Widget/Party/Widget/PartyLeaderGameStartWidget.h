// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyLeaderGameStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UPartyLeaderGameStartWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Button, Meta = (AllowPrivateAccess = true))
		class UButton* PartyLeaderGameStartButton;
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
		void PartyLeaderGameStartButtonClick();
};
