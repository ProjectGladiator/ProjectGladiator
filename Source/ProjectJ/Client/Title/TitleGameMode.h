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
		class UTitleWidgetUserIn* UserInWidget; //회원가입 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UTitleWidgetLogin* LoginWidget; //로그인 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UWidgetCancel* CancelWidget; //에러 다시시도,취소 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UWidgetOk* OkWidget; //에러 확인 위젯

	ATitleGameMode();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	

};
