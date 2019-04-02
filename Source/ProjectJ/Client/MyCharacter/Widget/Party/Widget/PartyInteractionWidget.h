// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/Widget/Party/Structure/FPartySlot.h"
#include "PartyInteractionWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UPartyInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UBorder* NickNameTextBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* NickNameText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* PartyLeaderDelegateButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* PartyKickButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* PartyExitButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		FPartySlot PartySlotInfo;
public:
	virtual void NativeConstruct() override;

	void SetPartyInteractionWidget(bool _IsMyPartySlot, FPartySlot& _PartySlotInfo);

	UFUNCTION()
		void PartyLeaderDelegate();
	UFUNCTION()
		void PartyKick();
	UFUNCTION()
		void PartyLeave();
};
