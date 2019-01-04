// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidgetLogin.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UTitleWidgetLogin : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UEditableTextBox* IDInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UEditableTextBox* PWInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* LoginButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* UserInButton;

	class ATitlePlayerController* PC;
	class ATitleGameMode* TitleGM;
	virtual void NativeConstruct() override;
	FTimerHandle LoadingTimer;

	UFUNCTION()
		void UserIn();
	UFUNCTION()
		void Login();
	UFUNCTION()
		void ToCharacterSelectLevel();
};
