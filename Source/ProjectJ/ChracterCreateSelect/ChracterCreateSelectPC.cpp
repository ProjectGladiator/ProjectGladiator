// Fill out your copyright notice in the Description page of Project Settings.

#include "ChracterCreateSelectPC.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterCreateSelectGameMode.h"
#include "CameraActor/ChracterCreateCamera.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/World.h"

#include "Title/Widget/TitleCharacterCreateWidget.h"
#include "Title/Widget/TitleCharacterSelectWidget.h"

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

	FStringClassReference CharacterSelectWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/CharacterSelect/Widget/W_CharacterSelect.W_CharacterSelect_C'"));

	//앞에서 읽어 들인 CharacterSelectWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = CharacterSelectWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 CharacterSelectWidget을 생성한다.
		CharacterSelectWidget = Cast<UTitleCharacterSelectWidget>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		CharacterSelectWidget->AddToViewport(); //화면에 붙인다.
	}

	FStringClassReference ChracterCreateWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/CharacterSelect/Widget/W_CharacterCreate.W_CharacterCreate_C'"));

	//앞에서 읽어 들인 ChracterCreateWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = ChracterCreateWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 ChracterCreateWidget을 생성한다.
		ChracterCreateWidget = Cast<UTitleCharacterCreateWidget>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		ChracterCreateWidget->AddToViewport(); //화면에 붙인다.
		ChracterCreateWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}
	
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	ClickEventKeys.Add(EKeys::LeftMouseButton); 
	DefaultClickTraceChannel = ECollisionChannel::ECC_Pawn;

	//SetInputMode(FInputModeGameAndUI());
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

void AChracterCreateSelectPC::CharacterSelectWidgetToggle()
{
	if (CharacterSelectWidget)
	{
		if (CharacterSelectWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			CharacterSelectWidget->MyCharacterSlotUpdate();
			CharacterSelectWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CharacterSelectWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AChracterCreateSelectPC::CharacterCreateWidgetToggle()
{
	if (ChracterCreateWidget)
	{
		if (ChracterCreateWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			ChracterCreateWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ChracterCreateWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
