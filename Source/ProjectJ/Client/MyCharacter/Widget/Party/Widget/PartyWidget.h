// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UPartyWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryWidget, Meta = (AllowPrivateAccess = true))
		TArray<class UPartySlotWiget*> PartySlotWigets;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryWidget, Meta = (AllowPrivateAccess = true))
		class UVerticalBox* VerticalPartySlots;
public:
	virtual void NativeConstruct() override;
		
};
