// Fill out your copyright notice in the Description page of Project Settings.

#include "ChattingWidget.h"
//클라 헤더
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
//#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "Client/MainMap/MainMapPlayerController.h"
#include "ChattingMessageWidget.h"
#include "Client/MyCharacter/PC/MyCharacter.h"
#include "kismet/KismetStringLibrary.h"
//서버 헤더

void UChattingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*ChannelListBox = Cast<UComboBoxString>(GetWidgetFromName(TEXT("ChannelListBox")));

	if (ChannelListBox)
	{
		GLog->Log(FString::Printf(TEXT("채널리스트 박스 있음")));
		ChannelListBox->SetRenderAngle(180.0f);
		ChannelListBox->AddOption(FString::Printf(TEXT("전체")));
	}*/

	ChattingInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ChattingInputBox")));

	if (ChattingInputBox)
	{
		ChattingInputBox->OnTextCommitted.AddDynamic(this, &UChattingWidget::ChattingSend);
	}

	ChattingScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("ChattingScrollBox")));

}

void UChattingWidget::ChattingStart()
{
	if (ChattingInputBox)
	{
		ChattingInputBox->SetKeyboardFocus();
	}
}

void UChattingWidget::ChattingSend(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		auto MainMapPlayerController = Cast<AMainMapPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (MainMapPlayerController)
		{
			MainMapPlayerController->SetInputMode(FInputModeGameOnly());

			FStringClassReference ChattingMessageWidgetClass(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/Chatting/W_ChattingMessageWidget.W_ChattingMessageWidget_C'"));

			if (UClass* MyWidgetClass = ChattingMessageWidgetClass.TryLoadClass<UUserWidget>())
			{
				auto ChattingMessageWidget = Cast<UChattingMessageWidget>(CreateWidget<UUserWidget>(MainMapPlayerController, MyWidgetClass));

				if (ChattingMessageWidget)
				{
					auto MyCharacter = Cast<AMyCharacter>(MainMapPlayerController->GetPawn());

					FText FinalChattingMessage = FText::FromString(FString::Printf(TEXT("%s : %s"), ANSI_TO_TCHAR(MyCharacter->GetCharacterNickName()), *Text.ToString()));
					
					ChattingMessageWidget->ChattingMessageSet(FinalChattingMessage);

					ChattingMessages.Add(ChattingMessageWidget);

					if (ChattingScrollBox)
					{
						ChattingScrollBox->AddChild(ChattingMessageWidget);
						ChattingScrollBox->ScrollToEnd();
						ChattingInputBox->SetText(FText::FromString(FString::Printf(TEXT(""))));
					}
				}
				else
				{
					GLog->Log(FString::Printf(TEXT("ChattingMessageWidget 없음")));
				}
			}
		}
	}
}
