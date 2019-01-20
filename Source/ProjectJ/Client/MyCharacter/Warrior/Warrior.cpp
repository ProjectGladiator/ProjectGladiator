// Fill out your copyright notice in the Description page of Project Settings.

#include "Warrior.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Animation/AnimBlueprint.h" //애니메이션블루프린트 헤더
#include "WarriorAnimInstance.h" //전사 애님 인스턴스 헤더
//서버 헤더

AWarrior::AWarrior()
{
	//에디터 상에서 스켈레탈메쉬를 찾아서 Warrior_SK_Mesh에 넣는다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Warrior_SK_Mesh(TEXT("SkeletalMesh'/Game/Assets/Paragon/Chracter/ParagonKhaimera/Characters/Heroes/Khaimera/Meshes/Khaimera.Khaimera'"));

	//찾는것에 성공하면
	if (Warrior_SK_Mesh.Succeeded())
	{
		//메쉬에 찾은 전사 메쉬를 넣어준다.
		GetMesh()->SetSkeletalMesh(Warrior_SK_Mesh.Object);
	}
		
	//메쉬의 위치와 각도를 조절해준다.
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//에디터 상에서 전사에 쓸 애니메이션 블루프린트를 찾아서 클래스 형식으로 ABP_Warrior에 넣어준다.
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Warrior(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/User/Warrior/Blueprints/ABP_Warrior.ABP_Warrior_C'"));

	if (ABP_Warrior.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* WarriorAnimBlueprint = ABP_Warrior.Object; //오브젝트를 구하고

		if (WarriorAnimBlueprint) 
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(WarriorAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}
}

void AWarrior::BeginPlay()
{
	Super::BeginPlay();

	WarriorAnimInstance = Cast<UWarriorAnimInstance>(GetMesh()->GetAnimInstance());

	if (WarriorAnimInstance)
	{
		WarriorAnimInstance->OnAttackEnded.AddDynamic(this, &AWarrior::OnAttackMontageEnded);
		WarriorAnimInstance->OnComboSave.AddDynamic(this, &AWarrior::OnComboMontageSave);
	}
}

void AWarrior::ClickedReactionMontagePlay()
{
	if (WarriorAnimInstance)
	{
		WarriorAnimInstance->PlayClickedReactionMontage();
	}	
}

void AWarrior::LeftClick()
{
	if (IsAttack)
	{
		IsCombo = true;
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("전사 상태에서 왼쪽 클릭")));
		IsAttack = true;
		
		if (WarriorAnimInstance)
		{
			WarriorAnimInstance->PlayAttackMontage();
			CurrentCombo += 1;
			WarriorAnimInstance->JumpAttackMontageSection(CurrentCombo);
		}
	}
}

void AWarrior::OnComboMontageSave()
{
	if (IsCombo)
	{
		GLog->Log(FString::Printf(TEXT("콤보 공격 시작함")));
		IsCombo = false;
		if (WarriorAnimInstance)
		{
			WarriorAnimInstance->PlayAttackMontage();
			CurrentCombo += 1;
			WarriorAnimInstance->JumpAttackMontageSection(CurrentCombo);
		}
	}
}
