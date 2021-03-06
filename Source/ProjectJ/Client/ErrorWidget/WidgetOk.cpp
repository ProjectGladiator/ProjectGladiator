﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetOk.h"
//클라 헤더
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWidgetOk::NativeConstruct()
{
	Super::NativeConstruct(); 
	//위젯 블루프린트에 있는 ErrorMessage를 가져와서 ErrorMessage에 넣는다.
	ErrorMessageOK = Cast<UTextBlock>(GetWidgetFromName(TEXT("ErrorMessageOK")));
	//위젯 블루프린트에 있는 OkButton를 가져와서 OkButton에 넣는다.
	OkButton = Cast<UButton>(GetWidgetFromName(TEXT("OkButton")));
	//위젯 블루프린트에 있는 CloseButton를 가져와서 CloseButton에 넣는다.
	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	if (OkButton)
	{
		//확인 버튼을 클릭하면 Ok함수를 실행한다.
		OkButton->OnClicked.AddDynamic(this, &UWidgetOk::Ok);
	}

	if (CloseButton)
	{
		//닫기 버튼을 클릭하면 Ok함수를 실행한다.
		CloseButton->OnClicked.AddDynamic(this, &UWidgetOk::Close);
	}
}

void UWidgetOk::SetErrorMessage(const FText & Message)
{
	//매개변수로 받아온 에러메세지를 
	if (ErrorMessageOK)
	{
		//셋팅한다.
		ErrorMessageOK->SetText(Message);
	}
}

void UWidgetOk::Ok()
{
	//위젯을 숨긴다.
	SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetOk::Close()
{
	//위젯을 숨긴다.
	SetVisibility(ESlateVisibility::Hidden);
}