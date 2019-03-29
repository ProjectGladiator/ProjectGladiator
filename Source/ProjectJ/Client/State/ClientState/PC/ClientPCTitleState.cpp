// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientPCTitleState.h"
//서버 헤더

//클라 헤더

ClientPCTitleState::ClientPCTitleState()
{
	GLog->Log(FString::Printf(TEXT("클라이언트 플레이어 컨트롤러 선택 상태 생성자 출력")));
}

ClientPCTitleState::~ClientPCTitleState()
{
	GLog->Log(FString::Printf(TEXT("클라이언트 플레이어 컨트롤러 선택 상태 소멸자 출력")));
}

void ClientPCTitleState::Tick(float _DeltaTime)
{
	//GLog->Log(FString::Printf(TEXT("클라이언트 플레이어 컨트롤러 선택 상태 틱")));
}
