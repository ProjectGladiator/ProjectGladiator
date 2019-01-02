// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleGameMode.h"
#include "Client/Title/TitlePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ATitleGameMode::ATitleGameMode()
{	
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = ATitlePlayerController::StaticClass();
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ATitleGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
