// Fill out your copyright notice in the Description page of Project Settings.

#include "Wizard.h"

#include "Components/SkeletalMeshComponent.h"		// �޽�
#include "UObject/ConstructorHelpers.h"					// ��� Ž��
#include "Animation/AnimBlueprint.h"						// �ִ� �������Ʈ

AWizard::AWizard()
{
	PrimaryActorTick.bCanEverTick = true;

	// ���̷�Ż �޽�ã�� �޽��� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Mesh(TEXT("SkeletalMesh'/Game/Assets/Character/Wizard/pirate_p_konstantinov.pirate_p_konstantinov'"));
	if (SM_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Mesh.Object);
	}

	// �ִԺ������Ʈ ã�� �޽��� ����
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Wizard_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/Wizard/Blueprints/WizardAnimBlueprint.WizardAnimBlueprint'"));
	if (Wizard_AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(Wizard_AnimBlueprint.Object->GeneratedClass);
	}

	// �޽��� ��ġ, ũ��, ���� ����
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}



