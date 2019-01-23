// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WinterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UWinterGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	int32 SelectCharacterIndex;
public:
	virtual void Init() override;
	virtual void Shutdown() override;
	
	int32 GetSelectCharacterIndex();
	void SetSelectCharacterIndex(int32 NewIndex);
	
};
