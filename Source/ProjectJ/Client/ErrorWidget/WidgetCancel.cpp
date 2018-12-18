// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetCancel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Client/Title/TitlePlayerController.h"

#include "Kismet/GameplayStatics.h"

void UWidgetCancel::NativeConstruct()
{
	Super::NativeConstruct();
	
	//위젯 블루프린트에 있는 ErrorMessage를 가져와서 ErrorMessage에 넣는다.
	ErrorMessage = Cast<UTextBlock>(GetWidgetFromName(TEXT("ErrorMessage")));
	//위젯 블루프린트에 있는 RetryButton를 가져와서 RetryButton에 넣는다.
	RetryButton = Cast<UButton>(GetWidgetFromName(TEXT("RetryButton")));
	//위젯 블루프린트에 있는 CancelButton를 가져와서 CancelButton에 넣는다.
	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));
	//위젯 블루프린트에 있는 CloseButton를 가져와서 CloseButton에 넣는다.
	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));


	if (RetryButton)
	{
		//다시시도 버튼을 클릭하면 Retry함수를 실행한다.
		RetryButton->OnClicked.AddDynamic(this, &UWidgetCancel::Retry);
	}

	if (CancelButton)
	{
		//취소 버튼을 클릭하면 Cancel함수를 실생한다
		CancelButton->OnClicked.AddDynamic(this, &UWidgetCancel::Cancel);
	}

	if (CloseButton)
	{
		//닫기 버튼을 클릭하면 Close함수를 실행한다.
		CloseButton->OnClicked.AddDynamic(this, &UWidgetCancel::Close);
	}

	//ATitlePlayerController를 얻는다.
	PC = Cast<ATitlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UWidgetCancel::Retry()
{
	//위젯을 숨긴다.
	SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetCancel::Cancel()
{
	//위젯을 숨긴다.
	SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetCancel::Close()
{
	//위젯을 숨긴다.
	SetVisibility(ESlateVisibility::Hidden);
}


void UWidgetCancel::SetErrorMessage(const FText& Message)
{
	//매개변수로 받아온 에러메세지를 
	if (ErrorMessage)
	{
		//셋팅한다.
		ErrorMessage->SetText(Message);
	}
}
