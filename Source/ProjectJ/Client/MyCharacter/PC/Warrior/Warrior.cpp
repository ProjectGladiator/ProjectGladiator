// Fill out your copyright notice in the Description page of Project Settings.

#include "Warrior.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h" //스켈레탈 메쉬 헤더
#include "Animation/AnimBlueprint.h" //애니메이션블루프린트 헤더
#include "WarriorAnimInstance.h" //전사 애님 인스턴스 헤더
#include "Kismet/KismetSystemLibrary.h"  //라인 트레이스 헤더 관련 헤더
#include "Client/MainMap/MainMapPlayerController.h" //메인맵 플레이어 컨트롤러 헤더
#include "Client/Monster/Monster.h"

//서버 헤더

AWarrior::AWarrior()
{
	//에디터 상에서 스켈레탈메쉬를 찾아서 Warrior_SK_Mesh에 넣는다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Warrior_SK_Mesh(TEXT("SkeletalMesh'/Game/Assets/Paragon/Chracter/ParagonKhaimera/Characters/Heroes/Khaimera/Meshes/Khaimera.Khaimera'"));

	//찾는것에 성공하면
	if (Warrior_SK_Mesh.Succeeded())
	{
		//메쉬에 찾은 전사 메쉬를 넣어준다.
		GetMesh()->SetSkeletalMesh(Warrior_SK_Mesh.Object);
	}
		
	//메쉬의 위치와 각도를 조절해준다.
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//에디터 상에서 전사에 쓸 애니메이션 블루프린트를 찾아서 클래스 형식으로 ABP_Warrior에 넣어준다.
	static ConstructorHelpers::FObjectFinder<UClass>ABP_Warrior(TEXT("AnimBlueprint'/Game/Blueprints/MyCharacter/User/Warrior/Blueprints/ABP_Warrior.ABP_Warrior_C'"));

	if (ABP_Warrior.Succeeded())  //찾는것에 성공햇으면
	{
		UClass* WarriorAnimBlueprint = ABP_Warrior.Object; //오브젝트를 구하고

		if (WarriorAnimBlueprint) 
		{
			//메쉬에 사용할 애니메이션을 블루프린트로 정한다.
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimInstanceClass(WarriorAnimBlueprint);  //찾은 애니메이션블루프린트를 넣어준다.
		}
	}
}

void AWarrior::BeginPlay()
{
	Super::BeginPlay();

	AttackSpeed = 1.0f;

	MyAnimInstance = Cast<UWarriorAnimInstance>(GetMesh()->GetAnimInstance());

	if (MyAnimInstance)
	{
		MyAnimInstance->OnAttackEnded.AddDynamic(this, &AWarrior::OnAttackMontageEnded);
		MyAnimInstance->OnComboSave.AddDynamic(this, &AWarrior::OnComboMontageSave);
		MyAnimInstance->OnAttackHit.AddDynamic(this, &AWarrior::OnAttackHit);
	}
}

void AWarrior::ClickedReactionMontagePlay()
{
	if (MyAnimInstance)
	{
		MyAnimInstance->PlayClickedReactionMontage();
	}	
}

void AWarrior::LeftClickOn()
{
	Super::LeftClickOn();

	if (MainMapPlayerController)
	{
		if (!MainMapPlayerController->bShowMouseCursor)
		{
			if (IsAttack)
			{
				IsCombo = true;
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("전사 상태에서 왼쪽 클릭")));
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

void AWarrior::RightClickOn()
{

}

void AWarrior::OnComboMontageSave()
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

void AWarrior::OnAttackHit()
{
	TArray<TEnumAsByte<EObjectTypeQuery>>ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<FHitResult> HitResults;

	TArray<AActor*>IgonreActors;
	IgonreActors.Add(this);

	FVector TraceStart = GetActorLocation() + GetActorForwardVector()*100.0f;
	FVector TraceEnd = TraceStart + GetActorForwardVector()*40.0f;


	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		TraceStart,
		TraceEnd,
		100.0f,
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

void AWarrior::MyTakeDamage(float _Damage, bool _IsLive)
{
	
}
