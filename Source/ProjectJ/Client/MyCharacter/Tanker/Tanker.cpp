// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanker.h"
//클라 헤더
#include "Components/SkeletalMeshComponent.h" // 메시
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Animation/AnimBlueprint.h" // 애님 블루프린트
#include "TankerAnimInstance.h" //탱커 애님 인스턴스 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
//서버 헤더

ATanker::ATanker()
{
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메시찾아 메쉬에 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_TankerMesh(TEXT("SkeletalMesh'/Game/Assets/Paragon/Chracter/ParagonTerra/Characters/Heroes/Terra/Meshes/Terra.Terra'"));
	if (SK_TankerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_TankerMesh.Object);
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

void ATanker::BeginPlay()
{
	Super::BeginPlay();

	TankerAnimInstance = Cast<UTankerAnimInstance>(GetMesh()->GetAnimInstance());

	if (TankerAnimInstance)
	{
		TankerAnimInstance->OnAttackEnded.AddDynamic(this, &ATanker::OnAttackMontageEnded);
		TankerAnimInstance->OnComboSave.AddDynamic(this, &ATanker::OnComboMontageSave);
		TankerAnimInstance->OnAttackHit.AddDynamic(this, &ATanker::OnAttackHit);
	}
}

void ATanker::ClickedReactionMontagePlay()
{
	if (TankerAnimInstance)
	{
		TankerAnimInstance->PlayClickedReactionMontage();
	}
}

void ATanker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATanker::LeftClick()
{
	if (IsAttack)
	{
		IsCombo = true;
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("탱커 상태에서 왼쪽 클릭")));
		IsAttack = true;

		if (TankerAnimInstance)
		{
			TankerAnimInstance->PlayAttackMontage();
			CurrentCombo += 1;
			TankerAnimInstance->JumpAttackMontageSection(CurrentCombo);
		}
	}
}

void ATanker::OnComboMontageSave()
{
	if (IsCombo)
	{
		GLog->Log(FString::Printf(TEXT("콤보 공격 시작함")));
		IsCombo = false;
		if (TankerAnimInstance)
		{
			TankerAnimInstance->PlayAttackMontage();
			CurrentCombo += 1;
			TankerAnimInstance->JumpAttackMontageSection(CurrentCombo);
		}
	}
}

void ATanker::OnAttackHit()
{
	TArray<TEnumAsByte<EObjectTypeQuery>>ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<FHitResult> HitResults;

	TArray<AActor*>IgonreActors;
	IgonreActors.Add(this);

	FVector TraceStart = GetActorLocation() + GetActorForwardVector()*100.0f;
	FVector TraceEnd = TraceStart + GetActorForwardVector()*100.0f;

	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		TraceStart,
		TraceEnd,
		140.0f,
		ObjectTypes,
		false,
		IgonreActors,
		EDrawDebugTrace::ForDuration,
		HitResults,
		true);

	for (int i = 0; i < HitResults.Num(); i++)
	{
		GLog->Log(FString::Printf(TEXT("%s"), *HitResults[i].BoneName.ToString()));
	}
}

float ATanker::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		GLog->Log(FString::Printf(TEXT("탱커 데미지 처리 함수 호출 데미지 : %f"), DamageAmount));
	}
	return DamageAmount;
}