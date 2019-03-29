// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageWidget.h"
//클라 헤더
#include "Components/TextBlock.h"

//서버 헤더

void UDamageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TakeDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TakeDamage")));
}
