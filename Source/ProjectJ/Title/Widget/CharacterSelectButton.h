// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UCharacterSelectButton : public UUserWidget
{
	GENERATED_BODY()
public:
	//UPROPERTY(VisibleAnywhere,BleurpintReadWrite,Category = "CharacerInfo")

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* CharacterSelectButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UTextBlock* CharacterNickName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UTextBlock* CharacterLevel;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UTextBlock* ClassName;

	class ATitlePlayerController* PC;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void CharacterSelect();

	void CharacterInfoInput(const FText& NickName, const FText& Level, const FText& JobName);	
};
