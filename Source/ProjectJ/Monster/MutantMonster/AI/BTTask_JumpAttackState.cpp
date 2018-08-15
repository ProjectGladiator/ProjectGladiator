// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_JumpAttackState.h"
#include "Kismet/KismetMathLibrary.h"

#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"

void UBTTask_JumpAttackState::InitializeFromAsset(UBehaviorTree & Asset)
{
	Super::InitializeFromAsset(Asset);
	bNotifyTick = true;
	CurrentFalling = false;
	PreviousFalling = false;
}

EBTNodeResult::Type UBTTask_JumpAttackState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		Mutant = Cast<AMutantMonster>(AI->GetPawn());
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_JumpAttackState::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
		
	if (Mutant)
	{
		FFindFloorResult FloorDistance;
		CurrentFalling = Mutant->CurrentFalling;
		if (CurrentFalling && PreviousFalling)
		{
			Mutant->CurrentJumpState = EMonsterJumpState::JumpLoop;
		}
		
		if (!CurrentFalling && PreviousFalling)
		{
			Mutant->GetCharacterMovement()->ComputeFloorDist(Mutant->GetCapsuleComponent()->GetComponentLocation(), 10000.0f, 10000.0f, FloorDistance, 34.0f);

			if (FloorDistance.FloorDist < 250.0f)
			{
				Mutant->CurrentJumpState = EMonsterJumpState::JumpLand;	
				Mutant->JumpRunCheckFlag = true; //점프 판별 다시 가능하게
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
		PreviousFalling = CurrentFalling;
	}
}

