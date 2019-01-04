// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleGameMode.h"
//클라 헤더
#include "Client/Title/TitlePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Client/Title/Widget/TitleWidgetLogin.h"
#include "Client/Title/Widget/TitleWidgetUserIn.h"
#include "Client/ErrorWidget/WidgetCancel.h"
#include "Client/ErrorWidget/WidgetOk.h"
//서버 헤더
#include "NetWork/NetworkManager.h"

ATitleGameMode::ATitleGameMode()
{	
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = ATitlePlayerController::StaticClass();
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	//에디터 상에 있는 블루프린트를 읽어서 TitleUserInWidgetClass에 저장한다.
	FStringClassReference TitleUserInWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/Widget/W_UserIn.W_UserIn_C'"));

	//앞에서 읽어 들인 TitleUserInWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = TitleUserInWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 TitleWidgetUserIn을 생성한다.
		UserInWidget = Cast<UTitleWidgetUserIn>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));

		UserInWidget->AddToViewport(); //화면에 붙인다.
		UserInWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}

	//에디터 상에 있는 블루프린트를 읽어서 TitleLoginWidgetClass에 저장한다.
	FStringClassReference TitleLoginWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Title/Widget/W_Login.W_Login_C'"));

	//앞에서 읽어 들인 TitleLoginWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = TitleLoginWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 TitleWidgetLogin을 생성한다.
		LoginWidget = Cast<UTitleWidgetLogin>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));

		LoginWidget->AddToViewport(); //화면에 붙인다.
		LoginWidget->SetVisibility(ESlateVisibility::Visible); //숨긴다.
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

	FStringClassReference LoadingWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Loading/W_Loading.W_Loading_C'"));

	if (UClass* MyWidgetClass = LoadingWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 OkWidget을 생성한다.
		LoadingWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass);
	}

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

void ATitleGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;
	bool isOverlap = false;

	if (StorageManager::GetInstance()->GetFront(Data))
	{
		switch (Data->protocol)
		{
		case PLOGIN_IDOVERLAP_RESULT:			// ID 중복체크 결과
			StorageManager::GetInstance()->ChangeData(Data->data, isOverlap);
			StorageManager::GetInstance()->PopData();
			if (isOverlap == true)
			{
				UE_LOG(LogClass, Warning, TEXT("ID OK"));
			}
			else
			{
				//PC->OkWidgetToggle(FText(FText::FromString("이미있는 아이디입니다. 다른아이디를 입력하시기 바랍니다")));
				UE_LOG(LogClass, Warning, TEXT("ID EXIST"));
			}
			break;
		case PLOGIN_JOIN_RESULT:				// 회원가입 결과
			if (LoginManager::GetInstance()->isJoin())
			{
				UE_LOG(LogClass, Warning, TEXT("join success"));
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("join fail"));
			}

			LoginWidgetToggle(); //로그인 위젯을 켜고
			UserInWidgetToggle(); //회원가입 위젯을 끈다
			StorageManager::GetInstance()->PopData();
			break;

		case PLOGIN_LOGIN_RESULT:				// 로그인 결과
			if (LoginManager::GetInstance()->isLogin())
			{
				LoginWidgetToggle();
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("CharacterCreateSelect"));
			}
			else
			{
				OkWidgetToggle(FText(FText::FromString("로그인 실패")));
			}

			StorageManager::GetInstance()->PopData();
			break;
		}
	}
}

void ATitleGameMode::UserInWidgetToggle()
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

void ATitleGameMode::LoginWidgetToggle()
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

void ATitleGameMode::CancelWidgetToggle(const FText & Message)
{
	if (CancelWidget)
	{
		//매개변수로 받아온 메세지를 취소 위젯 에러메세지에 셋팅하고
		CancelWidget->SetErrorMessage(Message);
		//취소 위젯을 보여준다.
		CancelWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATitleGameMode::OkWidgetToggle(const FText & Message)
{
	if (OkWidget)
	{
		//매개변수로 받아온 메세지를 확인 위젯 에러메세지에 셋팅하고
		OkWidget->SetErrorMessage(Message);
		//확인 위젯을 보여준다.
		OkWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATitleGameMode::LoadingWidgetViewScreen()
{
	if (LoadingWidget)
	{
		LoadingWidget->AddToViewport();
	}
}
