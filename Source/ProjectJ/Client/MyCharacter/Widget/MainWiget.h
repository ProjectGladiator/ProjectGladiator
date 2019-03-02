// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWiget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UMainWiget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UInventoryWidget* InventoryWidget;
public:
	virtual void NativeConstruct() override;


};
