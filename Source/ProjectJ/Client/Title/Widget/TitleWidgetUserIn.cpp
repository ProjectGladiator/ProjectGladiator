// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleWidgetUserIn.h"
//클라 헤더
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Kismet/GameplayStatics.h"
//서버 헤더
#include "NetWork/NetworkManager.h"

void UTitleWidgetUserIn::NativeConstruct()
{
	Super::NativeConstruct();

	//위젯 블루프린트에 있는 IDInputBox를 가져와서 IDInputBox에 넣는다.
	IDInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IDInputBox")));
	//위젯 블루프린트에 있는 PWInputBox를 가져와서 PWInputBox에 넣는다.
	PWInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PWInputBox")));
	//위젯 블루프린트에 있는 PWCheckInputBox를 가져와서 PWCheckInputBox에 넣는다.
	PWCheckInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PWCheckInputBox")));
	//위젯 블루프린트에 있는 IDOverlapCheckButton를 가져와서 IDOverlapCheckButton에 넣는다.
	IDOverlapCheckButton = Cast<UButton>(GetWidgetFromName(TEXT("IDOverlapCheckButton")));
	//위젯 블루프린트에 있는 UserInButton를 가져와서 UserInButton에 넣는다.
	UserInButton = Cast<UButton>(GetWidgetFromName(TEXT("UserInButton")));
	//위젯 블루프린트에 있는 CancelButton를 가져와서 CancelButton에 넣는다.
	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));

	if (CancelButton)
	{
		//취소 버튼을 클릭하면 Cancel함수를 실행한다.
		CancelButton->OnClicked.AddDynamic(this, &UTitleWidgetUserIn::Cancel);
	}

	if (IDOverlapCheckButton)
	{
		//취소 버튼을 클릭하면 Cancel함수를 실행한다.
		IDOverlapCheckButton->OnClicked.AddDynamic(this, &UTitleWidgetUserIn::IdOverapCheck);
	}

	if (UserInButton)
	{
		//취소 버튼을 클릭하면 Cancel함수를 실행한다.
		UserInButton->OnClicked.AddDynamic(this, &UTitleWidgetUserIn::Join);
	}

	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UTitleWidgetUserIn::Cancel()
{
	if (MainMapPlayerController)
	{
		LoginManager::GetInstance()->exitJoin();
		// 패킷 전송 - Send , 서버 응답 대기 - Wait
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		MainMapGameMode->LoginWidgetToggle(); //로그인 위젯을 켜고
		MainMapGameMode->UserInWidgetToggle(); //회원가입 위젯을 끈다
	}
}

void UTitleWidgetUserIn::IdOverapCheck()
{
	if (MainMapPlayerController)
	{
		FString id = IDInputBox->Text.ToString();
		LoginManager::GetInstance()->reqIdOverlapCheck(TCHAR_TO_ANSI(*id));
		NetworkClient_main::NetworkManager::GetInstance()->Send();

		IDOverlapCheckButton->bIsEnabled = false;
	}
}

void UTitleWidgetUserIn::Join()
{
	if (MainMapPlayerController)
	{
		FString id = IDInputBox->Text.ToString();
		FString pw = PWInputBox->Text.ToString();
		//LoginManager::GetInstance()->reqJoin(TCHAR_TO_ANSI(*id), TCHAR_TO_ANSI(*pw));
		//NetworkClient_main::NetworkManager::GetInstance()->Send();

		IDInputBox->SetText(FText::FromString(TEXT("")));
		PWInputBox->SetText(FText::FromString(TEXT("")));
		PWCheckInputBox->SetText(FText::FromString(TEXT("")));

		IDInputBox->bIsEnabled = false;
		PWInputBox->bIsEnabled = false;
		UserInButton->bIsEnabled = false;
	}
}
