// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
//클라 헤더
#include "MonsterAIController.h"
#include "Client/Monster/Manager/DistanceCheckAIManager.h"
//서버 헤더

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMonsterAIController::StaticClass();

	DistanceCheckAIManager = CreateDefaultSubobject<UDistanceCheckAIManager>(TEXT("DistanceCheckAIManager"));
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

