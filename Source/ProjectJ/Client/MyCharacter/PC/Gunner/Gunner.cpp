// Fill out your copyright notice in the Description page of Project Settings.

#include "Gunner.h"
//클라 헤더
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 컴포넌트 헤더
#include "UObject/ConstructorHelpers.h" // 경로 탐색 헤더
#include "Animation/AnimBlueprint.h" //애니메이션 블루프린트 헤더
#include "GunnerAnimInstance.h" //총잡이 애님인스턴스 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
#include "Particles/ParticleSystem.h"  //파티클 관련 헤더 파일
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h" //카메라 컴포넌트 헤더파일
#include "GunnerCameraShake.h" //총잡이 카메라 흔들기
#include "GameFramework/SpringArmComponent.h" //스프링암 컴포넌트 헤더파일
#include "Client/MainMap/MainMapPlayerController.h"
#include "TimerManager.h"

//서버 헤더
AGunner::AGunner()
{
	PrimaryActorTick.bCanEverTick = true; //틱 활성화

	SpringArm->SetRelativeLocation(FVector(0, 83.0f, 108.0f)); //카메라 위치 조정

	//총잡이 메쉬를 에디터에서 찾아서 SK_GunnerMesh에 저장
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_GunnerMesh(TEXT("SkeletalMesh'/Game/Assets/Paragon/Chracter/ParagonLtBelica/Characters/Heroes/Belica/Meshes/Belica.Belica'"));

	//잘찾앗는지 확인
	if (SK_GunnerMesh.Succeeded())
	{
		//찾앗으면 메쉬에 찾은 총잡이 메쉬 셋팅
		GetMesh()->SetSkeletalMesh(SK_GunnerMesh.Object);
	}

	//총잡이 애니메이션블루프린트를 에디터에서 찾아서 Gunner_AnimBlueprint에 저장
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>Gunner_AnimBlueprint(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/User/Gunner/Blueprints/ABP_Gunner.ABP_Gunner'"));

	//잘찾앗는지 확인
	if (Gunner_AnimBlueprint.Succeeded())
	{
		//찾앚으면 메쉬의 애니메이션모드를 AnimationBlueprint로 셋팅
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		//위에서 찾은 총잡이 애니메이션블루프린트로 셋팅
		GetMesh()->SetAnimInstanceClass(Gunner_AnimBlueprint.Object->GeneratedClass);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_HitEffectMonster(TEXT("ParticleSystem'/Game/Assets/Paragon/Chracter/ParagonLtBelica/FX/Particles/Belica/Abilities/Primary/FX/P_BelicaHitCharacter.P_BelicaHitCharacter'"));

	if (PT_HitEffectMonster.Succeeded())
	{
		HitEffectMonster = PT_HitEffectMonster.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PT_HitEffectWorld(TEXT("ParticleSystem'/Game/Assets/Paragon/Chracter/ParagonLtBelica/FX/Particles/Belica/Abilities/Primary/FX/P_BelicaHitWorld.P_BelicaHitWorld'"));

	if (PT_HitEffectWorld.Succeeded())
	{
		HitEffectWorld = PT_HitEffectWorld.Object;
	}

	// 메시의 위치, 크기, 각도 설정
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

void AGunner::BeginPlay()
{
	Super::BeginPlay();

	AttackSpeed = 3.0f;

	MyAnimInstance = Cast<UGunnerAnimInstance>(GetMesh()->GetAnimInstance()); //총잡이 애님인스턴스를 구해서 GunnerAnimInstance에 저장

	if (MyAnimInstance) //null이 아니면
	{
		//OnAttackEnded( 공격 애니메이션 끝 ) 델리게이트를 이용해서 총잡이에 있는 OnAttackMontageEnded 연동
		MyAnimInstance->OnAttackEnded.AddDynamic(this, &AGunner::OnAttackMontageEnded);
		//OnComboSave( 콤보 저장 ) 델리게이트를 이용해서 총잡이에 있는 OnComboMontageSave 연동
		MyAnimInstance->OnComboSave.AddDynamic(this, &AGunner::OnComboMontageSave);
		MyAnimInstance->OnAttackHit.AddDynamic(this, &AGunner::OnAttackHit);
	}
}

void AGunner::ClickedReactionMontagePlay()
{
	if (MyAnimInstance) //총잡이 애님인스턴스가 null인지 확인
	{
		//제대로 있으면
		//캐릭터 선택 애니메이션 실행
		MyAnimInstance->PlayClickedReactionMontage();
	}
}

void AGunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//화면 중앙 크로스헤어 퍼짐이 0보다 크면
	if (CrossHairSpread > 0)
	{
		//0으로 다시 보간해주는 작업을 해준다.
		CrossHairSpread = FMath::FInterpTo(CrossHairSpread, 0, DeltaTime, 3.0f);
	}
}

void AGunner::LeftClickOn()
{
	Super::LeftClickOn();

	if (MainMapPlayerController)
	{
		if (!MainMapPlayerController->bShowMouseCursor)
		{
			IsRepeatShoot = true;
			MyAnimInstance->PlayAttackMontage(AttackSpeed);

			if (IsRepeatShoot)
			{
				GetWorld()->GetTimerManager().SetTimer(RepeatShootTimer, this, &AMyCharacter::LeftClickOn, 1.0f / AttackSpeed, true, 1.0f / AttackSpeed);
			}
		}
	}
}

void AGunner::LeftClickOff()
{
	IsRepeatShoot = false;
	GetWorld()->GetTimerManager().ClearTimer(RepeatShootTimer);
}

void AGunner::OnAttackHit()
{
	TArray<TEnumAsByte<EObjectTypeQuery>>ObjectTypes; //라인 트레이스에 감지되는 오브젝트들을 담는 배열을 선언한다.
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody)); // 피직스바디와
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic)); // 월드스테틱을 담는다.

	TArray<AActor*> IgnoreActors; //라인 트레이스에 무시되는 변수들을 담는 배열을 선언한다.
	IgnoreActors.Add(this); //자신을 등록한다.

	FHitResult HitResult;

	if (IsRightClick) //오른쪽 마우스 클릭 상태이면
	{
		//카메라에서 라인트레이스를 쏜다.

		//라인트레이스 시작 위치를 카메라의 월드위치로 초기화 시킨다.
		FVector TraceStart = Camera->GetComponentLocation();

		float RandomPitch = (FMath::FRandRange(CrossHairSpread*-1.0f, CrossHairSpread) / 7.0f);
		float RandomYaw = (FMath::FRandRange(CrossHairSpread*-1.0f, CrossHairSpread) / 7.0f);

		//CrossHairSpread값에 따라 랜덤하게 정해진 Pitch와 Yaw로 회전값을 만든다.
		FRotator CrossHairRotator = UKismetMathLibrary::MakeRotator(0, RandomPitch, RandomYaw);
		//카메라의 회전값에 앞줄에서 만들어준 회전값을 더한 값을 구한다.
		FRotator ComposeRotator = UKismetMathLibrary::ComposeRotators(Camera->GetComponentRotation(), CrossHairRotator);
		//더한 회전값의 앞쪽 방향의 벡터를 구해준다.
		FVector Dir = UKismetMathLibrary::Conv_RotatorToVector(ComposeRotator);

		//라인트레이스 끝 위치를 시작위치에서 앞에서 계산해준 방향쪽으로 9000.0f 만큼 곱한 곳으로 정한다.
		FVector TraceEnd = TraceStart + (Dir*9000.0f);

		//앞에서 계산해준 값을 토대로 라인트레이스를 쏜다.
		bool CameraTraceFlag = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
			TraceStart,
			TraceEnd,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true);

		//무엇인가가 맞으면
		if (CameraTraceFlag)
		{
			//그곳으로 총구에서 라인트레이스를 쏜다.

			//라인트레이스 시작 위치를 총구 앞의 위치로 삼고
			FVector CompleteTraceStart = GetMesh()->GetSocketLocation(TEXT("MuzzleStationary"));

			//시작점에서 맞은 곳을 바라보는 회전값을 구하고
			FRotator CompleteTraceEndRotator = UKismetMathLibrary::FindLookAtRotation(CompleteTraceStart, HitResult.ImpactPoint);

			//구한 회전값의 앞쪽 방향 벡터를 구한다.
			Dir = UKismetMathLibrary::Conv_RotatorToVector(CompleteTraceEndRotator);

			//라인트레이스 끝 위치를 시작위치에서 계산해준 방향쪽으로 9000.0f 만큼 곱한 곳으로 정한다.
			FVector CompleteTraceEnd = CompleteTraceStart + (Dir*9000.0f);

			//앞에서 계산해준 값을 토대로 라인트레이스를 쏜다.
			UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
				CompleteTraceStart,
				CompleteTraceEnd,
				ObjectTypes,
				false,
				IgnoreActors,
				EDrawDebugTrace::ForDuration,
				HitResult,
				true);
		}

		CrossHairSpread = 70.0f;
	}
	else
	{
		//오른쪽 마우스 클릭 상태가 아니면

		//라인트레이스 시작 위치를 총구 앞의 위치로 삼고
		FVector TraceStart = GetMesh()->GetSocketLocation(TEXT("MuzzleStationary"));

		//라인트레이스 끝 위치를 시작위치에서 캐릭터 앞쪽 방향으로 9000.0f 만큼 곱한 곳으로 정한다.
		FVector TraceEnd = TraceStart + GetActorForwardVector()*9000.0f;

		//앞에서 계산해준 값을 토대로 라인트레이스를 쏜다.
		UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
			TraceStart,
			TraceEnd,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true);
	}

	if (HitResult.Actor->IsValidLowLevel()) //맞은곳의 액터가 존재하는지 확인한다.
	{
		if (HitResult.Actor->ActorHasTag(TEXT("Monster"))) //맞은곳의 액터의 태그가 Monster이면
		{
			GLog->Log(FString::Printf(TEXT("몬스터 때림")));
			//파티클을 소환해주고
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffectMonster, HitResult.Location);

			//데미지를 적용시킨다.
			UGameplayStatics::ApplyDamage(
				HitResult.GetActor(),
				10.0f,
				UGameplayStatics::GetPlayerController(GetWorld(), 0),
				this,
				nullptr);
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("환경 때림")));
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffectWorld, HitResult.ImpactPoint);
		}
	}

	//카메라를 흔들어준다.
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->PlayCameraShake(UGunnerCameraShake::StaticClass());
}

float AGunner::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return DamageAmount;
}

float AGunner::GetCrossHairSpread()
{
	return CrossHairSpread;
}

