// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMapGameMode.h"
//클라 헤더
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Client/Title/Widget/TitleWidgetLogin.h"
#include "Client/Title/Widget/TitleWidgetUserIn.h"
#include "Client/ChracterCreateSelect/Widget/CharacterCreateWidget.h"
#include "Client/ChracterCreateSelect/Widget/CharacterSelectWidget.h"
#include "Client/ErrorWidget/WidgetCancel.h"
#include "Client/ErrorWidget/WidgetOk.h"
#include "Client/ChracterCreateSelect/CameraActor/ChracterCreateCamera.h"
#include "Components/Button.h"
#include "Client/MyCharacter/Tanker/Tanker.h"
#include "Client/MyCharacter/Warrior/Warrior.h"
#include "Client/MyCharacter/Gunner/Gunner.h"
#include "MainMapPlayerController.h"
#include "Manager/StageManager.h"
#include "Client/MyCharacter/MyAnimInstance.h"
#include "Client/MyCharacter/MyCharacter.h"

//서버 헤더
#include "NetWork/CharacterManager.h"
#include "NetWork/NetworkManager.h"
#include "NetWork/StorageManager.h"
#include "NetWork/InGameManager.h"

AMainMapGameMode::AMainMapGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	StageManager = CreateDefaultSubobject<UStageManager>(TEXT("StageManager"));
}

void AMainMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChracterCreateCamera::StaticClass(), Cameras);

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

	FStringClassReference CharacterSelectWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/CharacterCreateSelect/Widget/W_CharacterSelect.W_CharacterSelect_C'"));

	//앞에서 읽어 들인 CharacterSelectWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = CharacterSelectWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 CharacterSelectWidget을 생성한다.
		CharacterSelectWidget = Cast<UCharacterSelectWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));
		CharacterSelectWidget->SetVisibility(ESlateVisibility::Hidden);
		CharacterSelectWidget->AddToViewport(); //화면에 붙인다.
	}

	FStringClassReference ChracterCreateWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/CharacterCreateSelect/Widget/W_CharacterCreate.W_CharacterCreate_C'"));

	//앞에서 읽어 들인 ChracterCreateWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = ChracterCreateWidgetClass.TryLoadClass<UUserWidget>())
	{
		//MyWidgetClass를 토대로 ChracterCreateWidget을 생성한다.
		ChracterCreateWidget = Cast<UCharacterCreateWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass));

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

void AMainMapGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;
	bool isOverlap = false;
	bool ResultFlag;
	CharacterInfo* character_info = nullptr;
	float x, y, z; float rx, ry, rz;				// 위치, 회전 넣을 변수
	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnActorOption;
	int UserCount = -1;
	AMyCharacter* MyCharacter = nullptr;
	AMyCharacter* OtherUserCharacter = nullptr;
	ATanker* Tanker = nullptr;
	AWarrior* Warrior = nullptr;
	AGunner* Gunner = nullptr;

	if (StorageManager::GetInstance()->GetFront(Data)) //창고매니저 큐에 들어있는 데이터를 가져와서 Data에 담는다.
	{
		switch (Data->protocol) //담아온 Data의 프로토콜을 확인한다.
		{
		case PLOGIN_IDOVERLAP_RESULT: // ID 중복체크 결과
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
			GLog->Log(FString::Printf(TEXT("게임모드 틱 로그인 결과")));
			if (LoginManager::GetInstance()->isLogin())
			{
				//LoadingWidget->AddToViewport();
				LoginWidgetToggle();
				CharacterSelectWidgetToggle();

				FLatentActionInfo LatentInfo;
				UGameplayStatics::LoadStreamLevel(this, TEXT("CharacterCreate"), true, true, LatentInfo);
				StorageManager::GetInstance()->PopData();
				CharacterManager::GetInstance()->Character_Req_Slot();
				NetworkClient_main::NetworkManager::GetInstance()->Send();
				//UGameplayStatics::OpenLevel(GetWorld(), TEXT("CharacterCreateSelect"));
			}
			else
			{
				StorageManager::GetInstance()->PopData();
				OkWidgetToggle(FText(FText::FromString("로그인 실패")));
			}

			break;
		case PCHARACTERDATA_SLOT_INFO:			// 슬롯 정보
			CharacterSelectWidget->MyCharacterSlotUpdate(Data);
			GLog->Log(FString::Printf(TEXT("캐릭터 슬롯 정보 업데이트")));
			break;
		case  PCHARACTERDATA_DELETE_RESULT:
			StorageManager::GetInstance()->ChangeData(Data->data, ResultFlag);
			StorageManager::GetInstance()->PopData();
			if (ResultFlag)
			{
				SelectCharacterDestroy();
				CharacterSelectWidget->MyCharacterSlotHidden();
				GLog->Log(FString::Printf(TEXT("캐릭터 삭제 성공")));
				CharacterManager::GetInstance()->Character_Req_Slot();
				NetworkClient_main::NetworkManager::GetInstance()->Send();
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("캐릭터 삭제 실패")));
			}
			break;
		case PCHARACTERDATA_ENTER_RESULT:		// 게임 접속 요청 결과
			StorageManager::GetInstance()->ChangeData(Data->data, ResultFlag);
			if (ResultFlag)
			{
				//****	
				//** 다음 씬 로딩
				//****
				CharacterSelectWidgetToggle();

				LoadingWidgetViewScreen();

				FLatentActionInfo LatentInfo;
				LatentInfo.CallbackTarget = this;
				LatentInfo.ExecutionFunction = "MapLoadComplete";
				LatentInfo.UUID = 123;
				LatentInfo.Linkage = 0;

				StorageManager::GetInstance()->PopData();
				UGameplayStatics::LoadStreamLevel(this, TEXT("MainStageStartArea"), true, true, LatentInfo);
			}
			else
			{
				//****
				//** 게임 시작, 생성 버튼 활성화 후 메세지창 띄우기
				//****
				CharacterSelectWidget->GetGameStartButton()->SetVisibility(ESlateVisibility::Visible);
				ChracterCreateWidget->GetChracterCreateButton()->SetVisibility(ESlateVisibility::Visible);
			}
			break;
		case PCHARACTERDATA_CREATE_RESULT:
			GLog->Log(FString::Printf(TEXT("캐릭터 생성창 프로토콜 인증 성공")));
			StorageManager::GetInstance()->ChangeData(Data->data, ResultFlag);
			StorageManager::GetInstance()->PopData();

			if (ResultFlag)
			{
				CharacterManager::GetInstance()->Character_Req_Slot();
				NetworkClient_main::NetworkManager::GetInstance()->Send();

			}
			else
			{
				GLog->Log(FString::Printf(TEXT("캐릭터 생성후 ChangeData Result가 false")));
			}
			break;
		case PCHARACTERDATA_ENTER_INFO:
			// 캐릭터 정보 받을 구조체 할당
			character_info = new CharacterInfo;

			memset(character_info, 0, sizeof(CharacterInfo));

			// 캐릭터 정보 서버에서 받은거 넣어줌
			StorageManager::GetInstance()->ChangeData(Data->data, character_info);

			StorageManager::GetInstance()->PopData();

			x = character_info->xyz[0]; y = character_info->xyz[1]; z = character_info->xyz[2];

			SpawnLocation = FVector(x, y, z);

			SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			switch (character_info->job_code)
			{
			case CHARACTER_JOB::Tanker:
				MyCharacter = GetWorld()->SpawnActor<ATanker>(Tanker->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);
				break;
			case CHARACTER_JOB::Warrior:
				MyCharacter = GetWorld()->SpawnActor<AWarrior>(Warrior->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);
				break;
			case CHARACTER_JOB::Magician:
				break;
			case CHARACTER_JOB::Gunner:
				MyCharacter = GetWorld()->SpawnActor<AGunner>(Gunner->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);
				break;
			}

			if (MyCharacter)
			{
				GLog->Log(ANSI_TO_TCHAR(character_info->code));
			
				MyCharacter->SetCharacterCode(character_info->code);

				MainMapSpawnCharacterPossess(MyCharacter);
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("캐릭터 소환 안됨")));
			}
			// 필요없어진 캐릭터정보 구조체 해제
			delete character_info;
			MyCharacter = nullptr;
			break;
		case PGAMEDATA_USERLIST_COUNT:
			StorageManager::GetInstance()->ChangeData(Data->data, UserCount);
			StorageManager::GetInstance()->PopData();
			GLog->Log(FString::Printf(TEXT("접속한 유저 수 : %d"), UserCount));
			break;
		case PGAMEDATA_USERLIST_USER:
			GLog->Log(FString::Printf(TEXT("접속한 다른 유저 월드에 스폰")));
			// 캐릭터 정보 받을 구조체 할당
			character_info = new CharacterInfo;

			memset(character_info, 0, sizeof(CharacterInfo));

			// 캐릭터 정보 서버에서 받은거 넣어줌
			StorageManager::GetInstance()->ChangeData(Data->data, character_info);
			StorageManager::GetInstance()->PopData();

			x = character_info->xyz[0]; y = character_info->xyz[1]; z = character_info->xyz[2];
			rx = character_info->rot_xyz[0]; ry = character_info->rot_xyz[1]; rz = character_info->rot_xyz[2];

			SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			SpawnLocation = FVector(x, y, z);
			SpawnRotation = FRotator(rx, ry, rz);

			switch (character_info->job_code)
			{
			case CHARACTER_JOB::Tanker:
				OtherUserCharacter = GetWorld()->SpawnActor<ATanker>(Tanker->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);
				break;
			case CHARACTER_JOB::Warrior:
				OtherUserCharacter = GetWorld()->SpawnActor<AWarrior>(Warrior->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);
				break;
			case CHARACTER_JOB::Magician:
				break;
			case CHARACTER_JOB::Gunner:
				OtherUserCharacter = GetWorld()->SpawnActor<AGunner>(Gunner->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);
				break;
			}

			if (OtherUserCharacter)
			{
				OtherLoginUserList.Add(OtherUserCharacter);
			}

			// 필요없어진 캐릭터정보 구조체 해제
			delete character_info;
			OtherUserCharacter = nullptr;
			break;
		}
	}
}

