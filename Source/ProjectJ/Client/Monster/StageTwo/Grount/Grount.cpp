// Fill out your copyright notice in the Description page of Project Settings.

#include "Grount.h"
#pragma region ClientHeader
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "GrountAIController.h" //AI 컨트롤러 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Client/Monster/Manager/AIManager.h" //AI담당 컴포넌트 헤더
#include "Client/MyCharacter/PC/MyCharacter.h" //캐릭터들 부모
#include "GameFrameWork/CharacterMovementComponent.h" //캐릭터 속도 관련 헤더
#include "GrountAnimInstance.h" //애님 인스턴스 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
#include "Kismet/KismetMathLibrary.h" //수학 관련 헤더
#include "Components/CapsuleComponent.h" //캡슐 컴포넌트 헤더
#pragma endregion 클라이언트 헤더

#pragma region ServerHeader
//Some ServerHeader
#pragma endregion 서버 헤더

#pragma region SkeletalMesh Set
#pragma endregion 스켈레탈 메쉬 세팅

#pragma region AnimBlueprint Set
#pragma endregion 애님 블루프린트 메쉬 세팅

#pragma region Mesh Set To World pos
#pragma endregion 매쉬를 월드에 적용하기 위한 위치값

#pragma region HP, TagetLimit_Distance, AttackRange, State Set
#pragma endregion 수치로 표현되는 초기화 값 모음

