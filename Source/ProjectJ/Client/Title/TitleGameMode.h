// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UTitleWidgetUserIn* UserInWidget; //ȸ������ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UTitleWidgetLogin* LoginWidget; //�α��� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UWidgetCancel* CancelWidget; //���� �ٽýõ�,��� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UWidgetOk* OkWidget; //���� Ȯ�� ����

	ATitleGameMode();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	

};
