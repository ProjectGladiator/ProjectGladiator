// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChattingMessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UChattingMessageWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* ChattingMessageText;
public:
	virtual void NativeConstruct() override;

	void ChattingMessageSet(const FText& _ChattingMessage);
};
