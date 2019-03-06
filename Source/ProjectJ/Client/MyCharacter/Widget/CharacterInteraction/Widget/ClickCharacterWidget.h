// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Structure/FClickCharacterInfo.h"
#include "ClickCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UClickCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UCharacterInteractionWidget* CharacterInteractionWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* ClickCharacterButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* ClickCharacterNickNameText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* ClickCharacterHPText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* ClickCharacterMPText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UProgressBar* ClickCharacterHPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UProgressBar* ClickCharacterMPBar;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
		FClickCharacterInfo ClickCharacterSlotInfo;

	virtual void NativeConstruct() override;

	void SetClickCharacterInfo(FClickCharacterInfo& _ClickCharacterInfo);

	void ClickCharacterUpdate();

	FClickCharacterInfo GetClickCharacterSlotInfo();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void CharacterInteractionWidgetVisible();
	void CharacterInteractionWidgetHidden();

};
