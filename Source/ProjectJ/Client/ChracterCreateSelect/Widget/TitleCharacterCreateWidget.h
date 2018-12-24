// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleCharacterCreateWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UTitleCharacterCreateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UEditableTextBox* NickNameInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* ChracterCreateButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* CancelButton;

	class AChracterCreateSelectPC* PC;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ChracterCreate();
	UFUNCTION()
	void Cancel();
};