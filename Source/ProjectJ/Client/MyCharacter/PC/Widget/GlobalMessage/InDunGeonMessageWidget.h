// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InDunGeonMessageWidget.generated.h"

UENUM(BlueprintType)
enum class EMessageState : uint8
{
	InDunGeon,
	GameStageStart
};

/**
 *
 */
UCLASS()
class PROJECTJ_API UInDunGeonMessageWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
		EMessageState MessageState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* MessageText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* InDunGeonAcceptButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* InDunGeonCancelButton;
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void InDunGeonAccept();
	UFUNCTION()
		void InDunGeonCancel();

	void SetMessageState(const EMessageState& _NewState, const FText & _NewMessage);
};
