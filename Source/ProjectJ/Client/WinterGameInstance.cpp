// Fill out your copyright notice in the Description page of Project Settings.

#include "WinterGameInstance.h"
//클라 헤더

//서버 헤더
#include "NetWork/NetworkManager.h"

using namespace NetworkClient_main;

void UWinterGameInstance::Init()
{
	NetworkManager::CreateInstance();
	NetworkManager::GetInstance()->MangerInitialize();
	NetworkManager::GetInstance()->Initialize();
	NetworkManager::GetInstance()->InitializeSocket();
}

void UWinterGameInstance::Shutdown()
{
	NetworkManager::GetInstance()->EndManager();
	NetworkManager::DestroyInstance();
}

