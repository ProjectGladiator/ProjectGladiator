// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleWidgetLogin.h"
//클라 헤더
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Client/Title/TitlePlayerController.h"
#include "Client/Title/TitleGameMode.h"
#include "Client/MainMap/MainMapGameMode.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

//서버 헤더
#include "NetWork/NetworkManager.h"
#include "NetWork/LoginManager.h"
#include "NetWork/CharacterManager.h"

void UTitleWidgetLogin::NativeConstruct()
{
	Super::NativeConstruct();

	//위젯블루프린트에 있는 IDInputBox를 가져와서 IDInputBox에 넣는다.
	IDInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IDBox")));

	//위젯블루프린트에 있는 PWInputBox를 가져와서 PWInputBox에 넣는다.
	PWInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PWBox")));

	//위젯블루프린트에 있는 LoginButton를 가져와서 LoginButton에 넣는다.
	LoginButton = Cast<UButton>(GetWidgetFromName(TEXT("LoginButton")));

	if (LoginButton)
	{
		//로그인버튼을 클릭하면 Login함수를 실행한다.
		LoginButton->OnClicked.AddDynamic(this, &UTitleWidgetLogin::Login);
	}

	//위젯블루프린트에 있는 UserInButton를 가져와서 UserInButton에 넣는다.
	UserInButton = Cast<UButton>(GetWidgetFromName(TEXT("UserInButton")));

	if (UserInButton)
	{
		//회원가입 버튼을 클릭하면 UserIn함수를 실행한다.
		UserInButton->OnClicked.AddDynamic(this, &UTitleWidgetLogin::UserIn);
	}

	//PC에 TitlePlayerController를 구해서 넣어준다.
	//PC = Cast<ATitlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//TitleGM = Cast<ATitleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainMapGameMode = Cast<AMainMapGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

//회원가입 버튼 눌럿을때
void UTitleWidgetLogin::UserIn()
{
	if (MainMapPlayerController)
	{
		LoginManager::GetInstance()->logoutMenuChoice(2);
		// 패킷 전송 - Send , 서버 응답 대기 - Wait
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		NetworkClient_main::NetworkManager::GetInstance()->Wait();

		MainMapGameMode->UserInWidgetToggle(); //회원가입 위젯을 켜고
		MainMapGameMode->LoginWidgetToggle(); //로그인 위젯을 끈다
	}
}

//로그인 버튼 눌럿을때
void UTitleWidgetLogin::Login()
{
	if (MainMapPlayerController)
	{
		GLog->Log(FString::Printf(TEXT("로그인")));
		// 아이디, 패스워드 에디트박스에서 Text 뽑아서 FString 으로 변환
		FString id = IDInputBox->Text.ToString();
		FString pw = PWInputBox->Text.ToString();
	
		// FString -> ANSI 표준으로 변환 후 인자로 넣어 로그인 요청 메세지 만듦
		LoginManager::GetInstance()->reqLogin(TCHAR_TO_ANSI(*id), TCHAR_TO_ANSI(*pw));
		// 패킷 전송 - Send
		NetworkClient_main::NetworkManager::GetInstance()->Send();
		
		IDInputBox->bIsEnabled = false;
		PWInputBox->bIsEnabled = false;
		this->bIsEnabled = false;
	}
}

void UTitleWidgetLogin::ToCharacterSelectLevel()
{
	//나중에 처리
	//GetWorld()->GetTimerManager().SetTimer(LoadingTimer, this, &UTitleWidgetLogin::ToCharacterSelectLevel, 1.5f, false);
	GLog->Log(FString::Printf(TEXT("캐릭터 셀렉트 맵으로")));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("CharacterCreateSelect"));
}
