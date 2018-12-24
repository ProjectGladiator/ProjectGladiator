// Fill out your copyright notice in the Description page of Project Settings.

#include "WinterGameInstance.h"

void UWinterGameInstance::Init()
{
	NetworkManager::CreateInstance();
	NetworkManager::GetInstance()->MangerInitialize();
	NetworkManager::GetInstance()->Initialize();
	NetworkManager::GetInstance()->InitializeSocket();
	//NetworkManager::GetInstance()->Connect();
}

void UWinterGameInstance::Shutdown()
{
	NetworkManager::GetInstance()->EndManager();
	NetworkManager::DestroyInstance();
}