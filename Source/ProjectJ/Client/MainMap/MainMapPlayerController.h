// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMapPlayerController.generated.h"

/**
 *
 */
struct CharacterSlot;

UCLASS()
class PROJECTJ_API AMainMapPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainMapPlayerController();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		TArray <AActor*> Cameras; //캐릭터 선택, 생성 카메라들을 담아둘 배열
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		class AChracterCreateCamera* CharacterCreateCamera; //캐릭터 생성창 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		class AChracterCreateCamera* CharacterSelectCamera; //캐릭터 선택창 카메라
	UPROPERTY()
		class AChracterCreateCamera* CharacterSelectZoomInCamera; //슬롯 선택시 소환된 캐릭터에게 줌인 되는 카메라
	UPROPERTY()
		class AMainMapGameMode* MainMapGameMode;
	int32 JobCode;
	int32 Select_index = -1;
	class ClientState* ClientCharacterState = nullptr; //클라이언트 상태
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	virtual void Tick(float DeltaTime) override;
public:
	CharacterSlot * CharacterSlotInfo;

	void ToCharacterCreate();
	void ToCharacterSelect();
	void ToCharacterZoomInCamera();

	void SelectCharacter(int NewJobCode);

	int32 GetJobCode();
	int32 GetSelectIndex();

	void SetSelectIndex(int32 _SelectIndex);

	void C2S_MoveConfirm(FVector& Location);
	void C2S_RotationcConfirm(FRotator& Rotation);
	void C2S_ReqMenuChannelInfo();
	void C2S_ReqMenuCharacterSelect();
	void C2S_ReqMenuLogOut();
	void C2S_ReqUserList();
	void C2S_ReqChannelChange(int32 ChannelIndex);

	void C2S_ReqPartyJoin(char* ReqCharacterCode);
	void C2S_ReqPartyAccept(bool _IsAccept, char* ReqCharacterCode, int32 _PartyRoomNum);
	void C2S_ReqPartyLeave();
	void C2S_ReqPartyKick(char* _PartyKickUserCode);
	void C2S_ReqPartyLeaderDelegate(char* _NewPartyLeaderUserCode);

	void C2S_ReqGameStageStart();
	void C2S_ReqInGameDungeon();

	void C2S_ReqMonsterInfo(const int32& _MonsterCode, const int32& _MonsterNumber, const FVector& _MonsterLocation);

	void C2S_ReqJump();

	void C2S_ReqAttack(int _Attacknum);

	void C2S_MyCharacterHitInfo(int _MonsterCode, int _MonsterNum, int _AttackNum, float _X, float _Y, float _Z);
	void C2S_MonsterHitInfo(int _MonsterCode,int _MonsterNum, int _AttackNum, float _X , float _Y, float _Z);


	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;

	void SetClientPCState(ClientState * _NewClientCharacterState);
};
