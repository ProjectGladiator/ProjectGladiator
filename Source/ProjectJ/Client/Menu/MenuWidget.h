// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE(FLogOutDelegate);
DECLARE_DYNAMIC_DELEGATE(FCharacterSelectDelegate);

UCLASS()
class PROJECTJ_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MenuButton, Meta = (AllowPrivateAccess = true))
		class UChannelChange* ChannelChangeWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MenuButton, Meta = (AllowPrivateAccess = true))
		class UButton* ChannelChangeButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MenuButton, Meta = (AllowPrivateAccess = true))
		class UButton* CharacterSelectButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MenuButton, Meta = (AllowPrivateAccess = true))
		class UButton* LogOutButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MenuButton, Meta = (AllowPrivateAccess = true))
		class UButton* GameExitButton;
public:
	FLogOutDelegate OnLogOut;
	FCharacterSelectDelegate OnCharacterSelect;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void ChannelChange();
	UFUNCTION()
		void CharacterSelect();
	UFUNCTION()
		void LogOut();
	UFUNCTION()
		void GameExit();

	void ChannelChangeWidgetVisible();
	void ChannelChangeWidgetHidden();

	UChannelChange* GetChannelChangeWidget();
};
