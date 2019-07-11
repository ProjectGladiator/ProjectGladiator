// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/PC/Widget/Party/Structure/FPartySlot.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UPartyInteractionWidget* PartyInteraction;
public:
	virtual void NativeConstruct() override;

	UPartySlotWiget* PartySlotCreate();

	void SetPartyInteraction(bool _IsMyPartySlot, FPartySlot& _PartySlotInfo);

	UPartyInteractionWidget* GetPartyInteraction();

	void PartyInteractionWidgetVisible();
	void PartyInteractionWidgetHidden();

	void PartyLeave();
	void PartyLeave(char* _CharacterCode);
	void PartySlotUIUpdate(char* _PartyUserCode,int _Type);
	void PartyLeaderUpdate();
};
