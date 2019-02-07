// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h"
#include "Client/Monster/Struct/MonsterAttackInfo.h"
#include "AIManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJ_API UAIManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//플레이어와의 거리를 재는 함수
	float DistanceCalculate(class AMonster* Monster, class AMyCharacter* Target);

	//플레이어를 쫓아가는 함수
	EPathFollowingRequestResult::Type TargetChase(class AMonsterAIController* MonsterAIController, class AMyCharacter* Target, float& TargetLimitDistance);	
	
	//근거리 공격판정 함수
	FHitResult AttackMeleeHitCreate(class AMonster* Monster, FMonsterAttackInfo& AttackInfo, bool RadialDamage);

	//원거리 공격판정 함수
	FHitResult AttackRangeHitCreate(class AMonster* Monster, float RangeDistance, const FName& SocketName, bool RadialDamage);
};
