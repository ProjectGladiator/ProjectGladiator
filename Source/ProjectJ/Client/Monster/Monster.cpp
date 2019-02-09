﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
//클라 헤더
#include "MonsterAIController.h"
#include "Client/Monster/Manager/AIManager.h"
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더

//서버 헤더

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AMonsterAIController::StaticClass();

	AIManager = CreateDefaultSubobject<UAIManager>(TEXT("AIManager"));

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	Tags.Add(TEXT("Monster"));
}

void AMonster::AttackHit()
{

}

void AMonster::OnMonsterAttackEnded()
{
	GLog->Log(FString::Printf(TEXT("IsAttack 초기화")));
	IsAttack = false; //false로 초기화
	IsCombo = false;
	CurrentCombo = 0; //콤보수 0으로 초기화
}

void AMonster::OnComboSave()
{

}

void AMonster::OnMonsterAttackChanged()
{

}

void AMonster::Death()
{

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



