// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetWork/JobInfo.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LogdingWidget, Meta = (AllowPrivateAccess = true))
		float CurrentChannelUserCount; //현재 채널에 있는 유저 수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LogdingWidget, Meta = (AllowPrivateAccess = true))
		float MaxChannelUserCount; //채널에 들어올 수 있는 최대 유저 수
	UPROPERTY()
		class UStageManager* StageManager;
	UPROPERTY()
		class AMyCharacter* SelectCharacter; //슬롯 버튼을 누르면 캐릭터를 소환 할때 저장해둘 캐릭터
	UPROPERTY()
		class AMyCharacter* CreateSelectCharacter; //캐릭터 선택, 캐릭터 생성, 게임 시작 등을 담당할 캐릭터
	UPROPERTY()
		TArray<class AMyCharacter*> OtherLoginUserList; //나를 제외한 현재 채널에 접속해 있는 모든 캐릭터들을 저장해둘 포인터 배열 변수
	UPROPERTY()
		class AMainMapPlayerController* MainMapPlayerController; 
	UPROPERTY()
		int32 Channelnum = -1; //속해 있는 채널 번호
public:
	AMainMapGameMode();

	TArray <AActor*> Cameras; //캐릭터 선택, 생성창의 카메라 

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void UserInWidgetToggle(); //회원가입 위젯 보여주기,끄기
	void LoginWidgetToggle(); //로그인 위젯 보여주기,끄기
	void CharacterSelectWidgetToggle(); //캐릭터 선택창 위젯 보여주기, 끄기
	void CharacterCreateWidgetToggle(); //캐릭터 생성창 위젯 보여주기, 끄기
	void CancelWidgetToggle(const FText& Message); //에러 다시시도,취소 위젯 보여주기
	void OkWidgetToggle(const FText& Message); //에러 확인 위젯 보여주기
	void LoadingWidgetViewScreen(); //로딩 위젯 화면에 붙이기
	void LoadingWidgetHiddenScreen(); //로딩 위젯 화면에서 없애기
	
	void SelectCharacterSpawn(CHARACTER_JOB _SelectJob); //캐릭터 선택창에서 선택한 슬롯의 직업에 따라 화면 가운데에 캐릭터를 스폰 시켜주는 함수
	void SelectCharacterDestroy();

	void AddLoginUser(AMyCharacter* _OtherCharacter); //로그인 된 캐릭터 배열에 추가하기
	void DeleteLoginUser(AMyCharacter* _OtherCharacter); //로그인 중인 캐릭터 삭제 하기

	AMyCharacter* GetLoginUser(char* _OtherCharacterCode); //특정 캐릭터 가져오기

	void LoginUserDestory(char* _OtherCharacterCode); // 로그 아웃 or 캐릭터 변경 누른 캐릭터 삭제 하기
	void LoginUserAllDestory(); //로그인 중인( 같은 채널 ) 모든 캐릭터 삭제하기

	float GetCurrentChannelUserCount(); //현재 채널에 있는 유저 수 반환
	float GetMaxChannelUserCount(); //채널 최대인원 수 반환

	int32 GetChannelNum();//현재 속한 채널 번호 반환

	UFUNCTION()
		void MapLoadComplete(); //스트리밍 레벨 로드 완료시 호출하는 함수	

	AMyCharacter* GetCreateSelectCharacter();

	void OpenDoor();
};
