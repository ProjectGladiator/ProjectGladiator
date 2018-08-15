// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_StateUpdate.h"
#include "Monster/MutantMonster/MutantAIController.h"
#include "Monster/MutantMonster/MutantMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

void UBTService_StateUpdate::InitializeFromAsset(UBehaviorTree & Asset)
{
	Super::InitializeFromAsset(Asset);

	AttackDistance = 280.0f;
	AddRange = 1500.0f;
}

void UBTService_StateUpdate::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	FRotator ZeroRotator = FRotator::ZeroRotator;

	AMutantAIController* AI = Cast<AMutantAIController>(OwnerComp.GetAIOwner());

	if (AI)
	{
		AMutantMonster* Mutant = Cast<AMutantMonster>(AI->GetPawn());
		
		AActor* Player = Cast<AActor>(AI->BBComponent->GetValueAsObject(TEXT("Player")));

		if (Mutant && Player)
		{
			Distance = FVector::Distance(Mutant->GetActorLocation(), Player->GetActorLocation());
			AI->BBComponent->SetValueAsFloat("Distance", Distance);

			if (Mutant->CurrentFalling == false && Mutant->IsParrying ==false)
			{
				switch (Mutant->CurrentState)
				{
				case EMonsterState::Dead:
					Mutant->GetCharacterMovement()->MaxWalkSpeed = 0;
					break;
				case EMonsterState::Idle:
					Mutant->GetCharacterMovement()->MaxWalkSpeed = 250.0f;
					break;
				case EMonsterState::Chase:
					if (Distance > AddRange)
					{
						if (Mutant->JumpRunCheckFlag)
						{
							Mutant->CurrentAnimState = EMonsterAnimState::JumpAttackReady;
							Mutant->JumpRunCheckFlag = false;
						}
					}
					else if (Distance <= 1200.0f) //ĳ���Ϳ��� �Ÿ��� 12M�����ε�
					{
						if (Mutant->CurrentAnimState == EMonsterAnimState::JumpAttack) //ĳ���Ͱ� �������¶��
						{
							if (Mutant->JumpEndFlag == true) //������ ���� ���¶��
							{
								Mutant->JumpEndFlag = false;
								Mutant->CurrentAnimState = EMonsterAnimState::Run;
							}
						}
						else
						{
							Mutant->CurrentAnimState = EMonsterAnimState::Run;

							if (Distance <= 400.0f)
							{
								Mutant->CurrentAnimState = EMonsterAnimState::Walk;

								if (Distance < AttackDistance)
								{
									Mutant->CurrentAnimState = EMonsterAnimState::Wait;
									Mutant->CurrentState = EMonsterState::Rotate;
								}
							}
						}
					}

					switch (Mutant->CurrentAnimState)
					{
					case EMonsterAnimState::Wait:
						Mutant->GetCharacterMovement()->MaxWalkSpeed = 0;
						break;
					case EMonsterAnimState::Walk:
						Mutant->GetCharacterMovement()->MaxWalkSpeed = 250.0f;
						break;
					case EMonsterAnimState::Run:
						Mutant->GetCharacterMovement()->MaxWalkSpeed = 500.0f;
						break;
					case EMonsterAnimState::JumpAttack:
						Mutant->GetCharacterMovement()->MaxWalkSpeed = 250.0f;
						break;
					case EMonsterAnimState::Roar:
						Mutant->GetCharacterMovement()->MaxWalkSpeed = 0;
						break;
					case EMonsterAnimState::Parrying:
						Mutant->GetCharacterMovement()->MaxWalkSpeed = 0;
						break;						
					}
					break;
				case EMonsterState::Battle:
					if (Distance > 450.0f)
					{
						Mutant->CurrentState = EMonsterState::Chase;
						Mutant->CurrentAnimState = EMonsterAnimState::Run;
					}
					break;
				case EMonsterState::Rotate:
					if (Distance > 300.0f)
					{
						Mutant->CurrentState = EMonsterState::Chase;
						Mutant->CurrentAnimState = EMonsterAnimState::Run;
					}
					break;
				}
			}			
		}
	}
}
