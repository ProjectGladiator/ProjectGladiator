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
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UEditableTextBox* IDInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UEditableTextBox* PWInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UEditableTextBox* PWCheckInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* IDOverlapCheckButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* UserInButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* CancelButton;

	class ATitlePlayerController* PC;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Cancel();
	UFUNCTION()
	void IdOverapCheck();
	UFUNCTION()
	void Join();

};
