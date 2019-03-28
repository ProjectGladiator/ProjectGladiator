// Fill out your copyright notice in the Description page of Project Settings.

#include "Grount.h"
#pragma region ClientHeader
#include "UObject/ConstructorHelpers.h" // ��� Ž�� ���
#include "GrountAIController.h" //AI ��Ʈ�ѷ� ���
#include "Components/SkeletalMeshComponent.h" //���̷�Ż �޽� ���
#include "Kismet/GameplayStatics.h" //���� ��ƿ ���
#include "Client/Monster/Manager/AIManager.h" //AI��� ������Ʈ ���
#include "Client/MyCharacter/PC/MyCharacter.h" //ĳ���͵� �θ�
#include "GameFrameWork/CharacterMovementComponent.h" //ĳ���� �ӵ� ���� ���
#include "GrountAnimInstance.h" //�ִ� �ν��Ͻ� ���
#include "Kismet/KismetSystemLibrary.h"  //���� Ʈ���̽� ��� ���� ���
#include "Kismet/KismetMathLibrary.h" //���� ���� ���
#include "Components/CapsuleComponent.h" //ĸ�� ������Ʈ ���
#pragma endregion Ŭ���̾�Ʈ ���

#pragma region ServerHeader
//Some ServerHeader
#pragma endregion ���� ���

#pragma region SkeletalMesh Set
#pragma endregion ���̷�Ż �޽� ����

#pragma region AnimBlueprint Set
#pragma endregion �ִ� �������Ʈ �޽� ����

#pragma region Mesh Set To World pos
#pragma endregion �Ž��� ���忡 �����ϱ� ���� ��ġ��

#pragma region HP, TagetLimit_Distance, AttackRange, State Set
#pragma endregion ��ġ�� ǥ���Ǵ� �ʱ�ȭ �� ����

