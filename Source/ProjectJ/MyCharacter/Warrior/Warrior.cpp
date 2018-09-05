// Fill out your copyright notice in the Description page of Project Settings.

#include "Warrior.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

AWarrior::AWarrior()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Warrior_SK_Mesh(TEXT("SkeletalMesh'/Game/Assets/Character/User/Warrior/Mesh/Male.Male'"));

	if (Warrior_SK_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Warrior_SK_Mesh.Object);
	}
}



