// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetOk.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API UWidgetOk : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UTextBlock* ErrorMessageOK; //에러메시지
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* OkButton; //확인 버튼
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		class UButton* CloseButton; //닫기 버튼
	class AMyPlaterController* PC;

	virtual void NativeConstruct() override;
	
	//에러메세지를 셋팅해주는 함수
	void SetErrorMessage(const FText& Message);
	UFUNCTION()
	void Ok(); //확인 버튼 누르면 실행하는 함수
	UFUNCTION()
	void Close(); //닫기 버튼 누르면 실행하는 함수
};
