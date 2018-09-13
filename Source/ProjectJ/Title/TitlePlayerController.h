// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API ATitlePlayerController : public APlayerController
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
	
	virtual void BeginPlay() override;

	void UserInWidgetToggle(); //회원가입 위젯 보여주기,끄기
	void LoginWidgetToggle(); //로그인 위젯 보여주기,끄기
	void CancelWidgetToggle(const FText& Message); //에러 다시시도,취소 위젯 보여주기
	void OkWidgetToggle(const FText& Message); //에러 확인 위젯 보여주기
};
