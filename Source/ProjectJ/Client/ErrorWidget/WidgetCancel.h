// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetCancel.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UWidgetCancel : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UTextBlock* ErrorMessage; //에러메시지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* RetryButton; //다시시도 버튼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* CancelButton; //취소 버튼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", Meta = (AllowPrivateAccess = true))
		class UButton* CloseButton; //닫기 버튼
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void Retry(); //다시 시도 버튼 누르면 실행하는 함수
	UFUNCTION()
		void Cancel(); //취소 버튼 누르면 실행하는 함수
	UFUNCTION()
		void Close(); //닫기 버튼 누르면 실행하는 함수
	//에러메세지를 셋팅해주는 함수
	void SetErrorMessage(const FText& Message);
};
