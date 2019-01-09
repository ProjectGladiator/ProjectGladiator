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
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		TArray <AActor*> Cameras;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		class AChracterCreateCamera* CharacterCreateCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		class AChracterCreateCamera* CharacterSelectCamera;
	int32 JobCode;
	int32 Select_index = -1;
public:
	CharacterSlot * CharacterSlotInfo;

	virtual void BeginPlay() override;

	void ToCharacterCreate();
	void ToCharacterSelect();

	void SelectCharacter(int NewJobCode);
	
	int32 GetJobCode();
	int32 GetSelectIndex();
	
	void SetSelectIndex(int32 _SelectIndex);

};
