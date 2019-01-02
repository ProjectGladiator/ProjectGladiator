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
public:
	TArray <AActor*> Cameras;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UTitleCharacterSelectWidget* CharacterSelectWidget;//캐릭터 선택 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UTitleCharacterCreateWidget* ChracterCreateWidget; //캐릭터 생성 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UWidgetCancel* CancelWidget; //에러 다시시도,취소 위젯
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
		class UWidgetOk* OkWidget; //에러 확인 위젯

	ACharacterCreateSelectGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void CharacterSelectWidgetToggle();
	void CharacterCreateWidgetToggle();
};
