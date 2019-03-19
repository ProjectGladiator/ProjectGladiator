// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMapOtherPlayerController.h"
//클라 헤더
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"

//서버 헤더

AMainMapOtherPlayerController::AMainMapOtherPlayerController()
{

}

void AMainMapOtherPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainMapOtherPlayerController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
}
