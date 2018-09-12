﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "TitlePlayerController.h"
#include "Title/Widget/TitleWidgetLogin.h"
#include "Title/Widget/TitleWidgetUserIn.h"
#include "ErrorWidget/WidgetCancel.h"
#include "ErrorWidget/WidgetOk.h"
#include "Title/Widget/TitleCharacterCreateWidget.h"
#include "Title/Widget/TitleCharacterSelectWidget.h"

#include "NetWork/NetworkManager.h"

void ATitlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//에디터 상에 있는 블루프린트를 읽어서 TitleUserInWidgetClass에 저장한다.
	FStringClassReference TitleUserInWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/Login/Widget/W_UserIn.W_UserIn_C'"));

	//앞에서 읽어 들인 TitleUserInWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = TitleUserInWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 TitleWidgetUserIn을 생성한다.
		UserInWidget = Cast<UTitleWidgetUserIn>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		UserInWidget->AddToViewport(); //화면에 붙인다.
		UserInWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}

	//에디터 상에 있는 블루프린트를 읽어서 TitleLoginWidgetClass에 저장한다.
	FStringClassReference TitleLoginWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/Login/Widget/W_Login.W_Login_C'"));

	//앞에서 읽어 들인 TitleLoginWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = TitleLoginWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 TitleWidgetLogin을 생성한다.
		LoginWidget = Cast<UTitleWidgetLogin>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		LoginWidget->AddToViewport(); //화면에 붙인다.
		LoginWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}
	
	FStringClassReference CancelWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Error/W_Cancel.W_Cancel_C'"));

	//앞에서 읽어 들인 CancelWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = CancelWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 CancelWidget을 생성한다.
		CancelWidget = Cast<UWidgetCancel>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		CancelWidget->AddToViewport(); //화면에 붙인다.
		CancelWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}

	FStringClassReference OkWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Error/W_ok.W_Ok_C'"));

	//앞에서 읽어 들인 OkWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = OkWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 OkWidget을 생성한다.
		OkWidget = Cast<UWidgetOk>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		OkWidget->AddToViewport(); //화면에 붙인다.
		OkWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}

	FStringClassReference CharacterSelectWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/CharacterSelect/Widget/W_CharacterSelect.W_CharacterSelect_C'"));

	//앞에서 읽어 들인 CharacterSelectWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = CharacterSelectWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 CharacterSelectWidget을 생성한다.
		CharacterSelectWidget = Cast<UTitleCharacterSelectWidget>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		CharacterSelectWidget->AddToViewport(); //화면에 붙인다.
		CharacterSelectWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
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

	bShowMouseCursor = true; //마우스 커서가 화면에 보이게 해준다.
	SetInputMode(FInputModeUIOnly()); //게임의 모드를 UIOnly로 설정한다.

	LoginWidgetToggle();

	// 서버와 연결 시도
	if (NetworkClient_main::NetworkManager::GetInstance()->Connect() == false)
	{
		UE_LOG(LogClass, Warning, TEXT("Server connect fail"));
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("Server connect success"));
	}
}

void ATitlePlayerController::UserInWidgetToggle()
{
	//회원가입 위젯이 숨겨져있으면 보여주고
	//보여져 있으면 숨겨준다.
	if (UserInWidget)
	{
		if (UserInWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			UserInWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UserInWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ATitlePlayerController::LoginWidgetToggle()
{
	//로그인 위젯이 숨겨져있으면 보여주고
	//보여져 있으면 숨겨준다.
	if (LoginWidget)
	{
		if (LoginWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			LoginWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			LoginWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ATitlePlayerController::CancelWidgetToggle(const FText& Message)
{
	if (CancelWidget)
	{
		//매개변수로 받아온 메세지를 취소 위젯 에러메세지에 셋팅하고
		CancelWidget->SetErrorMessage(Message);
		//취소 위젯을 보여준다.
		CancelWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATitlePlayerController::OkWidgetToggle(const FText& Message)
{
	if (OkWidget)
	{
		//매개변수로 받아온 메세지를 확인 위젯 에러메세지에 셋팅하고
		OkWidget->SetErrorMessage(Message);
		//확인 위젯을 보여준다.
		OkWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATitlePlayerController::CharacterSelectWidgetToggle()
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

void ATitlePlayerController::CharacterCreateWidgetToggle()
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
