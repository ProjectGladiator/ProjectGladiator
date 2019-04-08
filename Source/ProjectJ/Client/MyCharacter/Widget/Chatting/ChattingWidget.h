// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChattingWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UChattingWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UComboBoxString* ChannelListBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UEditableTextBox* ChattingInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UScrollBox* ChattingScrollBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		TArray<class UChattingMessageWidget*> ChattingMessages;
public:
	virtual void NativeConstruct() override;

	void ChattingStart();
	UFUNCTION()
		void ChattingSend(const FText& Text, ETextCommit::Type CommitMethod);
};
