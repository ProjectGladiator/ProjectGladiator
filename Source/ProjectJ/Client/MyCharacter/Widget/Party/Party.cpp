// Fill out your copyright notice in the Description page of Project Settings.

#include "Party.h"
//클라 헤더
#include "Kismet/GameplayStatics.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyWidget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartySlotWiget.h"
#include "Client/MyCharacter/Widget/Party/Widget/PartyAcceptRejectWidget.h"

//서버 헤더

// Sets default values for this component's properties
UParty::UParty()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UParty::BeginPlay()
{
	Super::BeginPlay();

	FStringClassReference PartyWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Party/W_Party.W_Party_C'"));

	if (UClass* MyPartyWidgetClass = PartyWidgetClass.TryLoadClass<UUserWidget>())
	{
		PartyWidget = Cast<UPartyWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MyPartyWidgetClass));

		PartyWidget->AddToViewport(); //화면에 붙인다.
		PartyWidget->SetVisibility(ESlateVisibility::Hidden); //숨긴다.
	}	

	FStringClassReference PartyAcceptRejectWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Party/W_PartyAcceptReject.W_PartyAcceptReject_C'"));

	if (UClass* MyPartyAcceptRejectWidgetClass = PartyAcceptRejectWidgetClass.TryLoadClass<UUserWidget>())
	{
		PartyAcceptRejectWidget = Cast<UPartyAcceptRejectWidget>(CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(),0),MyPartyAcceptRejectWidgetClass));
	}
}


// Called every frame
void UParty::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UParty::PartyWidgetToggle()
{
	if (PartyWidget)
	{
		if (PartyWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			PartyWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			PartyWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UParty::PartyAcceptRejectWidgetVisible()
{
	if (PartyAcceptRejectWidget)
	{
		PartyWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UParty::PArtyAcceptRejectWidgetHidden()
{
	if (PartyAcceptRejectWidget)
	{
		PartyWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

UPartyWidget * UParty::GetPartyWidget()
{
	return PartyWidget;
}

bool UParty::PartyJoin(AMyCharacter* _MyCharacter)
{
	if (PartyWidget)
	{
		if (_MyCharacter)
		{
			UPartySlotWiget* PartySlotWidget = PartyWidget->PartySlotCreate(); //파티 슬롯을 만든다.

			if (PartySlotWidget) //만든 파티슬롯의 정보를 업데이트 한다.
			{
				FPartySlot PartySlot;
				PartySlot.MyCharacter = _MyCharacter;
				int32 Index = PartySlots.Num();
				PartySlotWidget->PartySlotUpdate(PartySlot,Index);
				PartySlots.Add(PartySlot);

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			GLog->Log(FString::Printf(TEXT("상대방 캐릭터가 존재 하지 않음")));
			return false;
		}
	}
	else
	{
		return false;
	}
}