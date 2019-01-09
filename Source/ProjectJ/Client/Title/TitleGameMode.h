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
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UTitleWidgetUserIn* UserInWidget; //회원가입 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UTitleWidgetLogin* LoginWidget; //로그인 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UWidgetCancel* CancelWidget; //에러 다시시도,취소 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UWidgetOk* OkWidget; //에러 확인 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UUserWidget* LoadingWidget;
public:
	ATitleGameMode();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	

	void UserInWidgetToggle(); //회원가입 위젯 보여주기,끄기
	void LoginWidgetToggle(); //로그인 위젯 보여주기,끄기
	void CancelWidgetToggle(const FText& Message); //에러 다시시도,취소 위젯 보여주기
	void OkWidgetToggle(const FText& Message); //에러 확인 위젯 보여주기
	void LoadingWidgetViewScreen();

};
