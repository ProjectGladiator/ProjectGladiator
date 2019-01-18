// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
//클라 헤더
#include "MyCharacter.h"
#include "MyPlayerController.h"
//서버 헤더

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass(); //기본 폰을 캐릭터의 부모캐릭터로 설정
	PlayerControllerClass = AMyPlayerController::StaticClass(); //기본 플레이어컨트롤러를 MyPlayerController로 설정
}
