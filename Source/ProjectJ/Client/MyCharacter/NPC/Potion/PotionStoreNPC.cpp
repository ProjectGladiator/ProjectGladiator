// Fill out your copyright notice in the Description page of Project Settings.

#include "PotionStoreNPC.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Client/MyCharacter/NPC/Widget/StoreInventory/StoreInventory.h"
//서버 헤더

APotionStoreNPC::APotionStoreNPC()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Mesh(TEXT("SkeletalMesh'/Game/Assets/Character/NPC/PotionStore/Mesh/claire.claire'"));
	if (SM_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Mesh.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));	
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UClass>ABP_PotionStore(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/NPC/PotionStore/Blueprints/ABP_PotionStoreNPC.ABP_PotionStoreNPC_C'"));

	if (ABP_PotionStore.Succeeded())
	{
		UClass* PotionStoreAnimBlueprint = ABP_PotionStore.Object;

		if (PotionStoreAnimBlueprint)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(PotionStoreAnimBlueprint);
		}
	}
}

void APotionStoreNPC::BeginPlay()
{
	Super::BeginPlay();

	if (StoreInventoryComponent)
	{
		StoreInventoryComponent->PotionStoreInventoryCreate();
	}
}
