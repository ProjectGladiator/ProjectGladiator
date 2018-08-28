// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcherMonster.h"


// Sets default values
AArcherMonster::AArcherMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArcherMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArcherMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArcherMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

