// Fill out your copyright notice in the Description page of Project Settings.

#include "Potion.h"
//클라 헤더
#include "Client/Item/DataTable/DataTableComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
//서버 헤더

APotion::APotion()
{
	ItemInfo.ItemName = FText::FromString(FString::Printf(TEXT("체력포션")));
	ItemInfo.ItemExplanation = FText::FromString(FString::Printf(TEXT("체력을 일정량 만큼 회복해주는 물약")));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_RedPotion(TEXT("StaticMesh'/Game/Assets/Item/Potion/Mesh/RedPotion.RedPotion'"));

	if (SM_RedPotion.Succeeded())
	{
		Mesh->SetStaticMesh(SM_RedPotion.Object);
	}
		
	if (Sphere)
	{
		Sphere->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	}
	//ItemInfo.ItemMesh=
}

void APotion::BeginPlay()
{
	Super::BeginPlay();
	
	
}
