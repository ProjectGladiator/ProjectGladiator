// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleGameMode.h"
#include "Client/Title/TitlePlayerController.h"

ATitleGameMode::ATitleGameMode()
{	
	PlayerControllerClass = ATitlePlayerController::StaticClass();
}