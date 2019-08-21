// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Client/Monster/StageTwo/HammerBoss/BruteAIController.h"
#include "Brute.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ABrute : public AMonster
{
	GENERATED_BODY()
public :
	ABrute();
	virtual void Tick(float DeltaTime) override;
	virtual void Init(MONSTER_CODE __MyMonsterCode, int _MyMonsterNum) override;

	void SetAIController(class AMonsterAIController* NewAIController);

	//EBruteState GetCurrnetState();
	//EBruteAttackState GetCurrentAttackState();

	//UFUNCTION()
	//	virtual void AttackHit() override;
	//UFUNCTION()
	//	virtual void OnComboSave() override;
	//UFUNCTION()
	//	virtual void OnMonsterAttackEnded() override;
	//UFUNCTION()
	//	virtual void OnMonsterAttackChanged() override;
	//UFUNCTION()
	//	virtual void Death() override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
	class ABruteAIController* BruteAIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EBruteState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EBruteAttackState CurrentAttackState;
	UPROPERTY()
		class UBruteAnimInstance* BruteAnimInstance; //####### AnimInstance 확인할 것 #######
	UPROPERTY()
		float MaxHP;
	//wchar_t* SK_Address;
	/*wchar_t* AnimBP_Address;*/
public:
	EBruteState GetCurrnetState();
	EBruteAttackState GetCurrentAttackState();
};
