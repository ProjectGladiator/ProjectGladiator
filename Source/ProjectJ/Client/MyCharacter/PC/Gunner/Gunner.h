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
public:
	AGunner(); //생성자
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ClickedReactionMontagePlay() override;	//캐릭터 생성창에서 선택시 실행할 애니메이션 함수

	UFUNCTION()
		virtual void LeftClick() override; // 마우스 왼쪽 클릭시 호출해줄 함수 ( 기본 공격 애니메이션 출력 )
	UFUNCTION()
		virtual void OnComboMontageSave() override; //콤보 공격 실행 함수
	UFUNCTION()
		virtual void OnAttackHit() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	float GetCrossHairSpread();
};
