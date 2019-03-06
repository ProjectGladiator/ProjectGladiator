// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Structure/FClickCharacterInfo.h"
#include "CharacterInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UCharacterInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* TradeButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* PartyButton;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		FClickCharacterInfo ClickCharacterSlotInfo;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void Trade();
	UFUNCTION()
		void Party();
};
