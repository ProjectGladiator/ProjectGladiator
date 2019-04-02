// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/Widget/Party/Structure/FPartySlot.h"
#include "MainWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
		class UMenuWidget* MenuWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
		class UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		class UPartyWidget* PartyWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		class UPartyAcceptRejectWidget* PartyAcceptRejectWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		TArray<FPartySlot> PartySlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		int32 PartyMaxCount;
	UPROPERTY()
		class AMainMapGameMode* MainMapGameMode;
	UPROPERTY()
		class AMainMapPlayerController* MainMapPlayerController;
public:
	virtual void NativeConstruct() override;

	UMenuWidget* GetMenuWidget();

	void MenuWidgetToggle();

	UFUNCTION()
		void LogOut();
	UFUNCTION()
		void CharacterSelect();

	void ReadyCharacterSelectLogOut(const FName& _BindFunctionName); //메뉴에서 캐릭터 선택 or 로그아웃 선택시 뒷작업을 해주는 함수

	void PartyWidgetVisible();
	void PartyWidgetHidden();

	void PartyAcceptRejectWidgetVisible();
	void PartyAcceptRejectWidgetHidden();

	UPartyWidget* GetPartyWidget();
	UPartyAcceptRejectWidget* GetPartyAcceptRejectWidget();

	void PartyJoin(class AMyCharacter* _PartyInCharacter, char* _CharacterCode, int32 _JobCode, char* _NickName, float _HP, float _MP, bool _Leader);
	void PartyKick(char* _CharacterCode);
	void PartyLeave();
	void PartyLeave(char* _CharacterCode);
	void PartyLeaderUpdate();

	bool IsPartyJoin();
	int32 GetPartySize();

	UFUNCTION()
		void MapLoadComplete(); //스트리밍 레벨 로드 완료시 호출하는 함수	
	UFUNCTION()
		void MainMapUnLoadCompleteToTitle(); //메인 맵 스트리밍 레벨 언로드 완료시 호출하는 함수
	UFUNCTION()
		void MainMapUnLoadCompleteToCharacterSelect(); //메인 맵 스트리밍 레벨 언로드 완료시 호출하는 함수
};
