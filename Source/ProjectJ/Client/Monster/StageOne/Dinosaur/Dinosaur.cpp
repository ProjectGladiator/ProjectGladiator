// Fill out your copyright notice in the Description page of Project Settings.

#include "Dinosaur.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Animation/AnimBlueprint.h" // 애님 블루프린트
#include "DinosaurAnimInstance.h"

//서버 헤더

ADinosaur::ADinosaur()
{
	PrimaryActorTick.bCanEverTick = false;

	//// 스켈레탈 메시찾아 메쉬에 세팅
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_DinosaurMesh(TEXT("SkeletalMesh'/Game/Assets/Monster/ParagonMinions/Characters/Buff/Buff_Black/Meshes/Buff_Black.Buff_Black'"));
	//if (SK_DinosaurMesh.Succeeded())
	//{
	//	GetMesh()->SetSkeletalMesh(SK_DinosaurMesh.Object);
	//}
	//
	//// 애님블루프린트 찾아 메쉬에 세팅
	//	static ConstructorHelpers::FObjectFinder<UClass>ABP_Dinosaur(TEXT("AnimBlueprint'/Game/Blueprints/Monster/Dinosaur/Blueprints/ABP_Dinosaur.ABP_Dinosaur_C'"));

	//if (ABP_Dinosaur.Succeeded())  //찾는것에 성공햇으면
	//{
	//	UClass* DinosaurAnimBlueprint = ABP_Dinosaur.Object; //오브젝트를 구하고

	//	if (DinosaurAnimBlueprint)
	//	{
	//		//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
	//		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//		GetMesh()->SetAnimInstanceClass(DinosaurAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
	//	}
	//}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}
