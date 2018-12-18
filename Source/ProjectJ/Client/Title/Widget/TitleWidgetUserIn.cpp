// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleWidgetUserIn.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

#include "Client/Title/TitlePlayerController.h"

#include "Kismet/GameplayStatics.h"
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

	PC = Cast<ATitlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UTitleWidgetUserIn::Cancel()
{
	if (PC)
	{
		LoginManager::GetInstance()->exitJoin();
		// 패킷 전송 - Send , 서버 응답 대기 - Wait
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		PC->LoginWidgetToggle(); //로그인 위젯을 켜고
		PC->UserInWidgetToggle(); //회원가입 위젯을 끈다
	}
}

void UTitleWidgetUserIn::IdOverapCheck()
{
	if (PC)
	{
		FString id = IDInputBox->Text.ToString();
		LoginManager::GetInstance()->reqIdOverlapCheck(TCHAR_TO_ANSI(*id));
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		PacketData* pd;
		StorageManager::GetInstance()->GetFront(pd);
		if (pd->protocol == PLOGIN_IDOVERLAP_RESULT)
		{
			bool result;
			StorageManager::GetInstance()->ChangeData(pd->data, result);
			StorageManager::GetInstance()->PopData();
			if (result == true)
			{
				UE_LOG(LogClass, Warning, TEXT("ID OK"));
			}
			else
			{
				//PC->OkWidgetToggle(FText(FText::FromString("이미있는 아이디입니다. 다른아이디를 입력하시기 바랍니다")));
				UE_LOG(LogClass, Warning, TEXT("ID EXIST"));
			}
		}
	}
}

void UTitleWidgetUserIn::Join()
{
	if (PC)
	{
		FString id = IDInputBox->Text.ToString();
		FString pw = PWInputBox->Text.ToString();
		LoginManager::GetInstance()->reqJoin(TCHAR_TO_ANSI(*id), TCHAR_TO_ANSI(*pw));
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		if (LoginManager::GetInstance()->isJoin())
		{
			UE_LOG(LogClass, Warning, TEXT("join success"));
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("join fail"));
		}

		PC->LoginWidgetToggle(); //로그인 위젯을 켜고
		PC->UserInWidgetToggle(); //회원가입 위젯을 끈다
	}
}
