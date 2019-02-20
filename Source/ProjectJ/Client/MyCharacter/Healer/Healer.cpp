// Fill out your copyright notice in the Description page of Project Settings.

#include "Healer.h"
//클라 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 컴포넌트 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Animation/AnimBlueprint.h" //애니메이션 블루프린트 헤더

//서버 헤더
AHealer::AHealer()
{
	PrimaryActorTick.bCanEverTick = true; //틱 활성화

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_HealerMesh(TEXT("SkeletalMesh'/Game/Assets/Paragon/Chracter/ParagonDekker/Characters/Heroes/Dekker/Meshes/Dekker.Dekker'"));

	//잘찾앗는지 확인
	if (SK_HealerMesh.Succeeded())
	{
		//찾앗으면 메쉬에 찾은 총잡이 메쉬 셋팅
		GetMesh()->SetSkeletalMesh(SK_HealerMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Healer_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/User/Healer/Blueprints/ABP_Healer.ABP_Healer'"));

	//잘찾앗는지 확인
	if (Healer_AnimBlueprint.Succeeded())
	{
		//찾앚으면 메쉬의 애니메이션모드를 AnimationBlueprint로 셋팅
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		//위에서 찾은 총잡이 애니메이션블루프린트로 셋팅
		GetMesh()->SetAnimInstanceClass(Healer_AnimBlueprint.Object->GeneratedClass);
	}

	// 메시의 위치, 크기, 각도 설정
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

void AHealer::BeginPlay()
{
	Super::BeginPlay();
}
