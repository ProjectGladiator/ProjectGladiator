// Fill out your copyright notice in the Description page of Project Settings.

#include "ChracterCreateSelectPC.h"
//클라 헤더
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "CharacterCreateSelectGameMode.h"
#include "CameraActor/ChracterCreateCamera.h"
#include "Kismet/KismetStringLibrary.h"
//서버 헤더
#include "Network/StorageManager.h"

void AChracterCreateSelectPC::BeginPlay()
{
	ACharacterCreateSelectGameMode* CCGM = Cast<ACharacterCreateSelectGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (CCGM)
	{
		Cameras = CCGM->Cameras;

		for (auto Camera : Cameras)
		{
			AChracterCreateCamera* LocalCamera = Cast<AChracterCreateCamera>(Camera);
			if (LocalCamera)
			{
				if(UKismetStringLibrary::EqualEqual_StrStr(LocalCamera->GetName(), FString::Printf(TEXT("BP_CharacterCreateSelect_5"))))				
				{
					CharacterSelectCamera = LocalCamera;
					GLog->Log(FString::Printf(TEXT("캐릭터 선택창 카메라")));
				}
				else
				{
					CharacterCreateCamera = LocalCamera;
					GLog->Log(FString::Printf(TEXT("캐릭터 생성창 카메라")));
				}
			}
		}
	}

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	ClickEventKeys.Add(EKeys::LeftMouseButton); 
	DefaultClickTraceChannel = ECollisionChannel::ECC_Pawn;

	SetInputMode(FInputModeGameAndUI());
	SetViewTargetWithBlend(CharacterSelectCamera, 0, EViewTargetBlendFunction::VTBlend_Linear, 0, false);
}

void AChracterCreateSelectPC::ToCharacterCreate()
{
	SetViewTargetWithBlend(CharacterCreateCamera, 2.0f, EViewTargetBlendFunction::VTBlend_Linear, 0, false);
}

void AChracterCreateSelectPC::ToCharacterSelect()
{
	SetViewTargetWithBlend(CharacterSelectCamera, 2.0f, EViewTargetBlendFunction::VTBlend_Linear, 0, false);
}

void AChracterCreateSelectPC::SelectCharacter(int NewJobCode)
{
	JobCode = NewJobCode;
}

int32 AChracterCreateSelectPC::GetJobCode()
{
	return JobCode;
}

int32 AChracterCreateSelectPC::GetSelectIndex()
{
	return Select_index;
}

void AChracterCreateSelectPC::SetSelectIndex(int32 _SelectIndex)
{
	Select_index = _SelectIndex;
}
