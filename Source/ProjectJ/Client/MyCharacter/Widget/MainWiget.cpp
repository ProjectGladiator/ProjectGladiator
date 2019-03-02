// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWiget.h"
//클라 헤더
#include "Client/MyCharacter/Widget/Inventory/Widget/InventoryWidget.h"

//서버 헤더

void UMainWiget::NativeConstruct()
{
	InventoryWidget = Cast<UInventoryWidget>(GetWidgetFromName(TEXT("MyInventory")));
}
