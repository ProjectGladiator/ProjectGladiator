// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanker.h"

#include "Components/SkeletalMeshComponent.h"		// �޽�
#include "UObject/ConstructorHelpers.h"					// ��� Ž��
#include "Animation/AnimBlueprint.h"						// �ִ� �������Ʈ

ATanker::ATanker()
{
	PrimaryActorTick.bCanEverTick = true;

	// ���̷�Ż �޽�ã�� �޽��� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Mesh(TEXT("SkeletalMesh'/Game/Assets/Character/Tanker/dreyar_m_aure.dreyar_m_aure'"));	
	if (SM_Mesh.Succeeded()) 
	{
		GetMesh()->SetSkeletalMesh(SM_Mesh.Object); 
	}

	// �ִԺ������Ʈ ã�� �޽��� ����
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Tanker_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/Tanker/Blueprints/TankerAnimBlueprint.TankerAnimBlueprint'"));
	if (Tanker_AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Tanker_AnimBlueprint.Object->GeneratedClass);
	}

	// �޽��� ��ġ, ũ��, ���� ����
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}
