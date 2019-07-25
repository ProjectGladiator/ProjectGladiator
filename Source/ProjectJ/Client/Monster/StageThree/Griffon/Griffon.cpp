// Fill out your copyright notice in the Description page of Project Settings.

#include "Griffon.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h" //경로 탐색 헤더
#include "GriffonAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"

//서버 헤더

AGriffon::AGriffon()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AGriffonAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Griffon(TEXT("SkeletalMesh'/Game/Assets/Monster/QuadrapedCreatures/Griffon/Meshes/SK_Griffon.SK_Griffon'"));

	if (SK_Griffon.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Griffon.Object);
	}

	static ConstructorHelpers::FObjectFinder<UClass>ABP_Griffon(TEXT("AnimBlueprint'/Game/Blueprints/Monster/StageThree/Griffon/ABP_Griffon.ABP_Griffon_C'"));

	if (ABP_Griffon.Succeeded())
	{
		UClass* GriffonAnimBlueprint = ABP_Griffon.Object; //오브젝트를 구하고

		if (GriffonAnimBlueprint)
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(GriffonAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	DeathFlag = false;
	MaxHP = 100.0f;
}

void AGriffon::BeginPlay()
{
	Super::BeginPlay();
}

void AGriffon::Tick(float DeltaTime)
{

}

void AGriffon::Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum)
{
	Super::Init(_MyMonsterCode, _MyMonsterNum);
}

void AGriffon::SetAIController(AMonsterAIController * NewAIController)
{

}

EGriffonState AGriffon::GetCurrentState()
{
	return CurrentState;
}
