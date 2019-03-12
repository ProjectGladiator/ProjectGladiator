// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/Menu/ChannelChange/Structure/FChannelInfo.h"
#include "ChannelChangeSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UChannelChangeSlot : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		int32 ChannelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		class UButton* ChannelChangeSlotButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		class UTextBlock* ChannelNameText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		class UProgressBar* ChannelCongestionBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		FChannelInfo ChannelInfo;
public:
	virtual void NativeConstruct() override;
	
	void SetChannelInfo(class AMainMapGameMode* _MainMapGameMode);

	void InitChannelSlot(int32 _ChannelIndex);

	void ChannelSlotUpdate();
};
