// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Client/State/MonsterState/MonsterState.h"
#include "Griffon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AGriffon : public AMonster
{
	GENERATED_BODY()
public:
	AGriffon();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controller, Meta = (AllowPrivateAccess = true))
		class AGriffonAIController* GriffonAIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EGriffonState CurrentState;
	UPROPERTY()
		class UGriffonAnimInstance* GriffonAnimInstance;
	UPROPERTY()
		float MaxHP;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void init() override;

	void SetAIController(class AMonsterAIController* NewAIController);

	EGriffonState GetCurrentState();
};
