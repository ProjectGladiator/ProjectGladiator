// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/PC/Widget/Party/Structure/FPartySlot.h"
#include "Client/MyCharacter/PC/Widget/Inventory/Structure/FInventorySlot.h"
#include "Client/MyCharacter/PC/Widget/GlobalMessage/InDunGeonMessageWidget.h"
#include "MainWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GlobalMessageWidget, Meta = (AllowPrivateAccess = true))
		class UTextBlock* InChannelText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GlobalMessageWidget, Meta = (AllowPrivateAccess = true))
		class UTextBlock* InGameStageStartText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GlobalMessageWidget, Meta = (AllowPrivateAccess = true))
		class UInDunGeonMessageWidget* InDunGeonMessageWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MenuWidget, Meta = (AllowPrivateAccess = true))
		class UMenuWidget* MenuWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryWidget, Meta = (AllowPrivateAccess = true))
		class UInventoryWidget* InventoryWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryWidget, Meta = (AllowPrivateAccess = true))
		int32 InventoryMaxCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryWidget, Meta = (AllowPrivateAccess = true))
		TArray<FInventorySlot> Slots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		class UPartyWidget* PartyWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		class UPartyAcceptRejectWidget* PartyAcceptRejectWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		TArray<FPartySlot> PartySlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		int32 PartyMaxCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ChattingWidget, Meta = (AllowPrivateAccess = true))
		class UChattingWidget* ChattingWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ChattingWidget, Meta = (AllowPrivateAccess = true))
		class UPartyLeaderGameStartWidget* PartyLeaderGameStartWidget;

	UPROPERTY()
		class AMainMapGameMode* MainMapGameMode;
	UPROPERTY()
		class AMainMapPlayerController* MainMapPlayerController;
	UPROPERTY()
		class UWidgetAnimation* InChannelTextInVisibleAnimation;
	UPROPERTY()
		FTimerHandle GameStageStartTimer;
	UPROPERTY()
		int32 GameStageStartCount;
public:
	virtual void NativeConstruct() override;

	/*
		메뉴 관련 함수
	*/
	UMenuWidget* GetMenuWidget();

	void MenuWidgetToggle();

	UFUNCTION()
		void LogOut();
	UFUNCTION()
		void CharacterSelect();

	void ReadyCharacterSelectLogOut(const FName& _BindFunctionName); //메뉴에서 캐릭터 선택 or 로그아웃 선택시 뒷작업을 해주는 함수

	/*
		가방 관련 함수
	*/

	void InventoryCreate(int32 _NewInventoryMaxCount); //가방을 생성 매개변수 수만큼
	void InventoryWidgetToggle();

	void MoneyUpdate(int32 _GetMoney);

	/*
		파티 관련 함수
	*/
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
	FPartySlot GetPartySlot(int32 _Index);

	//파티장 게임 시작 버튼 토글함수
	void PartyLeaderGameStartWidgetToggle();


	UFUNCTION()
		void MapLoadComplete(); //스트리밍 레벨 로드 완료시 호출하는 함수	
	UFUNCTION()
		void MainMapUnLoadCompleteToTitle(); //메인 맵 스트리밍 레벨 언로드 완료시 호출하는 함수
	UFUNCTION()
		void MainMapUnLoadCompleteToCharacterSelect(); //메인 맵 스트리밍 레벨 언로드 완료시 호출하는 함수

	UFUNCTION()
		void SetInChannelText(const FText& _ChannelInMessage);

	UFUNCTION()
		void InChannelTextHidden();

	/*
		글로벌 메세지 관련 함수
	*/
	void SetInDunGeonMessageWidgetState(const EMessageState& _NewState, const FText & _NewMessage);
	void InDunGeonMessageWidgetVisible();
	bool IsDunGeonMessageWidgetVisible();
	
	//중앙 맵 이동 카운트 관련 함수들
	void SetGameStageStartCountInit(int32 _GameStageStartCount);
	UFUNCTION()
		void StartGameStageCount();

	void ChattingStart();
};
