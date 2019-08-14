// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMapGameMode.h"
//클라 헤더
#include "Kismet/GameplayStatics.h" //각종 유틸 헤더
#include "Client/Title/Widget/TitleWidgetLogin.h" //로그인 위젯 헤더
#include "Client/Title/Widget/TitleWidgetUserIn.h" //회원가입 위젯 헤더
#include "Client/ChracterCreateSelect/Widget/CharacterCreateWidget.h" //캐릭터 생성 위젯 헤더
#include "Client/ChracterCreateSelect/Widget/CharacterSelectWidget.h" //캐릭터 선택 위젯 헤더
#include "Client/ErrorWidget/WidgetCancel.h" //에러 확인,취소 위젯 헤더
#include "Client/ErrorWidget/WidgetOk.h" //에러 확인 위젯 헤더
#include "Client/ChracterCreateSelect/CameraActor/ChracterCreateCamera.h" //캐릭터 생성, 선택 맵에 있는 카메라 헤더
#include "Client/MyCharacter/PC/MyCharacter.h" //플레이어 캐릭터 헤더
#include "Client/MyCharacter/PC/Tanker/Tanker.h" //탱커 헤더
#include "Client/MyCharacter/PC/Warrior/Warrior.h" //전사 헤더
#include "Client/MyCharacter/PC/Gunner/Gunner.h" //총잡이 헤더
#include "Client/MyCharacter/PC/MyAnimInstance.h" //선택한 슬롯 캐릭터 애니메이션 재생을 위한 애님인스턴스 헤더
#include "MainMapPlayerController.h" //메인맵 플레이어 컨트롤러 헤더
#include "MainMapOtherPlayerController.h" //메인맵 나를 제외한 플레이어 컨트롤러 헤더
#include "Manager/StageManager.h" //스테이지 관리 액터 컴포넌트 헤더
#include "Client/State/ClientState/ClientState.h" //클라 상태 헤더
#include "Client/State/ClientState/Character/ClientCharacterInGameState.h" //클라 인게임 상태 헤더
#include "Client/State/ClientState/Character/ClientCharacterTitleState.h" //클라 타이틀 상태 헤더
#include "Client/State/ClientState/PC/ClientPCTitleState.h" //클라 플레이어컨트롤러 타이틀 상태 헤더
#include "Client/State/ClientState/PC/ClientPCInGameState.h" //클라 플레이어컨트롤러 인게임 상태 헤더
#include "Client/Menu/MenuWidget.h" //메뉴 위젯 헤더
#include "Client/Menu/ChannelChange/Widget/ChannelChange.h" //채널변경 위젯 헤더
#include "Client/Menu/ChannelChange/Widget/ChannelChangeSlot.h" //채널변경 슬롯 위젯 헤더
#include "Client/MyCharacter/PC/Widget/MyCharacterUI.h" //캐릭터가 소유하고 있는 위젯 헤더
#include "Client/MyCharacter/PC/Widget/CharacterInteraction/ClickCharacterInteraction.h" //캐릭터 상호작용 위젯 헤더
#include "Client/MYCharacter/PC/Widget/Party/Widget/PartyWidget.h" //캐릭터 파티 위젯 헤더
#include "Client/MyCharacter/PC/Widget/Party/Widget/PartyAcceptRejectWidget.h" //캐릭터 파티 수락, 취소 위젯 헤더
#include "Client/MyCharacter/PC/Widget/MainWidget.h" //메인 위젯 헤더
#include "Client/Environment/InGameStartDoor.h"
#include "Client/Monster/Monster.h"
#include "TimerManager.h" //타이머 헤더

//서버 헤더
#include "NetWork/CharacterManager.h"
#include "NetWork/NetworkManager.h"
#include "NetWork/StorageManager.h"

AMainMapGameMode::AMainMapGameMode()
{
	PrimaryActorTick.bCanEverTick = true; //틱 활성화

	StageManager = CreateDefaultSubobject<UStageManager>(TEXT("StageManager")); //스테이지를 관리하는 액터 컴포넌트 생성

	MaxChannelUserCount = 100; //채널 한곳당 최대인원 설정
}

