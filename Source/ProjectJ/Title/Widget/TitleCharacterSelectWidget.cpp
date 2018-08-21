// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleCharacterSelectWidget.h"
#include "Components/Button.h"
#include "Title/Widget/CharacterSelectButton.h"
#include "Kismet/GameplayStatics.h"
#include "Title/TitlePlayerController.h"

void UTitleCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStart")));
	CharacterDelete = Cast<UButton>(GetWidgetFromName(TEXT("CharacterDelete")));
	CharacterButtonOne = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonOne")));
	CharacterButtonTwo = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonTwo")));
	CharacterButtonThree = Cast<UCharacterSelectButton>(GetWidgetFromName(TEXT("CharacterSelectButtonThree")));

	
	if (GameStartButton)
	{
		GameStartButton->OnClicked.AddDynamic(this, &UTitleCharacterSelectWidget::GameStart);
	}

	if (CharacterDelete)
	{
		CharacterDelete->OnClicked.AddDynamic(this, &UTitleCharacterSelectWidget::MyCharacterDelete);
	}	
	
	PC = Cast<ATitlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}	

void UTitleCharacterSelectWidget::GameStart()
{
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainStage")); //타이틀 맵으로 이동			
	}	
}

void UTitleCharacterSelectWidget::MyCharacterDelete()
{

}
