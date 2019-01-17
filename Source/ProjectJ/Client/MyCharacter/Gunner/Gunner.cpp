// Fill out your copyright notice in the Description page of Project Settings.

#include "Gunner.h"
//클라 헤더
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/AnimBlueprint.h"
#include "GunnerAnimInstance.h"
//서버 헤더
AGunner::AGunner()
{
	PrimaryActorTick.bCanEverTick = false;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_GunnerMesh(TEXT("SkeletalMesh'/Game/Assets/Paragon/Chracter/ParagonLtBelica/Characters/Heroes/Belica/Meshes/Belica.Belica'"));

	if (SK_GunnerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_GunnerMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Gunner_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/User/Gunner/Blueprints/ABP_Gunner.ABP_Gunner'"));

	if (Gunner_AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Gunner_AnimBlueprint.Object->GeneratedClass);
	}

	// 메시의 위치, 크기, 각도 설정
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

void AGunner::BeginPlay()
{
	Super::BeginPlay();

	GunnerAnimInstance = Cast<UGunnerAnimInstance>(GetMesh()->GetAnimInstance());

	if (GunnerAnimInstance)
	{
		GunnerAnimInstance->OnAttackEnded.AddDynamic(this, &AGunner::OnAttackMontageEnded);
		GunnerAnimInstance->OnComboSave.AddDynamic(this, &AGunner::OnComboMontageSave);
	}
}

void AGunner::ClickedReactionMontagePlay()
{
	if (GunnerAnimInstance)
	{
		GunnerAnimInstance->PlayClickedReactionMontage();
	}	
}

void AGunner::LeftClick()
{
	if (IsAttack)
	{
		IsCombo = true;
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("총잡이 상태에서 왼쪽 클릭")));
		IsAttack = true;

		if (GunnerAnimInstance)
		{
			GunnerAnimInstance->PlayAttackMontage();
			CurrentCombo += 1;
			GunnerAnimInstance->JumpAttackMontageSection(CurrentCombo);
		}
	}
}

void AGunner::OnComboMontageSave()
{
	if (IsCombo)
	{
		GLog->Log(FString::Printf(TEXT("콤보 공격 시작함")));
		IsCombo = false;
		if (GunnerAnimInstance)
		{
			GunnerAnimInstance->PlayAttackMontage();
			CurrentCombo += 1;
			GunnerAnimInstance->JumpAttackMontageSection(CurrentCombo);
		}
	}
}
