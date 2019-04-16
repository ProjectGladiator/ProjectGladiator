// Fill out your copyright notice in the Description page of Project Settings.

#include "StoreInventorySlotWidget.h"

void UStoreInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UStoreInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		GLog->Log(FString::Printf(TEXT("���� ������ ������ Ŭ��")));
	}

	return FReply::Handled();
}
