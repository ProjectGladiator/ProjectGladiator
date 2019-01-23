// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CharacterCreateSelectGameMode.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API ACharacterCreateSelectGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ErrorWidget", Meta = (AllowPrivateAccess = true))
		class UWidgetCancel* CancelWidget; //에러 다시시도,취소 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ErrorWidget", Meta = (AllowPrivateAccess = true))
		class UWidgetOk* OkWidget; //에러 확인 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UCharacterSelectWidget* CharacterSelectWidget;//캐릭터 선택 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UCharacterCreateWidget* ChracterCreateWidget; //캐릭터 생성 위젯
public:
	TArray <AActor*> Cameras;

	ACharacterCreateSelectGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void CharacterSelectWidgetToggle();
	void CharacterCreateWidgetToggle();

	void CancelWidgetToggle(const FText& Message); //에러 다시시도,취소 위젯 보여주기
	void OkWidgetToggle(const FText& Message); //에러 확인 위젯 보여주기
};
