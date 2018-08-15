// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AttackReadyState.h"

#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"

#include "Engine/World.h"
#include "TimerManager.h"

#include "UObject/ConstructorHelpers.h"

EBTNodeResult::Type UBTTask_AttackReadyState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			int RandomAttack = FMath::RandRange(1, 10);

			//attack1 (�и� ���� ������ ���) attack2   attack3 (���� �����ϴ� ���ݸ�� ���� �и��� ����)
			//40%							  30%       30%

			if (RandomAttack <= 4)
			{
				Mutant->CurrentAttackState = EMonsterAttackState::ParryingAttack;
				Mutant->CurrentAnimState = EMonsterAnimState::Wait;
			}
			else if (RandomAttack > 4 && RandomAttack < 8)
			{
				Mutant->CurrentAttackState = EMonsterAttackState::DefaultAttack;
				Mutant->CurrentAnimState = EMonsterAnimState::Wait;
			}
			else
			{
				Mutant->CurrentAttackState = EMonsterAttackState::ParryingAttack;
				Mutant->CurrentAnimState = EMonsterAnimState::Wait;
			}
		}
	}
	return EBTNodeResult::Succeeded;
}
