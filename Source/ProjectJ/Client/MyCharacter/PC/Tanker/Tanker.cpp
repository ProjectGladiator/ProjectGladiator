
// Fill out your copyright notice in the Description page of Project Settings.

#include "Tanker.h"
//클라 헤더
#include "Components/SkeletalMeshComponent.h" // 메시
#include "UObject/ConstructorHelpers.h" // 경로 탐색
#include "Animation/AnimBlueprint.h" // 애님 블루프린트
#include "TankerAnimInstance.h" //탱커 애님 인스턴스 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일
#include "GameFramework/CharacterMovementComponent.h" //캐릭터 속력 관련 헤더파일
#include "Client/MainMap/MainMapPlayerController.h"
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

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_HitEffectMonster(TEXT("ParticleSystem'/Game/Assets/Paragon/Chracter/ParagonTerra/FX/Particles/Terra/Abilities/Primary/FX/P_Terra_Primary_Impact.P_Terra_Primary_Impact'"));

	if (PT_HitEffectMonster.Succeeded())
	{
		HitEffectMonster = PT_HitEffectMonster.Object;
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

	MyAnimInstance = Cast<UTankerAnimInstance>(GetMesh()->GetAnimInstance());

	if (MyAnimInstance)
	{
		MyAnimInstance->OnAttackEnded.AddDynamic(this, &ATanker::OnAttackMontageEnded);
		MyAnimInstance->OnComboSave.AddDynamic(this, &ATanker::OnComboMontageSave);
		MyAnimInstance->OnAttackHit.AddDynamic(this, &ATanker::OnAttackHit);
	}
}

void ATanker::ClickedReactionMontagePlay()
{
	if (MyAnimInstance)
	{
		MyAnimInstance->PlayClickedReactionMontage();
	}
}

void ATanker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GLog->Log(FString::Printf(TEXT("TimeSeconds : %f\nUnpausedTimeSeconds : %f\nRealTimeSeconds : %f\nDeltaTimeSeconds : %f"), GetWorld()->TimeSeconds, GetWorld()->UnpausedTimeSeconds, GetWorld()->RealTimeSeconds, GetWorld()->DeltaTimeSeconds));
	//GLog->Log(FString::Printf(TEXT("IsRightClick :%d \n IsAttack : %d"), IsRightClick,IsAttack));
}

void ATanker::LeftClick()
{
	Super::LeftClick();

	if (!IsRightClick && !MainMapPlayerController->bShowMouseCursor)
	{
		if (IsAttack)
		{
			IsCombo = true;
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("탱커 상태에서 왼쪽 클릭")));
			IsAttack = true;

			if (MyAnimInstance)
			{
				MyAnimInstance->PlayAttackMontage();
				CurrentCombo += 1;
				MyAnimInstance->JumpAttackMontageSection(CurrentCombo);
			}
		}
	}
}

void ATanker::RightClickOn()
{
	Super::RightClickOn();

	if (MainMapPlayerController)
	{
		if (!MainMapPlayerController->bShowMouseCursor)
		{
			GetCharacterMovement()->MaxWalkSpeed = 250.0f;
			GLog->Log(FString::Printf(TEXT("오른쪽 클릭")));
			MyAnimInstance->PlayRightClickAbilityMontage();
		}
	}
}

void ATanker::RightClickOff()
{
	Super::RightClickOff();

	if (MainMapPlayerController)
	{
		if (!MainMapPlayerController->bShowMouseCursor)
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
			MyAnimInstance->PlayStopRightClickAbilityMontage();
		}
	}
}

void ATanker::OnComboMontageSave()
{
	if (IsCombo)
	{
		GLog->Log(FString::Printf(TEXT("콤보 공격 시작함")));
		IsCombo = false;
		if (MyAnimInstance)
		{
			MyAnimInstance->PlayAttackMontage();
			CurrentCombo += 1;
			MyAnimInstance->JumpAttackMontageSection(CurrentCombo);
		}
	}
}

void ATanker::OnAttackHit()
{
	TArray<TEnumAsByte<EObjectTypeQuery>>ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<FHitResult> HitResults;
	FHitResult HirResult;
	TArray<AActor*>IgonreActors;
	IgonreActors.Add(this);
	
	FVector TraceStart = GetActorLocation() + GetActorForwardVector()*100.0f;
	FVector TraceEnd = TraceStart + GetActorForwardVector()*100.0f;

	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(),
		TraceStart,
		TraceEnd,
		140.0f,
		ObjectTypes,
		false,
		IgonreActors,
		EDrawDebugTrace::None,
		HirResult,
		true);
	
	GLog->Log(FString::Printf(TEXT("%s"),*HirResult.BoneName.ToString()));

	UGameplayStatics::ApplyDamage(
		HirResult.GetActor(),
		10.0f,
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		this,
		nullptr);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffectMonster, HirResult.ImpactPoint);


	/*UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		TraceStart,
		TraceEnd,
		140.0f,
		ObjectTypes,
		false,
		IgonreActors,
		EDrawDebugTrace::None,
		HitResults,
		true);

	for (int i = 0; i < HitResults.Num(); i++)
	{
		UGameplayStatics::ApplyDamage(
			HitResults[i].GetActor(),
			10.0f,
			UGameplayStatics::GetPlayerController(GetWorld(), 0),
			this,
			nullptr);
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffectMonster, HitResults[i].ImpactPoint);
	}*/
}

float ATanker::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);
		
		GLog->Log(FString::Printf(TEXT("탱커 데미지 범위 데미지 받음 : %f"), ActualDamage));
	}
	else if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);

		GLog->Log(FString::Printf(TEXT("탱커 데미지 포인트 데미지 받음 : %f"), ActualDamage));

		CurrentHP -= ActualDamage;
	}
	return DamageAmount;
}