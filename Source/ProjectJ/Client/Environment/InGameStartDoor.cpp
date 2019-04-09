// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameStartDoor.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "Client/MyCharacter/Widget/MyCharacterUI.h"
#include "Client/MyCharacter/Widget/MainWidget.h"
#include "Kismet/GameplayStatics.h"

//서버 헤더

// Sets default values
AInGameStartDoor::AInGameStartDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorBody"));
	SetRootComponent(DoorBody);

	if (DoorBody)
	{
		DoorBody->SetCollisionProfileName(TEXT("OverlapAll"));
	}

	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(GetRootComponent());

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_DoorBody(TEXT("StaticMesh'/Game/Assets/MedievalDungeon/Mesh/SM_Crypt_Doorway.SM_Crypt_Doorway'"));

	if (SM_DoorBody.Succeeded())
	{
		DoorBody->SetStaticMesh(SM_DoorBody.Object);
	}

	DoorBody->SetRelativeScale3D(FVector(2.0f, 1.0f, 2.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_DoorLeft(TEXT("StaticMesh'/Game/Assets/MedievalDungeon/Mesh/SM_DoorWay_Large_Door_Left.SM_DoorWay_Large_Door_Left'"));

	if (SM_DoorLeft.Succeeded())
	{
		DoorLeft->SetStaticMesh(SM_DoorLeft.Object);
	}

	DoorLeft->SetRelativeLocation(FVector(-128.0f, 10.0f, 0));
	//DoorLeft->SetRelativeRotation(FRotator(0, -190.0f, 0));
	DoorLeft->SetRelativeRotation(FRotator(0, -90.0f, 0));
	DoorLeft->SetRelativeScale3D(FVector(1.0f, 2.0f, 1.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_DoorRight(TEXT("StaticMesh'/Game/Assets/MedievalDungeon/Mesh/SM_DoorWay_Large_Door_Right.SM_DoorWay_Large_Door_Right'"));

	if (SM_DoorRight.Succeeded())
	{
		DoorRight->SetStaticMesh(SM_DoorRight.Object);
	}

	DoorRight->SetRelativeLocation(FVector(128.0f, 10.0f, 0));
	//DoorRight->SetRelativeRotation(FRotator(0, 10.0f, 0));
	DoorRight->SetRelativeRotation(FRotator(0, -90.0f, 0));
	DoorRight->SetRelativeScale3D(FVector(1.0f, 2.0f, 1.0f));

	InDunGeonColision = CreateDefaultSubobject<UBoxComponent>(TEXT("InDunGeonColision"));

	if (InDunGeonColision)
	{
		InDunGeonColision->SetupAttachment(GetRootComponent());
		InDunGeonColision->SetRelativeLocation(FVector(0, 144.0f, 160.0f));
		InDunGeonColision->SetRelativeScale3D(FVector(5.7f, 5.0f, 5.7f));
		InDunGeonColision->SetCollisionProfileName(TEXT("OverlapAll"));
	}

	OpenDoorFlag = false;
	IsInDungeonMessage = true;
}

// Called when the game starts or when spawned
void AInGameStartDoor::BeginPlay()
{
	Super::BeginPlay();

	if (InDunGeonColision)
	{
		InDunGeonColision->OnComponentBeginOverlap.AddDynamic(this, &AInGameStartDoor::InDunGeonBeginOverlap);
	}
}

// Called every frame
void AInGameStartDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DoorLeft && DoorRight)
	{
		FRotator LeftRotation;
		FRotator RightRotation;

		if (OpenDoorFlag)
		{
			LeftRotation = FMath::RInterpTo(DoorLeft->GetComponentRotation(), FRotator(0, -190.0f, 0), DeltaTime, 0.5f);
			RightRotation = FMath::RInterpTo(DoorRight->GetComponentRotation(), FRotator(0, 10.0f, 0), DeltaTime, 0.5f);
		}
		else
		{
			LeftRotation = FMath::RInterpTo(DoorLeft->GetComponentRotation(), FRotator(0, -90.0f, 0), DeltaTime, 0.5f);
			RightRotation = FMath::RInterpTo(DoorRight->GetComponentRotation(), FRotator(0, -90.0f, 0), DeltaTime, 0.5f);
		}

		DoorLeft->SetRelativeRotation(LeftRotation);
		DoorRight->SetRelativeRotation(RightRotation);
	}
}

void AInGameStartDoor::InDunGeonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto BeginOverlapCharacter = Cast<AMyCharacter>(OtherActor);

	if (BeginOverlapCharacter)
	{
		bool IsPartyLeader = BeginOverlapCharacter->GetPartyLeader();

		if (IsPartyLeader)
		{
			bool IsDunGeonMessageWidgetVisibleFlag = BeginOverlapCharacter->GetMyCharacterUI()->GetMainWidget()->IsDunGeonMessageWidgetVisible();

			if (!IsDunGeonMessageWidgetVisibleFlag)
			{
				if (IsInDungeonMessage)
				{
					BeginOverlapCharacter->GetMyCharacterUI()->GetMainWidget()->InDunGeonMessageWidgetVisible();
					IsInDungeonMessage = false;
				}
			}
		}
	}
}

void AInGameStartDoor::OpenDoor()
{
	OpenDoorFlag = true;
}

void AInGameStartDoor::CloseDoor()
{
	OpenDoorFlag = false;
}

void AInGameStartDoor::Init()
{	
	IsInDungeonMessage = true;
}

