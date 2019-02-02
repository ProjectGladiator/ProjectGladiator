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
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UEditableTextBox* IDInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UEditableTextBox* PWInputBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* LoginButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* UserInButton;

	class AMainMapPlayerController* MainMapPlayerController =nullptr;
	class AMainMapGameMode* MainMapGameMode =nullptr;
	FTimerHandle LoadingTimer;
public:	
	virtual void NativeConstruct() override;	

	UFUNCTION()
		void UserIn();
	UFUNCTION()
		void Login();
	UFUNCTION()
		void ToCharacterSelectLevel();
};
