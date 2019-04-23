// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMapPlayerController.h"
//클라 헤더
#include "MainMapGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetStringLibrary.h"
#include "Client/ChracterCreateSelect/CameraActor/ChracterCreateCamera.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/State/ClientState/PC/ClientPCTitleState.h"
#include "Client/State/ClientState/PC/ClientPCInGameState.h"

//서버 헤더
#include "NetWork/InGameManager.h"
#include "NetWork/NetworkManager.h"

AMainMapPlayerController::AMainMapPlayerController()
{
	
}

void AMainMapPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (MainMapGameMode)
	{
		Cameras = MainMapGameMode->Cameras;

		for (auto Camera : Cameras)
		{
			AChracterCreateCamera* LocalCamera = Cast<AChracterCreateCamera>(Camera);

			if (LocalCamera)
			{
				if (UKismetStringLibrary::EqualEqual_StrStr(LocalCamera->GetName(), FString::Printf(TEXT("BP_CharacterCreateSelect_5"))))
				{
					CharacterSelectCamera = LocalCamera; //캐릭터 선택창 카메라
				}
				else if (UKismetStringLibrary::EqualEqual_StrStr(LocalCamera->GetName(), FString::Printf(TEXT("BP_CharacterCreateSelect2_2"))))
				{
					CharacterCreateCamera = LocalCamera; //캐릭터 생성창 카메라
				}
				else if (UKismetStringLibrary::EqualEqual_StrStr(LocalCamera->GetName(), FString::Printf(TEXT("BP_CharacterCreateSelect3"))))
				{
					CharacterSelectZoomInCamera = LocalCamera; //캐릭터 선택창 줌인 카메라
				}
			}
		}
	}

	bShowMouseCursor = true; //커서를 보이고
	bEnableClickEvents = true; //마우스 클릭 이벤트를 활성화 시키고
	bEnableMouseOverEvents = true; //마우스를 가져다 대는 이벤트를 활성화 시키고
	ClickEventKeys.Add(EKeys::LeftMouseButton); //클릭 이벤트에 마우스 왼쪽 버튼을 추가하고
	DefaultClickTraceChannel = ECollisionChannel::ECC_Pawn; //클릭 이벤트에 반응하는 채널을 Pawn으로 설정한다.

	SetInputMode(FInputModeGameAndUI()); //게임 입력 모드를 게임,UI모드로 설정한다.
	SetViewTargetWithBlend(CharacterSelectCamera, 0, EViewTargetBlendFunction::VTBlend_Linear, 0, false); //캐릭터 선택창 카메라로 시점을 돌려준다.s

	SetClientPCState(new ClientPCTitleState());
}

void AMainMapPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ClientCharacterState)
	{
		delete ClientCharacterState;
		ClientCharacterState = nullptr;
	}
}

void AMainMapPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ClientCharacterState->Tick(DeltaTime);
}

void AMainMapPlayerController::ToCharacterCreate()
{
	auto MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!MyCharacter->GetIsClick())
	{
		MyCharacter->SetIsClick(true); //캐릭터들을 선택할수 있는 상태로 변경
	}

	SetViewTargetWithBlend(CharacterCreateCamera, 2.0f, EViewTargetBlendFunction::VTBlend_EaseIn, 0, false);
}

void AMainMapPlayerController::ToCharacterSelect()
{
	auto MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (MyCharacter->GetIsClick())
	{
		MyCharacter->SetIsClick(false); //캐릭터들을 선택할수 없는 상태로 변경
	}

	SetViewTargetWithBlend(CharacterSelectCamera, 2.0f, EViewTargetBlendFunction::VTBlend_EaseIn, 0, false);
}

void AMainMapPlayerController::ToCharacterZoomInCamera()
{
	SetViewTargetWithBlend(CharacterSelectZoomInCamera, 1.0f, EViewTargetBlendFunction::VTBlend_Linear, 0, false);
}

void AMainMapPlayerController::SelectCharacter(int _JobCode)
{
	JobCode = _JobCode;
}

int32 AMainMapPlayerController::GetJobCode()
{
	return JobCode;
}

int32 AMainMapPlayerController::GetSelectIndex()
{
	return Select_index;
}

void AMainMapPlayerController::SetSelectIndex(int32 _SelectIndex)
{
	Select_index = _SelectIndex;
}

void AMainMapPlayerController::C2S_MoveConfirm(FVector & Location)
{
	InGameManager::GetInstance()->InGame_Req_Move(Location.X, Location.Y, Location.Z);
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_RotationcConfirm(FRotator & Rotation)
{
	InGameManager::GetInstance()->InGame_Req_Rotation(Rotation.Roll, Rotation.Pitch, Rotation.Yaw);
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqMenuChannelInfo()
{
	InGameManager::GetInstance()->InGame_Req_ChannelInfo();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqMenuCharacterSelect()
{
	InGameManager::GetInstance()->InGame_Req_Menu_Character();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqMenuLogOut()
{
	InGameManager::GetInstance()->InGame_Req_Menu_Title();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqUserList()
{
	InGameManager::GetInstance()->InGame_Req_UserList();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqChannelChange(int32 ChannelIndex)
{
	InGameManager::GetInstance()->InGame_Req_ChannelChange(ChannelIndex);
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqPartyJoin(char * ReqCharacterCode)
{
	InGameManager::GetInstance()->InGame_Req_Party_Invite(ReqCharacterCode);
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqPartyAccept(bool _IsAccept, char * ReqCharacterCode, int32 _PartyRoomNum)
{
	InGameManager::GetInstance()->InGame_Req_Party_Invite_Result(_IsAccept,ReqCharacterCode, _PartyRoomNum);
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqPartyLeave()
{
	InGameManager::GetInstance()->InGame_Req_LeaveParty();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqPartyKick(char * _PartyKickUserCode)
{
	InGameManager::GetInstance()->InGame_Req_KickUser(_PartyKickUserCode);
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqPartyLeaderDelegate(char * _NewPartyLeaderUserCode)
{
	InGameManager::GetInstance()->InGame_Req_LeaderDelegate(_NewPartyLeaderUserCode);
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqGameStageStart()
{
	InGameManager::GetInstance()->InGame_Req_Dungeon_Stage_Enter();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::C2S_ReqInGameDungeon()
{
	InGameManager::GetInstance()->InGame_Req_Dungeon_Enter();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapPlayerController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
}

void AMainMapPlayerController::SetClientPCState(ClientState * _NewClientCharacterState)
{
	if (!ClientCharacterState)
	{
		delete ClientCharacterState;
		ClientCharacterState = nullptr;
	}

	ClientCharacterState = _NewClientCharacterState;
}