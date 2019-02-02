// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMapGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AMainMapGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		class UTitleWidgetUserIn* UserInWidget; //회원가입 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserLoginWidget, Meta = (AllowPrivateAccess = true))
		class UTitleWidgetLogin* LoginWidget; //로그인 위젯

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterCreateSelectWidget, Meta = (AllowPrivateAccess = true))
		class UCharacterSelectWidget* CharacterSelectWidget;//캐릭터 선택 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterCreateSelectWidget, Meta = (AllowPrivateAccess = true))
		class UCharacterCreateWidget* ChracterCreateWidget; //캐릭터 생성 위젯

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ErrorWidget, Meta = (AllowPrivateAccess = true))
		class UWidgetCancel* CancelWidget; //에러 다시시도,취소 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ErrorWidget, Meta = (AllowPrivateAccess = true))
		class UWidgetOk* OkWidget; //에러 확인 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LogdingWidget, Meta = (AllowPrivateAccess = true))
		class UUserWidget* LoadingWidget; //로딩 위젯

public:
	AMainMapGameMode();

	TArray <AActor*> Cameras;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void UserInWidgetToggle(); //회원가입 위젯 보여주기,끄기
	void LoginWidgetToggle(); //로그인 위젯 보여주기,끄기
	void CharacterSelectWidgetToggle(); //캐릭터 선택창 위젯 보여주기, 끄기
	void CharacterCreateWidgetToggle(); //캐릭터 생성창 위젯 보여주기, 끄기
	void CancelWidgetToggle(const FText& Message); //에러 다시시도,취소 위젯 보여주기
	void OkWidgetToggle(const FText& Message); //에러 확인 위젯 보여주기
	void LoadingWidgetViewScreen();
	
	UFUNCTION()
		void MapLoadComplete();
	void MainMapSpawnCharacterPossess(class AMyCharacter* _MyCharacter);
};
