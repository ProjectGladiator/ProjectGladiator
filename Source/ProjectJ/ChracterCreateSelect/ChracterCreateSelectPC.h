// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Network/StorageManager.h"
#include "ChracterCreateSelectPC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJ_API AChracterCreateSelectPC : public APlayerController
{
	GENERATED_BODY()
public:
	TArray <AActor*> Cameras;
	class UTitleCharacterSelectWidget* CharacterSelectWidget;//캐릭터 선택 위젯
	class UTitleCharacterCreateWidget* ChracterCreateWidget; //캐릭터 생성 위젯
	class AChracterCreateCamera* CharacterCreateCamera;
	class AChracterCreateCamera* CharacterSelectCamera;
	virtual void BeginPlay() override;	

	void ToCharacterCreate();
	void ToCharacterSelect();
	void CharacterSelectWidgetToggle();
	void CharacterCreateWidgetToggle();
	
	CharacterSlot* CharacterSlotInfo;
};
