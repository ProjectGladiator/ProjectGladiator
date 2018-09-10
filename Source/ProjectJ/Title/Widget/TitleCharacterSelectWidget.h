// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleCharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UTitleCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* GameStartButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* CharacterDelete;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* CharacterCreate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UCharacterSelectButton* CharacterButtonOne;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UCharacterSelectButton* CharacterButtonTwo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UCharacterSelectButton* CharacterButtonThree;

	class ATitlePlayerController* PC;
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void GameStart();
	UFUNCTION()
	void MyCharacterDelete();
	UFUNCTION()
		void MyCharacterCreate();
};