void AMainMapGameMode::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnActorOption;

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

	//로딩 위젯 블루프린트를 Class 형태로 읽어서 LoadingWidgetClass에 저장한다.
	FStringClassReference LoadingWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Loading/W_Loading.W_Loading_C'"));

	//앞에서 읽어 들인 LoadingWidgetClass를 UserWidget클래스 형태로 읽어서 MyWidgetClass에 저장한다.
	if (UClass* MyWidgetClass = LoadingWidgetClass.TryLoadClass<UUserWidget>())
	{
		//읽어 들인 클래스로 위젯을 생성하고 LoadingWidget에 넣는다.
		LoadingWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyWidgetClass);
		LoadingWidget->AddToViewport(); //화면에 붙이고
		LoadingWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
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

	//메인맵 플레이어 컨트롤러를 월드에서 찾아서 넣어준다.
	MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//캐릭터 생성, 선택에 사용할 캐릭터를 월드에 스폰시킨다.
	CreateSelectCharacter = GetWorld()->SpawnActor<AMyCharacter>(CreateSelectCharacter->StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnActorOption);

	if (CreateSelectCharacter) //스폰이 됐으면
	{
		//캐릭터의 상태를 Title상태로 바꿔준다. 
		CreateSelectCharacter->SetClientCharacterState(new ClientCharacterTitleState());

		if (MainMapPlayerController)
		{
			//메인맵 플레이어 컨트롤러로 캐릭터 생성, 선택 캐릭터에 빙의한다.
			MainMapPlayerController->Possess(CreateSelectCharacter);
		}
	}

	TArray <AActor*> InGameStartDoors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInGameStartDoor::StaticClass(), InGameStartDoors);

	if (InGameStartDoors.Num() > 0)
	{
		InGameStartDoor = Cast<AInGameStartDoor>(InGameStartDoors[0]);
	}

	FLatentActionInfo InGameStageAreaMapLoadInfo;
	UGameplayStatics::LoadStreamLevel(this, TEXT("InGameStageArea"), true, true, InGameStageAreaMapLoadInfo);
}

void AMainMapGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PacketData* Data;
	bool isOverlap = false;
	bool ResultFlag;
	bool PartyLeaveResultFlag;
	bool PartyKickResultFlag;
	bool PartyLeaderFlag;

	CharacterInfo* character_info = nullptr;
	float x = 0, y = 0, z = 0; float rx, ry, rz;				// 위치, 회전 넣을 변수
	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnActorOption;
	int UserCount = -1;
	AMyCharacter* MyCharacter = nullptr;
	AMyCharacter* OtherUserCharacter = nullptr;
	AMyCharacter* PartyLeaderCharacter = nullptr;
	AMyCharacter* PreviousPartyLeaderCharacter = nullptr;
	AMyCharacter* PartyUserCharacter = nullptr;
	ATanker* Tanker = nullptr;
	AWarrior* Warrior = nullptr;
	AGunner* Gunner = nullptr;
	AMainMapOtherPlayerController* OtherCharacterController = nullptr;
	ChannelInfo TempchanneleInfo[6];
	ChannelInfo* channelInfo = TempchanneleInfo;
	char TempLeaveCharacterCode[30];
	char* LeaveCharacterCode = TempLeaveCharacterCode;
	bool ChannelChangeFlag;
	int32 S2C_ChannelNum = -1;

	char TempPartyReqCharacterCode[30];
	char* PartyReqCharacterCode = TempPartyReqCharacterCode;
	char TempPartyReqCharacterNickName[20];
	char* PartyReqCharacterNickName = TempPartyReqCharacterNickName;
	char TempPartyLeaveCharacterCode[30];
	char* PartyLeaveCharacterCode = TempPartyLeaveCharacterCode;
	char TempPartyLeaderCharacterCode[30];
	char* PartyLeaderCharacterCode = TempPartyLeaderCharacterCode;
	char TempPreviousPartyLeaderCharacterCode[30];
	char* PreviousPartyLeaderCharacterCode = TempPreviousPartyLeaderCharacterCode;

	int32 PartyRoomNum = -1;
	int32 PartyUserCount = -1;

	PartyUserInfo* PartyUser_Info;

	int MonsterCode=-1;
	int MonsterNum=-1;
	FVector MosterPosition;

	char* Nick;

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
				LoginWidgetToggle();
				CharacterSelectWidgetToggle();

				StorageManager::GetInstance()->PopData();
				CharacterManager::GetInstance()->Character_Req_Slot();
				NetworkClient_main::NetworkManager::GetInstance()->Send();
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
		case  PCHARACTERDATA_DELETE_RESULT:  //캐릭터 삭제 결과
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
				StorageManager::GetInstance()->PopData();
				//****	
				//** 다음 씬 로딩
				//****			
				CharacterSelectWidgetToggle();

				C2S_ReqUserList();
			}
			else
			{
				//****
				//** 게임 시작, 생성 버튼 활성화 후 메세지창 띄우기
				//****ButtonDisable
				CharacterSelectWidget->ButtonEnable();
				ChracterCreateWidget->ButtonEnable();
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
			StorageManager::GetInstance()->ChangeData(Data->data, character_info, S2C_ChannelNum);
			StorageManager::GetInstance()->PopData();
			Channelnum = S2C_ChannelNum;
			GLog->Log(FString::Printf(TEXT("현재 접속중인 채널 : %d"), Channelnum));

			x = character_info->xyz[0]; y = character_info->xyz[1]; z = character_info->xyz[2];

			SpawnLocation = FVector(x, y, z);

			SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

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
				GLog->Log(FString::Printf(TEXT("스폰 위치 X : %f Y : %f Z : %f"), MyCharacter->GetActorLocation().X, MyCharacter->GetActorLocation().Y, MyCharacter->GetActorLocation().Z));
				GLog->Log(ANSI_TO_TCHAR(character_info->code));

				MyCharacter->SetClientCharacterState(new ClientCharacterInGameState(MyCharacter));
				MyCharacter->SetCharacterCode(character_info->code, character_info->nick);
				MyCharacter->SetIsClick(true);

				if (MainMapPlayerController)
				{
					MainMapPlayerController->SetClientPCState(new ClientPCInGameState(this));
					MainMapPlayerController->bShowMouseCursor = false;
					MainMapPlayerController->SetInputMode(FInputModeGameOnly());
					MainMapPlayerController->Possess(MyCharacter);
					MyCharacter->SetDefaultMyCharacter();
					MyCharacter->GetMyCharacterUI()->GetMainWidget()->SetInChannelText(FText::FromString(FString::Printf(TEXT("%d 채널에 입장하셨습니다."), Channelnum)));
				}
			}
			else
			{
				GLog->Log(FString::Printf(TEXT("캐릭터 소환 안됨")));
			}
			// 필요없어진 캐릭터정보 구조체 해제
			delete character_info;
			MyCharacter = nullptr;
			break;
		case PGAMEDATA_USERLIST_COUNT: //현재 채널에 접속한 유저가 몇명인지
			StorageManager::GetInstance()->ChangeData(Data->data, UserCount); //현재 채널에 접속한 유저가 몇명인지 받고
			StorageManager::GetInstance()->PopData();
			GLog->Log(FString::Printf(TEXT("접속한 유저 수 : %d"), UserCount)); //출력해준다.
			break;
		case PGAMEDATA_USERLIST_USER: //나를 제외한 채널에 접속한 유저들을 월드에 스폰시켜주는 함수
			GLog->Log(FString::Printf(TEXT("접속한 다른 유저 월드에 스폰")));
			// 캐릭터 정보 받을 구조체 할당
			character_info = new CharacterInfo;

			memset(character_info, 0, sizeof(CharacterInfo));

			// 캐릭터 정보 서버에서 받은거 넣어줌
			StorageManager::GetInstance()->ChangeData(Data->data, character_info);
			StorageManager::GetInstance()->PopData();

			Nick = character_info->nick;
			GLog->Log(ANSI_TO_TCHAR(character_info->code));

			x = character_info->xyz[0]; y = character_info->xyz[1]; z = character_info->xyz[2];
			rx = character_info->rot_xyz[0]; ry = character_info->rot_xyz[1]; rz = character_info->rot_xyz[2];

			SpawnActorOption.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			SpawnLocation = FVector(x, y, z);
			SpawnRotation = FRotator(rx, ry, rz);

			OtherCharacterController = GetWorld()->SpawnActor<AMainMapOtherPlayerController>(OtherCharacterController->StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnActorOption);

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
				OtherUserCharacter->SetCharacterCode(character_info->code, character_info->nick);

				OtherUserCharacter->SetOtherCharacterController(OtherCharacterController);

				OtherCharacterController->Possess(OtherUserCharacter);

				OtherUserCharacter->SetDefaultOtherCharacter();

				AddLoginUser(OtherUserCharacter);
			}

			// 필요없어진 캐릭터정보 구조체 해제
			delete character_info;
			OtherUserCharacter = nullptr;
			break;
		case PGAMEDATA_CHANNEL_INFO: //메뉴 목록에서 서버변경을 눌럿을때 서버로부터 오는 채널 정보들
			StorageManager::GetInstance()->ChangeData(Data->data, channelInfo); //채널 정보를 받고
			StorageManager::GetInstance()->PopData();

			//내 캐릭터가 소유하고 있는 메인 위젯에 접근하기 위해 내가 현재 조종중인 캐릭터를 구한다.
			MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

			if (MyCharacter) //캐릭터가 존재하면
			{
				//캐릭터가 소유하고 있는 메뉴위젯을 구하고
				auto MenuWidget = Cast<UMenuWidget>(MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetMenuWidget());

				//채널 수만큼 반복하면서 ( 총 채널 6개 )
				for (int i = 0; i < 6; i++)
				{
					if (MenuWidget) //메뉴 위젯이 있는지 확인하고
					{
						//메뉴위젯이 가지고 있는 채널위젯의 채널슬롯에 정보를 업데이트 해준다.
						MenuWidget->GetChannelChangeWidget()->ChannelUpdate(channelInfo[i].channelNum, channelInfo[i].channelUsercount);
					}
				}
			}
			break;
		case PGAMEDATA_LEAVE_PLAYER: //나를 제외한 유저가 로그아웃 or 캐릭터 선택창으로 이동
			memset(TempLeaveCharacterCode, 0, sizeof(TempLeaveCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, LeaveCharacterCode); //서버로부터 로그아웃 or 캐릭터 선택창으로 이동한 캐릭터코드를 받고
			StorageManager::GetInstance()->PopData();

			OtherUserCharacter = GetLoginUser(LeaveCharacterCode);

			if (OtherUserCharacter)
			{
				OtherUserCharacter->AllUIDestroy();
			}

			LoginUserDestory(LeaveCharacterCode); //해당 캐릭터를 삭제한다.
			LeaveCharacterCode = nullptr;
			break;
		case PGAMEDATA_MENU_CHARACTER_SELECT:
			StorageManager::GetInstance()->PopData();
			MainMapPlayerController->SetClientPCState(new ClientPCTitleState());
			MainMapPlayerController->SetSelectIndex(-1);
			CharacterSelectWidget->ButtonEnable();
			break;
		case PGAMEDATA_MENU_LOGOUT:
			StorageManager::GetInstance()->PopData();
			MainMapPlayerController->SetClientPCState(new ClientPCTitleState());
			MainMapPlayerController->SetSelectIndex(-1);
			CharacterSelectWidget->ButtonEnable();
			break;
		case PGAMEDATA_CHANNEL_REQ_CHANGE: //채널 변경 눌럿을때
			LoadingWidgetHiddenScreen();

			StorageManager::GetInstance()->ChangeData(Data->data, ChannelChangeFlag, S2C_ChannelNum);
			StorageManager::GetInstance()->PopData();

			if (ChannelChangeFlag)
			{
				if (MainMapPlayerController)
				{
					MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

					if (MyCharacter)
					{
						LoginUserAllDestory();
						Channelnum = S2C_ChannelNum;
						MyCharacter->GetMyCharacterUI()->GetMainWidget()->SetInChannelText(FText::FromString(FString::Printf(TEXT("%d 채널에 입장하셨습니다."), Channelnum)));
						MainMapPlayerController->C2S_ReqUserList();
					}
				}
			}
			break;
		case PGAMEDATA_PARTY_INVITE:
			memset(TempPartyReqCharacterCode, 0, sizeof(TempPartyReqCharacterCode));
			memset(TempPartyReqCharacterNickName, 0, sizeof(TempPartyReqCharacterNickName));

			StorageManager::GetInstance()->ChangeData(Data->data, PartyRoomNum, PartyReqCharacterCode, PartyReqCharacterNickName);
			StorageManager::GetInstance()->PopData();

			if (MainMapPlayerController)
			{
				MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

				if (MyCharacter)
				{
					MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartyAcceptRejectWidget()->SetPartyRequestCharacterSetInfo(PartyReqCharacterNickName, PartyReqCharacterCode, PartyRoomNum);
					MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyAcceptRejectWidgetVisible();
				}
			}
			break;
		case PGAMEDATA_PARTY_INFO:
			StorageManager::GetInstance()->ChangeData(Data->data, PartyRoomNum, PartyUserCount);
			StorageManager::GetInstance()->PopData();

			MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

			if (MyCharacter)
			{
				MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeave();
				MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyWidgetVisible();
			}

			GLog->Log(FString::Printf(TEXT("파티 수 : %d"), PartyUserCount));

			break;
		case PGAMEDATA_PARTY_USER_INFO:
			PartyUser_Info = new PartyUserInfo();

			memset(PartyUser_Info, 0, sizeof(PartyUserInfo));

			StorageManager::GetInstance()->ChangeData(Data->data, PartyUser_Info);
			StorageManager::GetInstance()->PopData();

			MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

			if (MyCharacter)
			{
				if (!strcmp(MyCharacter->GetCharacterCode(), PartyUser_Info->code) == 0)
				{
					PartyUserCharacter = GetLoginUser(PartyUser_Info->code);
				}
				else
				{
					PartyUserCharacter = MyCharacter;
				}

				MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyJoin(PartyUserCharacter, PartyUser_Info->code, PartyUser_Info->job_code, PartyUser_Info->nick, PartyUser_Info->hp, PartyUser_Info->mp, PartyUser_Info->leader);
			}

			delete PartyUser_Info;
			break;
		case PGAMEDATA_PARTY_LEAVE_RESULT:
			StorageManager::GetInstance()->ChangeData(Data->data, PartyLeaveResultFlag);
			StorageManager::GetInstance()->PopData();

			if (PartyLeaveResultFlag)
			{
				MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				if (MyCharacter)
				{
					MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeave();
				}
			}
			break;
		case PGAMEDATA_PARTY_LEAVE_INFO:
			memset(TempPartyLeaveCharacterCode, 0, sizeof(TempPartyLeaveCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, PartyLeaveCharacterCode);
			StorageManager::GetInstance()->PopData();

			MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			if (MyCharacter)
			{
				MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeave(PartyLeaveCharacterCode);
			}
			break;
		case PGAMEDATA_PARTY_PARTYROOM_REMOVE:
			StorageManager::GetInstance()->PopData();

			MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			if (MyCharacter)
			{
				MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeave();
			}
			break;
		case PGAMEDATA_PARTY_KICK: //강퇴 당한 파티원이 받는 프로토콜
			StorageManager::GetInstance()->PopData();

			MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			if (MyCharacter)
			{
				MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeave();
			}
			break;
		case PGAMEDATA_PARTY_USER_KICK_INFO: //파티장과 강퇴 당한 애를 제외한 나머지 파티원이 받는 프로토콜
			memset(TempPartyLeaveCharacterCode, 0, sizeof(TempPartyLeaveCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, PartyLeaveCharacterCode);
			StorageManager::GetInstance()->PopData();

			MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			if (MyCharacter)
			{
				MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeave(PartyLeaveCharacterCode);
			}
			break;
		case PGAMEDATA_PARTY_USER_KICK_RESULT: //강퇴 햇을때 파티장이 받는 프로토콜
			memset(TempPartyLeaveCharacterCode, 0, sizeof(TempPartyLeaveCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, PartyKickResultFlag, PartyLeaveCharacterCode);
			StorageManager::GetInstance()->PopData();

			if (PartyKickResultFlag)
			{
				MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				if (MyCharacter)
				{
					MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeave(PartyLeaveCharacterCode);
				}
			}
			break;
		case PGAMEDATA_PARTY_LEADER_DELEGATE_RESULT: //파티장 위임 결과 성공이면 파티장 코드 
			memset(TempPartyLeaderCharacterCode, 0, sizeof(TempPartyLeaderCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, PartyLeaderFlag, PartyLeaderCharacterCode);
			StorageManager::GetInstance()->PopData();

			if (PartyLeaderFlag)
			{
				MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

				if (MyCharacter)
				{
					MyCharacter->SetPartyLeader(false);
				}

				PartyLeaderCharacter = GetLoginUser(PartyLeaderCharacterCode);

				if (PartyLeaderCharacter)
				{
					PartyLeaderCharacter->SetPartyLeader(true);
				}

				if (MyCharacter)
				{
					MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeaderUpdate();
				}
			}
			break;
		case PGAMEDATA_PARTY_LEADER_INFO: //새로운 파티장 정보 코드
			memset(TempPreviousPartyLeaderCharacterCode, 0, sizeof(TempPreviousPartyLeaderCharacterCode));
			memset(TempPartyLeaderCharacterCode, 0, sizeof(TempPartyLeaderCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, PreviousPartyLeaderCharacterCode, PartyLeaderCharacterCode);
			StorageManager::GetInstance()->PopData();

			MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

			if (MyCharacter)
			{
				PreviousPartyLeaderCharacter = GetLoginUser(PreviousPartyLeaderCharacterCode);

				if (PreviousPartyLeaderCharacter)
				{
					PreviousPartyLeaderCharacter->SetPartyLeader(false);
				}

				PartyLeaderCharacter = GetLoginUser(PartyLeaderCharacterCode);

				if (PartyLeaderCharacter)
				{
					PartyLeaderCharacter->SetPartyLeader(true);
				}
				else
				{
					PartyLeaderCharacter = MyCharacter;
					PartyLeaderCharacter->SetPartyLeader(true);
				}

				MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeaderUpdate();
			}
			break;
		case PGAMEDATA_PARTY_DUNGEON_ENTER_RESULT: 
			StorageManager::GetInstance()->ChangeData(Data->data, UserCount); 
			StorageManager::GetInstance()->PopData();

			MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

			MyCharacter->GetMyCharacterUI()->GetMainWidget()->SetGameStageStartCountInit(10);

			DungeonIn();
			break;
		case PGAMEDATA_PARTY_DUNGEON_SPAWNINFO:
			memset(TempPartyReqCharacterCode, 0, sizeof(TempPartyReqCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, PartyReqCharacterCode, x, y, z);
			StorageManager::GetInstance()->PopData();
						
			MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

			if (MyCharacter)
			{
				for (int i = 0; i < MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartySize(); i++)
				{
					FPartySlot PartySlot = MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartySlot(i);

					if (strcmp(PartySlot.CharacterCode, PartyReqCharacterCode) == 0)
					{
						PartySlot.PartyUser->SetActorLocation(FVector(x, y, z));
					}
				}
			}
			break;
		case PGAMEDATA_MONSTER_MOVE_INFO: // 몬스터 이동정보 - ([int] 몬스터코드, [int] 몬스터숫자, [float*3] 좌표)
			StorageManager::GetInstance()->ChangeData(Data->data, MonsterCode, MonsterNum, MosterPosition.X, MosterPosition.Y, MosterPosition.Z);
			StorageManager::GetInstance()->PopData();
			
			Get_MonsterPosition(StageManager->GetObjectPool()->Get_SpawnMoster_Map(), static_cast<MONSTER_CODE>(MonsterCode), MonsterNum, MosterPosition); //Get_SpawnMoster_Map(), static_cast<MONSTER_CODE>(MonsterCode),MonsterNum,MosterPosition);
			break;
		case PGAMEDATA_PARTY_DUNGEON_STAGE_ENTER_RESULT:
			StorageManager::GetInstance()->ChangeData(Data->data, UserCount); 
			StorageManager::GetInstance()->PopData();

			break;
		case PGAMEDATA_PARTY_DUNGEON_STAGE_SPAWNINFO:
			memset(TempPartyReqCharacterCode, 0, sizeof(TempPartyReqCharacterCode));

			StorageManager::GetInstance()->ChangeData(Data->data, PartyReqCharacterCode, x, y, z);
			StorageManager::GetInstance()->PopData();
		
			GameStageStartSpawnLocation.X = x;
			GameStageStartSpawnLocation.Y = y;
			GameStageStartSpawnLocation.Z = z;

			MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

			if (MyCharacter)
			{
				for (int i = 0; i < MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartySize(); i++)
				{
					FPartySlot PartySlot = MyCharacter->GetMyCharacterUI()->GetMainWidget()->GetPartySlot(i);

					if (strcmp(PartySlot.CharacterCode, PartyReqCharacterCode) == 0)
					{
						PartySlot.PartyUser->SetActorLocation(GameStageStartSpawnLocation);
						PartySlot.PartyUser->SpawnGameStageStartEffect();
					}
				}

				//파티장 게임시작 버튼 활성화 몬스터 정보 0.2s초마다 서버로 보냄
				if (MyCharacter->GetPartyLeader())
				{
					MyCharacter->SetC2SMonsterInfoAssemble(); //스테이지 클리어하면 꺼주는 작업 필요
					MyCharacter->GetMyCharacterUI()->GetMainWidget()->PartyLeaderGameStartWidgetToggle();
				}
			}
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
		LoadingWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainMapGameMode::LoadingWidgetHiddenScreen()
{
	if (LoadingWidget)
	{
		LoadingWidget->SetVisibility(ESlateVisibility::Hidden);
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

void AMainMapGameMode::AddLoginUser(AMyCharacter * _OtherCharacter)
{
	if (_OtherCharacter)
	{
		OtherLoginUserList.Add(_OtherCharacter);
		CurrentChannelUserCount = OtherLoginUserList.Num();
	}
}

void AMainMapGameMode::DeleteLoginUser(AMyCharacter * _OtherCharacter)
{
	if (_OtherCharacter)
	{
		OtherLoginUserList.RemoveSingle(_OtherCharacter);
		CurrentChannelUserCount = OtherLoginUserList.Num();
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

void AMainMapGameMode::LoginUserDestory(char * _OtherCharacterCode)
{
	auto DestoryOtherCharacter = GetLoginUser(_OtherCharacterCode);

	if (DestoryOtherCharacter)
	{
		DeleteLoginUser(DestoryOtherCharacter);

		//안켜져 있는 캐릭터 UI도 끄는 작업을 함 수정필요
		DestoryOtherCharacter->GetMyCharacterUI()->GetMyCharacterInteraction()->MyCharacterWidgetHidden();

		DestoryOtherCharacter->Destroy();
	}
	else
	{
		GLog->Log(FString::Printf(TEXT("삭제 하려는 캐릭터가 존재하지 않음")));
	}
}

void AMainMapGameMode::LoginUserAllDestory()
{
	for (int i = 0; i < OtherLoginUserList.Num(); i++)
	{
		if (OtherLoginUserList[i])
		{
			OtherLoginUserList[i]->GetMyCharacterUI()->GetMyCharacterInteraction()->MyCharacterWidgetHidden();
			OtherLoginUserList[i]->Destroy();
		}
	}

	OtherLoginUserList.Empty();
}

float AMainMapGameMode::GetCurrentChannelUserCount()
{
	return CurrentChannelUserCount;
}

float AMainMapGameMode::GetMaxChannelUserCount()
{
	return MaxChannelUserCount;
}

int32 AMainMapGameMode::GetChannelNum()
{
	return Channelnum;
}

void AMainMapGameMode::C2S_ReqUserList()
{
	SelectCharacterDestroy();

	if (MainMapPlayerController)
	{
		MainMapPlayerController->C2S_ReqUserList(); //서버에 다른 유저 리스트 요청
	}
}

AMyCharacter * AMainMapGameMode::GetCreateSelectCharacter()
{
	return CreateSelectCharacter;
}

void AMainMapGameMode::OpenDoor()
{
	if (InGameStartDoor)
	{
		InGameStartDoor->OpenDoor();
	}
}

void AMainMapGameMode::CloseDoor()
{
	if (InGameStartDoor)
	{
		InGameStartDoor->CloseDoor();
	}
}

void AMainMapGameMode::DungeonIn()
{
	LoadingWidgetViewScreen();

	FLatentActionInfo InGameStageAreaMapLoadInfo;

	UGameplayStatics::LoadStreamLevel(this, TEXT("MainStageStartArea"), true, true, InGameStageAreaMapLoadInfo); //던전 안 레벨 메모리 로드

	FTimerHandle FadeInEndTimer; //FadeOut용 타이머

	auto MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn()); //내가 조종하고 있는캐릭터를 가져와서      

	if (MyCharacter)
	{
		MyCharacter->AllUIHidden(); //UI를 모두 다 숨겨준다.
	}

	for (int i = 0; i < OtherLoginUserList.Num(); i++)
	{
		OtherLoginUserList[i]->MyCharacterNickWidgetHidden(); //다른 유저의 이름 UI도 숨겨준다.
	}

	FTimerHandle DungeonInRecoveryTimer;
	GetWorld()->GetTimerManager().SetTimer(DungeonInRecoveryTimer,this, &AMainMapGameMode::DungeonInRecovery, 1.5f, false);
}

void AMainMapGameMode::DungeonInRecovery()
{
	LoadingWidgetHiddenScreen();

	auto MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn()); //내가 조종하고 있는 캐릭터를 가져온다.

	if (MyCharacter)
	{
		//모든 UI를 다 보여준다.
		MyCharacter->AllUIVisible();
	}

	for (int i = 0; i < OtherLoginUserList.Num(); i++)
	{
		OtherLoginUserList[i]->MyCharacterNickWidgetVisible(); //다른 유저의 이름 UI를 보여준다.
	}
}

UStageManager * AMainMapGameMode::GetStageManager()
{
	return StageManager;
}

void AMainMapGameMode::Get_MonsterPosition(TMap<MONSTER_CODE, FMonsterstruct>_MonsterMapData,MONSTER_CODE _MC,int _Num, FVector _MosterPosition)
{
	if (_MonsterMapData[_MC].Monster_Volum_Array[_Num] == nullptr)
	{
		//GLog->Log(FString::Printf(TEXT("Get Monster* is Fail")));
		UE_LOG(LogTemp, Error, TEXT("Get MonsterPosition is Fail\ngo To MainMapGameMode, Check to Get_MonsterPosition Function"));
	}
	else
	{
		FVector TempbeforeMonsterPosition = _MonsterMapData[_MC].Monster_Volum_Array[_Num]->GetActorLocation();
		//GLog->Log(FString::Printf(TEXT("before MonsterPosition: %f,%f,%f"),_MonsterMapData[_MC].Monster_Volum_Array[_Num]->GetActorLocation().X, _MonsterMapData[_MC].Monster_Volum_Array[_Num]->GetActorLocation().Y, _MonsterMapData[_MC].Monster_Volum_Array[_Num]->GetActorLocation().Z));
		
		_MonsterMapData[_MC].Monster_Volum_Array[_Num]->S2C_LocationUpdate(_MosterPosition);
		//_MonsterMapData[_MC].Monster_Volum_Array[_Num]->SetActorLocation(_MosterPosition);

		FVector TempAfterMonsterPosition = _MonsterMapData[_MC].Monster_Volum_Array[_Num]->GetActorLocation();
		//GLog->Log(FString::Printf(TEXT("After MonsterPosition: %f,%f,%f"), _MonsterMapData[_MC].Monster_Volum_Array[_Num]->GetActorLocation().X, _MonsterMapData[_MC].Monster_Volum_Array[_Num]->GetActorLocation().Y, _MonsterMapData[_MC].Monster_Volum_Array[_Num]->GetActorLocation().Z));
		
		//UE_LOG(LogTemp, Warning, TEXT("Gap MonsterPosition X: %d, Y: %d, Z: %d"), TempbeforeMonsterPosition.X - TempAfterMonsterPosition.X, TempbeforeMonsterPosition.Y - TempAfterMonsterPosition.Y, TempbeforeMonsterPosition.Z - TempAfterMonsterPosition.Z);
	}
}

AMainMapPlayerController * AMainMapGameMode::GetMainMapPlayerController()
{
	if (MainMapPlayerController)
	{
		return MainMapPlayerController;
	}
	else
	{
		return nullptr;
	}
}
