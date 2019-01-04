// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* GameStartButton; //게임 시작 버튼
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* CharacterDeleteButton; //캐릭터 삭제 버튼
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* CharacterCreateButton; //캐릭터 생성 버튼

	//유저가 소유하고 있는 게임 캐릭터 목록 (총 3개)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UCharacterSelectButton* CharacterButtonOne; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UCharacterSelectButton* CharacterButtonTwo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UCharacterSelectButton* CharacterButtonThree;

	class AChracterCreateSelectPC* PC;
	class ACharacterCreateSelectGameMode* CCSGM;
	virtual void NativeConstruct() override;

	UFUNCTION()
		void GameStart();
	UFUNCTION()
		void MyCharacterDelete();
	UFUNCTION()
		void MyCharacterCreate();
	void MyCharacterSlotUpdate(struct PacketData* _data);
	
	
	
};
