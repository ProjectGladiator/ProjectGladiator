// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMapPlayerController.h"
//클라 헤더
#include "MainMapGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetStringLibrary.h"
#include "Client/ChracterCreateSelect/CameraActor/ChracterCreateCamera.h"
#include "Client/MyCharacter/MyCharacter.h"

//서버 헤더

void AMainMapPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AMainMapGameMode* MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

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
	SetViewTargetWithBlend(CharacterSelectCamera, 0, EViewTargetBlendFunction::VTBlend_Linear, 0, false); //캐릭터 선택창 카메라로 시점을 돌려준다.
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


