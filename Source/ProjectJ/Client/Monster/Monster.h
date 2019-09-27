// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetWork/MonsterInfo.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "GameFramework/Character.h"
#include "Client/Monster/Struct/MonsterAttackInfo.h"
#include "Monster.generated.h"

UCLASS()
class PROJECTJ_API AMonster : public ACharacter
{
	friend class AObjectPool;
	GENERATED_BODY()
public:
	AMonster();
protected:
	MONSTER_ATTACK_CODE m_MonsterAttackCode;
	//나 자신의 몬스터 코드
	MONSTER_CODE m_MonsterCode;
	//나의 몬스터 번호
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterCode)
		int m_MonsterNum;

	//Pool의 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ResetPosition)
		FVector m_PoolPos;
	//현재 위치
	UPROPERTY(VisibleAnywhere, Category = LocatPosition)
		FVector CurrentLocation;

	//현재 상태
	UPROPERTY(VisibleAnywhere, Category = stat)
		COMMON_MONSTER_STATE Current_Common_State;
	//현재 체력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat)
		float CurrentHP;

	//AI Property
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = AI)
		class UAIManager* AIManager;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
		float DeathInVisibleValue;

	//AttackProperty
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		float TargetLimitDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		FMonsterAttackInfo AttackInfo;

	//EffectProperty
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect)
		class UParticleSystem* HitEffectTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = true))
		class UParticleSystem* SpawnEffect;

	////제거해도 될지 않될지 모를값
	//UPROPERTY(VisibleInstanceOnly, Category = isDead)
	//	bool DeathFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ComboAttack)
		bool IsAttack; //공격중인지 아닌지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ComboAttack)
		bool IsCombo;  //콤보공격중인지 아닌지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ComboAttack)
		int32 CurrentCombo; //현재 콤보의 단계

	UFUNCTION()
		virtual void AttackHit();
	UFUNCTION()
		virtual void OnMonsterAttackEnded();
	UFUNCTION()
		virtual void OnComboSave();
	UFUNCTION()
		virtual void OnMonsterAttackChanged();
	UFUNCTION()
		virtual void Death();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Set Monster value initialize
	virtual void Init(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum);
	//virtual void Firstinit(MONSTER_CODE _MyMonsterCode, int _MyMonsterNum);

	UFUNCTION()
	float GetHP();
	UFUNCTION()
	void SetHP(float _currentHP);
	int SetMonsterNum(int);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
	class AMyCharacter* Target;
	/** Actor Hidden 확인여부 */
	UPROPERTY(VisibleInstanceOnly, Category = isSpawn)
	bool bisActive ;

	MONSTER_CODE SetMonsterCode(MONSTER_CODE);

	void Monster_SetActive(AMonster*, bool);

	void FirstTarget();

	void Targeting(char* _CharacterCode);

	void S2C_LocationUpdate(const FVector& _NewLocation);

	MONSTER_ATTACK_CODE GetMonsterAttackCode();
	MONSTER_CODE GetMonsterCode();
	int GetMonsterNum();

};

USTRUCT()
struct FActiveMonsterInfo
{
	GENERATED_USTRUCT_BODY()
	int MonsterNum;
	MONSTER_CODE MonsterCode;
	AMonster* Monster;
};