﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
//클라 헤더
#include "MonsterAIController.h"
#include "Client/Monster/Manager/DistanceCheckAIManager.h"
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Components/CapsuleComponent.h"

//서버 헤더

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AMonsterAIController::StaticClass();

	DistanceCheckAIManager = CreateDefaultSubobject<UDistanceCheckAIManager>(TEXT("DistanceCheckAIManager"));

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	Tags.Add(TEXT("Monster"));
}

void AMonster::AttackHit()
{

}

void AMonster::Death()
{
	GLog->Log(FString::Printf(TEXT("부모 Dath 호출")));
	GetCapsuleComponent()->SetCollisionProfileName("OverlapOnlyPawn");
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonster::GetHP()
{
	return CurrentHP;
}



