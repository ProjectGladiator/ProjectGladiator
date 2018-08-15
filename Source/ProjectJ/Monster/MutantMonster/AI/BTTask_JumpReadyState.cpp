// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_JumpReadyState.h"
#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"

EBTNodeResult::Type UBTTask_JumpReadyState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		Mutant = Cast<AMutantMonster>(AI->GetPawn());

		if (Mutant)
		{
			float Distance = AI->BBComponent->GetValueAsFloat("Distance");

			if (Distance >= 2000.0f)
			{
				Mutant->CurrentAnimState = EMonsterAnimState::JumpAttack;
				Mutant->CurrentJumpState = EMonsterJumpState::JumpStart;
			}
			else
			{
				//���� �ִϸ��̼� ���߿� ���� �ִϸ��̼��� �ٽ� �Ǻ��Ǽ� 
				//���� �ִϸ��̼��� �����ϳ� ���� �ص尡 ȣ���� �ȵǾ �ٽ� �Ǵ��� �ȵ�.
				int JumpRunValue = FMath::RandRange(1, 10);

				if (JumpRunValue <= 3)
				{
					Mutant->CurrentAnimState = EMonsterAnimState::JumpAttack;
					Mutant->CurrentJumpState = EMonsterJumpState::JumpStart;
				}
				else
				{
					Mutant->CurrentAnimState = EMonsterAnimState::Run;
					Mutant->CurrentJumpState = EMonsterJumpState::Idle;
				}

				if (Mutant->CurrentAnimState == EMonsterAnimState::Run)
				{
					GetWorld()->GetTimerManager().SetTimer(RunTimer, this, &UBTTask_JumpReadyState::JumpRunCheck, 5.0f, false);
				}
				UE_LOG(LogClass, Warning, TEXT("Random Value : %d"), JumpRunValue);
			}			
		}
	}
	return EBTNodeResult::Succeeded;
}

void UBTTask_JumpReadyState::JumpRunCheck()
{
	if (Mutant)
	{
		Mutant->JumpRunCheckFlag = true;
	}
}