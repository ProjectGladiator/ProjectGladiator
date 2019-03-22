// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Client/MyCharacter/Widget/CharacterInteraction/Structure/FClickCharacterInfo.h"
#include "PartyAcceptRejectWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTJ_API UPartyAcceptRejectWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UTextBlock* PartyInvitedCharacterNick;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* PartyAcceptButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
		class UButton* PartyRejectButton;
	char PartyReqCharacterCode[30];
	char* PartyReqCharacterNickName = nullptr;
	int32 PartyRoomNum = -1;
public:
	virtual void NativeConstruct() override;

	//PartyRequestCharacterSetInfo
	void SetPartyRequestCharacterSetInfo(char* _PartyReqCharacterNickName, char* _PartyReqCharacterCode, int32 _PartyRoomNum);

	UFUNCTION()
		void PartyAccept();
	UFUNCTION()
		void PartyReject();
};
