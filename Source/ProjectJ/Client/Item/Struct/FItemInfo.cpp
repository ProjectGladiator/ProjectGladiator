// Fill out your copyright notice in the Description page of Project Settings.

#include "FItemInfo.h"

FItemInfo::FItemInfo()
{

}

FItemInfo::FItemInfo(int32 _ItemPrice,const FText& _ItemNameText, const EItemType& _ItemType, int32 _ItemMaxCount, int32 _EquipAbilityIncreasePoint, int32 _ConsumableIncreasePoint, class UTexture2D* _ItemThumbnail)
{
	IsActive = true;
	ItemPrice = _ItemPrice;
	ItemNameText = _ItemNameText;
	ItemType = _ItemType;
	ItemMaxCount = _ItemMaxCount;
	EquipAbilityIncreasePoint = _EquipAbilityIncreasePoint;
	ConsumableIncreasePoint = _ConsumableIncreasePoint;
	ItemThumbnail = _ItemThumbnail;
}

FItemInfo::~FItemInfo()
{
	
}