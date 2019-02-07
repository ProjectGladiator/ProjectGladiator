// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidgetUserIn.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UTitleWidgetUserIn : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UEditableTextBox* IDInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UEditableTextBox* PWInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UEditableTextBox* PWCheckInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* IDOverlapCheckButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* UserInButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* CancelButton;
	UPROPERTY()
		class AMainMapPlayerController* MainMapPlayerController;
	UPROPERTY()
		class AMainMapGameMode* MainMapGameMode;
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void Cancel();
	UFUNCTION()
		void IdOverapCheck();
	UFUNCTION()
		void Join();

};
