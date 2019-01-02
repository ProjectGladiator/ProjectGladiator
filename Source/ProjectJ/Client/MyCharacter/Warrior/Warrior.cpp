// Fill out your copyright notice in the Description page of Project Settings.

#include "Warrior.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimBlueprint.h"
#include "Components/CapsuleComponent.h"
//서버 헤더

AWarrior::AWarrior()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Warrior_SK_Mesh(TEXT("SkeletalMesh'/Game/Assets/Character/User/Warrior/Mesh/Male.Male'"));

	if (Warrior_SK_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Warrior_SK_Mesh.Object);
	}
		
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UClass>ABP_Warrior(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/User/Warrior/Blueprints/ABP_Warrior.ABP_Warrior_C'"));

	if (ABP_Warrior.Succeeded()) 
	{
		UClass* WarriorAnimBlueprint = ABP_Warrior.Object;

		if (WarriorAnimBlueprint)
		{
			
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(WarriorAnimBlueprint); 
		}
	}
}

void AWarrior::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("WarriorClick")));
	OnClicked.AddDynamic(this, &AWarrior::WarriorMouseClicked);
}

void AWarrior::WarriorMouseClicked(AActor* TouchedActor, FKey ButtonPressed)
{	
	if (ButtonPressed == EKeys::LeftMouseButton)
	{
		GLog->Log(FString::Printf(TEXT("마우스 클릭")));
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("클릭")));
	}
}