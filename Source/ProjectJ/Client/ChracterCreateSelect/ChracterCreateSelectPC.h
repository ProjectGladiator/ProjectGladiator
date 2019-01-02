// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChracterCreateSelectPC.generated.h"
/**
 * 
 */
struct CharacterSlot;
UCLASS()
class PROJECTJ_API AChracterCreateSelectPC : public APlayerController
{
	GENERATED_BODY()
public:
	TArray <AActor*> Cameras;
	class AChracterCreateCamera* CharacterCreateCamera;
	class AChracterCreateCamera* CharacterSelectCamera;

	int JobCode;
	int select_index;

	CharacterSlot* CharacterSlotInfo;

	virtual void BeginPlay() override;	

	void ToCharacterCreate();
	void ToCharacterSelect();

	void SelectCharacter(int NewJobCode);
};
