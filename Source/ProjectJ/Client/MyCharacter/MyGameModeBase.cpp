// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
//클라 헤더
#include "MyCharacter.h"
#include "MyPlayerController.h"
//서버 헤더

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
