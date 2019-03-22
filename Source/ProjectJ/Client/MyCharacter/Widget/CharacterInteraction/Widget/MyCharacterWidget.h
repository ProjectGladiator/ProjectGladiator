// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Structure/FClickCharacterInfo.h"
#include "MyCharacterWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UMyCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UCharacterInteractionWidget* CharacterInteraction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* MyCharacterButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UProgressBar* MyCharacterHPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UProgressBar* MyCharacterMPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* MyCharacterHPText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* MyCharacterMPText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* MyCharacterNickName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		FClickCharacterInfo MyCharacterSlotInfo;
public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void SetInit(class AMyCharacter* _MyCharacter, APlayerController* _PlayerController);

	void HPUpdate();
	void MPUpdate();

	FClickCharacterInfo GetMyCharacterSlotInfo();

	void CharacterInteractionWidgetVisible();
	void CharacterInteractionWidgetHidden();

	void SetPosition(FVector2D _Position);
};
