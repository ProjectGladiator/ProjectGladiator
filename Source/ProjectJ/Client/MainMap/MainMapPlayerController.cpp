// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMapPlayerController.h"
//클라 헤더
#include "MainMapGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetStringLibrary.h"
#include "Client/ChracterCreateSelect/CameraActor/ChracterCreateCamera.h"

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
					CharacterSelectCamera = LocalCamera;
					GLog->Log(FString::Printf(TEXT("캐릭터 선택창 카메라")));
				}
				else if (UKismetStringLibrary::EqualEqual_StrStr(LocalCamera->GetName(), FString::Printf(TEXT("BP_CharacterCreateSelect2_2"))))
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

void AMainMapPlayerController::ToCharacterCreate()
{
	SetViewTargetWithBlend(CharacterCreateCamera, 2.0f, EViewTargetBlendFunction::VTBlend_Linear, 0, false);
}

void AMainMapPlayerController::ToCharacterSelect()
{
	SetViewTargetWithBlend(CharacterSelectCamera, 2.0f, EViewTargetBlendFunction::VTBlend_Linear, 0, false);
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


