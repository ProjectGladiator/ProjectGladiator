// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanker.h"

#include "Components/SkeletalMeshComponent.h"		// 메시
#include "UObject/ConstructorHelpers.h"					// 경로 탐색
#include "Animation/AnimBlueprint.h"						// 애님 블루프린트

ATanker::ATanker()
{
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메시찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Mesh(TEXT("SkeletalMesh'/Game/Assets/Character/Tanker/dreyar_m_aure.dreyar_m_aure'"));	
	if (SM_Mesh.Succeeded()) 
	{
		GetMesh()->SetSkeletalMesh(SM_Mesh.Object); 
	}

	// 애님블루프린트 찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Tanker_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/Tanker/Blueprints/TankerAnimBlueprint.TankerAnimBlueprint'"));
	if (Tanker_AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Tanker_AnimBlueprint.Object->GeneratedClass);
	}

	// 메시의 위치, 크기, 각도 설정
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}
