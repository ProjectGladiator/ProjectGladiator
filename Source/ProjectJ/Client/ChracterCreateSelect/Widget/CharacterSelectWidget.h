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
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* GameStartButton; //게임 시작 버튼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* CharacterDeleteButton; //캐릭터 삭제 버튼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* CharacterCreateButton; //캐릭터 생성 버튼
											  //유저가 소유하고 있는 게임 캐릭터 목록 (총 3개)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterButtons, Meta = (AllowPrivateAccess = true))
		class UCharacterSelectButton* CharacterButtonOne;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterButtons, Meta = (AllowPrivateAccess = true))
		class UCharacterSelectButton* CharacterButtonTwo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterButtons, Meta = (AllowPrivateAccess = true))
		class UCharacterSelectButton* CharacterButtonThree;
	UPROPERTY()
		class AMainMapPlayerController* MainMapPlayerController;
	UPROPERTY()
		class AMainMapGameMode* MainMapGameMode;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void GameStart();
	UFUNCTION()
		void MyCharacterDelete();
	UFUNCTION()
		void MyCharacterCreate();

	void MyCharacterSlotUpdate(struct PacketData* _data);

	class UButton* GetGameStartButton();
	class UButton* GetChracterCreateButton();
};
