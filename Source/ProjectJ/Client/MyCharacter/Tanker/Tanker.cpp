﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanker.h"
//클라 헤더
#include "Components/SkeletalMeshComponent.h" // 메시
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Animation/AnimBlueprint.h" // 애님 블루프린트
//서버 헤더

ATanker::ATanker()
{
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메시찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_TankerMesh(TEXT("SkeletalMesh'/Game/Assets/Paragon/Chracter/ParagonTerra/Characters/Heroes/Terra/Meshes/Terra.Terra'"));	
	if (SM_TankerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_TankerMesh.Object);
	}

	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Tanker_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/User/Tanker/Blueprints/ABP_Tanker.ABP_Tanker'"));
	if (Tanker_AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Tanker_AnimBlueprint.Object->GeneratedClass);
	}

	// 메시의 위치, 크기, 각도 설정
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}
