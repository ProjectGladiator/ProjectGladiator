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
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* CharacterSelectButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UTextBlock* CharacterNickName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UTextBlock* CharacterLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UTextBlock* ClassName;
	class AMainMapPlayerController* MainMapPlayerController = nullptr;
public:	

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void CharacterSelect();

	void CharacterInfoInput(const FText& NickName, const FText& Level, const FText& JobName);	
};
