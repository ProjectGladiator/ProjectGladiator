// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterCreateSelectGameMode.h"
//클라 헤더
#include "ChracterCreateSelectPC.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Client/ChracterCreateSelect/CameraActor/ChracterCreateCamera.h"
#include "Client/ChracterCreateSelect/Widget/TitleCharacterCreateWidget.h"
#include "Client/ChracterCreateSelect/Widget/TitleCharacterSelectWidget.h"
#include "Client/ErrorWidget/WidgetCancel.h"
#include "Client/ErrorWidget/WidgetOk.h"
#include "Kismet/KismetStringLibrary.h"
//서버 헤더
#include "NetWork/CharacterManager.h"
#include "NetWork/NetworkManager.h"
#include "NetWork/StorageManager.h"

ACharacterCreateSelectGameMode::ACharacterCreateSelectGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = AChracterCreateSelectPC::StaticClass();
}

void ACharacterCreateSelectGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChracterCreateCamera::StaticClass(), Cameras);

	FStringClassReference CharacterSelectWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/CharacterSelect/Widget/W_CharacterSelect.W_CharacterSelect_C'"));

	//앞에서 읽어 들인 CharacterSelectWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = CharacterSelectWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 CharacterSelectWidget을 생성한다.
		CharacterSelectWidget = Cast<UTitleCharacterSelectWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(),0), MyWidgetClass));
		CharacterSelectWidget->SetVisibility(ESlateVisibility::Visible);
		CharacterSelectWidget->AddToViewport(); //화면에 붙인다.
	}

	FStringClassReference ChracterCreateWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/CharacterSelect/Widget/W_CharacterCreate.W_CharacterCreate_C'"));

	//앞에서 읽어 들인 ChracterCreateWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = ChracterCreateWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 ChracterCreateWidget을 생성한다.
		ChracterCreateWidget = Cast<UTitleCharacterCreateWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));

		ChracterCreateWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
		ChracterCreateWidget->AddToViewport(); //화면에 붙인다.
	}

	FStringClassReference CancelWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Error/W_Cancel.W_Cancel_C'"));

	//앞에서 읽어 들인 CancelWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = CancelWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 CancelWidget을 생성한다.
		CancelWidget = Cast<UWidgetCancel>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));

		CancelWidget->AddToViewport(); //화면에 붙인다.
		CancelWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}

	FStringClassReference OkWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Error/W_ok.W_Ok_C'"));

	//앞에서 읽어 들인 OkWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = OkWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 OkWidget을 생성한다.
		OkWidget = Cast<UWidgetOk>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));

		OkWidget->AddToViewport(); //화면에 붙인다.
		OkWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}

	CharacterManager::GetInstance()->Character_Req_Slot();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void ACharacterCreateSelectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;
	//bool ResultFlag;

	if (StorageManager::GetInstance()->GetFront(Data))
	{
		switch (Data->protocol)
		{
		case PCHARACTERDATA_SLOT_INFO:
			CharacterSelectWidget->MyCharacterSlotUpdate(Data);
			break;
		}
	}
}

void ACharacterCreateSelectGameMode::CharacterSelectWidgetToggle()
{
	if (CharacterSelectWidget)
	{
		if (CharacterSelectWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			//CharacterSelectWidget->MyCharacterSlotUpdate();
			CharacterSelectWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CharacterSelectWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ACharacterCreateSelectGameMode::CharacterCreateWidgetToggle()
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
