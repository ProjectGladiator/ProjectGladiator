// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChannelChange.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UChannelChange : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		class UUniformGridPanel* ChannelChangeGrid;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		class UButton* ChannelChangeBackButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		TArray<class UChannelChangeSlot*> ChannelChangeSlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		float RowColumnValue;
public:
	virtual void NativeConstruct() override;

	void CreateChannelChange();
	void ChannelUpdate(int32 _ChannelNum);
	UFUNCTION()
		void ChannChangeWidgetHidden();
};
