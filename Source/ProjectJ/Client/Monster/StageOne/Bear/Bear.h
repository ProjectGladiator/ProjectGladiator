// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/Monster/Monster.h"
#include "Bear.generated.h"

UENUM(BlueprintType)
enum class EBearState : uint8
{
	Idle,
	Chase,
	Attack,
	Death
};

/**
 * 
 */
UCLASS()
class PROJECTJ_API ABear : public AMonster
{
	GENERATED_BODY()
public:
	ABear();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
		EBearState CurrentState;
public:
	virtual void Tick(float DeltaTime) override;
};
