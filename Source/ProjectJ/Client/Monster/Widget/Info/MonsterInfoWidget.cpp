// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterInfoWidget.h"
//클라 헤더
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

//서버 헤더

void UMonsterInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MonsterNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MonsterNameText")));
	MonsterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MonsterHPBar")));
}
