// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterWidget.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
//서버 헤더

void UMyCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyCharacterButton = Cast<UButton>(GetWidgetFromName(TEXT("MyCharacterButton")));
	MyCharacterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MyCharacterHPBar")));
	MyCharacterMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MyCharacterMPBar")));
	MyCharacterHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterHPText")));
	MyCharacterMPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterMPText")));
	MyCharacterNickName = Cast<UTextBlock>(GetWidgetFromName(TEXT("MyCharacterNickName")));
}

void UMyCharacterWidget::SetInit(AMyCharacter* _MyCharacter)
{
	MyCharacter = _MyCharacter;

	if (MyCharacterNickName)
	{
		
	}
}

void UMyCharacterWidget::HPUpdate()
{

}

void UMyCharacterWidget::MPUpdate()
{

}

