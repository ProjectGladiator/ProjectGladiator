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
	PrimaryActorTick.bCanEverTick = false; //틱 비활성화
	
	//총잡이 메쉬를 에디터에서 찾아서 SK_GunnerMesh에 저장
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_GunnerMesh(TEXT("SkeletalMesh'/Game/Assets/Paragon/Chracter/ParagonLtBelica/Characters/Heroes/Belica/Meshes/Belica.Belica'"));

	//잘찾앗는지 확인
	if (SK_GunnerMesh.Succeeded())
	{
		//찾앗으면 메쉬에 찾은 총잡이 메쉬 셋팅
		GetMesh()->SetSkeletalMesh(SK_GunnerMesh.Object);
	}

	//총잡이 애니메이션블루프린트를 에디터에서 찾아서 Gunner_AnimBlueprint에 저장
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Gunner_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/User/Gunner/Blueprints/ABP_Gunner.ABP_Gunner'"));

	//잘찾앗는지 확인
	if (Gunner_AnimBlueprint.Succeeded())
	{
		//찾앚으면 메쉬의 애니메이션모드를 AnimationBlueprint로 셋팅
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		//위에서 찾은 총잡이 애니메이션블루프린트로 셋팅
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

	GunnerAnimInstance = Cast<UGunnerAnimInstance>(GetMesh()->GetAnimInstance()); //총잡이 애님인스턴스를 구해서 GunnerAnimInstance에 저장

	if (GunnerAnimInstance) //null이 아니면
	{
		//OnAttackEnded( 공격 애니메이션 끝 ) 델리게이트를 이용해서 총잡이에 있는 OnAttackMontageEnded 연동
		GunnerAnimInstance->OnAttackEnded.AddDynamic(this, &AGunner::OnAttackMontageEnded);
		//OnComboSave( 콤보 저장 ) 델리게이트를 이용해서 총잡이에 있는 OnComboMontageSave 연동
		GunnerAnimInstance->OnComboSave.AddDynamic(this, &AGunner::OnComboMontageSave);
	}
}

void AGunner::ClickedReactionMontagePlay()
{
	if (GunnerAnimInstance) //총잡이 애님인스턴스가 null인지 확인
	{
		//제대로 있으면
		//캐릭터 선택 애니메이션 실행
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
