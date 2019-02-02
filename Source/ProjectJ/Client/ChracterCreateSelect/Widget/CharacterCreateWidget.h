// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCreateWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UCharacterCreateWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UEditableTextBox* NickNameInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* ChracterCreateButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* CancelButton;
	class AMainMapPlayerController* MainMapPlayerController = nullptr;
	class AMainMapGameMode* MainMapGameMode = nullptr;
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void ChracterCreate();
	UFUNCTION()
		void Cancel();

	class UButton* GetChracterCreateButton();
};
