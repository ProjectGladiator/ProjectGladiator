
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
#include "Client/MainMap/MainMapPlayerController.h"//메인맵 플레이어 컨트롤러 헤더
#include "Client/Monster/Monster.h"
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

	MaxHP = 150.0f;
	CurrentHP = MaxHP;
	CurrentMP = 0;
}

void ATanker::BeginPlay()
{
	Super::BeginPlay();

	AttackSpeed = 1.0f;

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

	//GLog->Log(FString::Printf(TEXT("GetActorForwardVector %f"), GetActorForwardVector().X));
	//GLog->Log(FString::Printf(TEXT("TimeSeconds : %f\nUnpausedTimeSeconds : %f\nRealTimeSeconds : %f\nDeltaTimeSeconds : %f"), GetWorld()->TimeSeconds, GetWorld()->UnpausedTimeSeconds, GetWorld()->RealTimeSeconds, GetWorld()->DeltaTimeSeconds));
	//GLog->Log(FString::Printf(TEXT("IsRightClick :%d \n IsAttack : %d"), IsRightClick,IsAttack));
}

void ATanker::LeftClickOn()
{
	Super::LeftClickOn();

	if (MainMapPlayerController)
	{
		if (!IsRightClick && !MainMapPlayerController->bShowMouseCursor) // 오른쪽 클릭 상태가 아니고 커서가 보이지 않는 상황이면
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
					MyAnimInstance->PlayAttackMontage(AttackSpeed);
					CurrentCombo += 1;
					MyAnimInstance->JumpAttackMontageSection(CurrentCombo);
				}
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
	FHitResult HitResult;
	TArray<AActor*>IgonreActors;
	IgonreActors.Add(this);
	
	FVector TraceStart = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FVector TraceEnd = TraceStart + GetActorForwardVector() * 100.0f;

	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(),
		TraceStart,
		TraceEnd,
		140.0f,
		ObjectTypes,
		false,
		IgonreActors,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true);
	
	FVector CircleCollision = GetActorLocation() + GetActorForwardVector() * 200.0f;

	//GLog->Log(FString::Printf(TEXT("TraceStart %f %f %f"), TraceStart.X, TraceStart.Y, TraceStart.Z));
	//GLog->Log(FString::Printf(TEXT("TraceEnd %f %f %f"), TraceEnd.X, TraceEnd.Y, TraceEnd.Z));
	//GLog->Log(FString::Printf(TEXT("CircleCollision %f %f %f"), CircleCollision.X, CircleCollision.Y, CircleCollision.Z));

	//MainMapPlayerController->C2S_HitInfo(10001, 0, 1, CircleCollision.X, CircleCollision.Y, CircleCollision.Z);

	if (HitResult.GetActor())
	{
		AMonster* Monster = Cast<AMonster>(HitResult.GetActor());

		if (Monster)
		{
			if (MainMapPlayerController)
			{
				MainMapPlayerController->C2S_HitInfo(Monster->GetMonsterCode(), 0, 1, CircleCollision.X, CircleCollision.Y, CircleCollision.Z);
				GLog->Log(FString::Printf(TEXT("%d"), Monster->GetMonsterCode()));
			}
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("부딪힌 액터는 있으나 몬스터가 아님")));
		}

		GLog->Log(FString::Printf(TEXT("%s"), *HitResult.BoneName.ToString()));

		UGameplayStatics::ApplyDamage(
			HitResult.GetActor(),
			10.0f,
			UGameplayStatics::GetPlayerController(GetWorld(), 0),
			this,
			nullptr);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffectMonster, HitResult.ImpactPoint);
	}
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

void ATanker::MyTakeDamage(float _Damage)
{

}
