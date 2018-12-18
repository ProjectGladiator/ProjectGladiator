// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_RotationUpdate.h"
#include "Client/Header/MutantAIHeader.h"

void UBTTask_RotationUpdate::InitializeFromAsset(UBehaviorTree & Asset)
{
	Super::InitializeFromAsset(Asset);

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RotationUpdate::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_RotationUpdate::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());

		AActor* Player = Cast<AActor>(AI->BBComponent->GetValueAsObject(TEXT("Player")));

		if (Mutant && Player)
		{
			AMyCharacter* MyCharacter = Cast<AMyCharacter>(Player);
			FRotator LookAt, CurrentRot;

			if (MyCharacter)
			{
				LookAt = UKismetMathLibrary::FindLookAtRotation(Mutant->GetActorLocation(), MyCharacter->GetActorLocation());
				CurrentRot = FMath::Lerp(Mutant->GetActorRotation(), LookAt, 0.1f);

				Mutant->CurrentAnimState = EMonsterAnimState::Wait;
				Mutant->SetActorRotation(CurrentRot);
				
				if (UKismetMathLibrary::EqualEqual_RotatorRotator(CurrentRot, LookAt, 10.0f))
				{
					Mutant->CurrentState = EMonsterState::Battle;
					Mutant->CurrentAnimState = EMonsterAnimState::AttackReady;					
				}
			}
		}
	}
}