void AMainMapGameMode::UserInWidgetToggle()
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

void AMainMapGameMode::LoginWidgetToggle()
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

void AMainMapGameMode::CharacterSelectWidgetToggle()
{
	if (CharacterSelectWidget)
	{
		if (CharacterSelectWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			CharacterSelectWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CharacterSelectWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AMainMapGameMode::CharacterCreateWidgetToggle()
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

void AMainMapGameMode::CancelWidgetToggle(const FText & Message)
{
	if (CancelWidget)
	{
		//매개변수로 받아온 메세지를 취소 위젯 에러메세지에 셋팅하고
		CancelWidget->SetErrorMessage(Message);
		//취소 위젯을 보여준다.
		CancelWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainMapGameMode::OkWidgetToggle(const FText & Message)
{
	if (OkWidget)
	{
		//매개변수로 받아온 메세지를 확인 위젯 에러메세지에 셋팅하고
		OkWidget->SetErrorMessage(Message);
		//확인 위젯을 보여준다.
		OkWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainMapGameMode::LoadingWidgetViewScreen()
{
	if (LoadingWidget)
	{
		LoadingWidget->AddToViewport();
	}
}

void AMainMapGameMode::MapLoadComplete()
{
	SelectCharacterDestroy();
	GLog->Log(FString::Printf(TEXT("맵 로드 완료")));
	LoadingWidget->SetVisibility(ESlateVisibility::Hidden);

	// 서버에 다른 유저리스트 요청
	InGameManager::GetInstance()->InGame_Req_UserList();
	NetworkClient_main::NetworkManager::GetInstance()->Send();
}

void AMainMapGameMode::MainMapSpawnCharacterPossess(AMyCharacter* _MyCharacter)
{
	if (_MyCharacter)
	{
		auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (MainMapPlayerController)
		{
			MainMapPlayerController->bShowMouseCursor = false;
			MainMapPlayerController->SetInputMode(FInputModeGameOnly());
			/*MainMapPlayerController->bEnableClickEvents = false;
			MainMapPlayerController->bEnableMouseOverEvents = false;*/
			MainMapPlayerController->Possess(_MyCharacter);
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("메인 스테이지 월드에 메인스테이지 플레이어컨트롤러가 스폰 안됨")));
		}
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("메인 스테이지 월드에 캐릭터가 스폰 안됨")));
	}
}

void AMainMapGameMode::SelectCharacterSpawn(CHARACTER_JOB _SelectJob)
{
	GLog->Log(FString::Printf(TEXT("선택한 캐릭터 스폰")));

	ATanker* SelectTankerCharacter = nullptr;
	AWarrior* SelectWarriorCharacter = nullptr;
	AGunner* SelectGunnerCharacter = nullptr;

	FActorSpawnParameters SpawnActorOption;
	SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SelectCharacterDestroy();

	switch (_SelectJob)
	{
	case CHARACTER_JOB::Tanker:
		SelectCharacter = GetWorld()->SpawnActor<ATanker>(SelectTankerCharacter->StaticClass(), FVector(5.0f, -1150.0f, 155.0f), FRotator::ZeroRotator, SpawnActorOption);
		break;
	case CHARACTER_JOB::Warrior:
		SelectCharacter = GetWorld()->SpawnActor<AWarrior>(SelectWarriorCharacter->StaticClass(), FVector(5.0f, -1150.0f, 155.0f), FRotator::ZeroRotator, SpawnActorOption);
		break;
	case CHARACTER_JOB::Gunner:
		SelectCharacter = GetWorld()->SpawnActor<AGunner>(SelectGunnerCharacter->StaticClass(), FVector(5.0f, -1150.0f, 155.0f), FRotator::ZeroRotator, SpawnActorOption);
		break;
	}

	if (SelectCharacter)
	{
		GLog->Log(FString::Printf(TEXT("메인맵 게임모드 레벨스타트 몽타주 실행")));
		SelectCharacter->SetActorRotation(FRotator(0, -90.0f, 0));
		SelectCharacter->GetMyAnimInstance()->PlayLevelStartMontage();
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("캐릭터가 스폰되지 않음")));
	}
}

void AMainMapGameMode::SelectCharacterDestroy()
{
	if (SelectCharacter)
	{
		SelectCharacter->Destroy();
	}
}

AMyCharacter* AMainMapGameMode::GetLoginUser(char* _OtherCharacterCode)
{
	
	for (int i = 0; i < OtherLoginUserList.Num(); i++)
	{
		if (strcmp(OtherLoginUserList[i]->GetCharacterCode(), _OtherCharacterCode) == 0)
		{
			return OtherLoginUserList[i];
		}
	}

	return nullptr;
}
