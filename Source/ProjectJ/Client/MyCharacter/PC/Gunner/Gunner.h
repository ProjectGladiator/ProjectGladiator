// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Gunner.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AGunner : public AMyCharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect , Meta = (AllowPrivateAccess = true))
		class UParticleSystem* HitEffectMonster;  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = true))
		class UParticleSystem* HitEffectWorld;
	UPROPERTY()
		float CrossHairSpread;
	UPROPERTY()
		FTimerHandle RepeatShootTimer;
	UPROPERTY()
		bool IsRepeatShoot;
public:
	AGunner(); //생성자
	
	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay() override;	//캐릭터 생성창에서 선택시 실행할 애니메이션 함수
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void LeftClickOn() override; // 마우스 왼쪽 클릭시 호출해줄 함수 ( 기본 공격 애니메이션 출력 )
	UFUNCTION()
		virtual void LeftClickOff() override;
	UFUNCTION()
		virtual void OnAttackHit() override;

	float GetCrossHairSpread();

	virtual void MyTakeDamage(float _Damage, bool _IsLive) override;
};
