// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Client/MyCharacter/MyCharacter.h"
#include "Tanker.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API ATanker : public AMyCharacter
{
	GENERATED_BODY()
private:
	UPROPERTY()
		class UTankerAnimInstance* TankerAnimInstance;
public:
	ATanker();

	virtual void BeginPlay() override;
	virtual void ClickedReactionMontagePlay() override;

	UFUNCTION()
		virtual void LeftClick() override;
	UFUNCTION()
		virtual void OnComboMontageSave() override;
};
