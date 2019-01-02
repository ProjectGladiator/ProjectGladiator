// Fill out your copyright notice in the Description page of Project Settings.

#include "TitlePlayerController.h"

void ATitlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true; //마우스 커서가 화면에 보이게 해준다.
	SetInputMode(FInputModeUIOnly()); //게임의 모드를 UIOnly로 설정한다.
}