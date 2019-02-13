// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StageManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJ_API UStageManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStageManager();
private:
	UPROPERTY()
		class AMonster* CurrentSpawnMonster;
	UPROPERTY()
		int32 CurrentSpawnMonsterCount;
	UPROPERTY()
		int32 StageLevel;
	UPROPERTY()
		class UParticleSystem* SpawnEffect;
	UPROPERTY()
		FTimerHandle SpawnTimerHandle;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetSpawnMonsterInfo(class AMonster* _Monster, int32 _Count);

	void SpawnStart();

	UFUNCTION()
		void Spawn();
};
