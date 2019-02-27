// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Client/State/ClientState/ClientState.h"
#include "MainMapPlayerController.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FControlOtherCharacterMoveDelegate, FVector&, Location);
DECLARE_DYNAMIC_DELEGATE_OneParam(FControlOtherCharacterRotateDelegate, FRotator&, Rotation);

/**
 *
 */
struct CharacterSlot;

UCLASS()
class PROJECTJ_API AMainMapPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainMapPlayerController();
private:
	UPROPERTY()
		EClientState ClientCurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		TArray <AActor*> Cameras; //캐릭터 선택, 생성 카메라들을 담아둘 배열
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		class AChracterCreateCamera* CharacterCreateCamera; //캐릭터 생성창 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras, Meta = (AllowPrivateAccess = true))
		class AChracterCreateCamera* CharacterSelectCamera; //캐릭터 선택창 카메라
	UPROPERTY()
		class AChracterCreateCamera* CharacterSelectZoomInCamera;
	UPROPERTY()
		class AMainMapGameMode* MainMapGameMode;
	int32 JobCode;
	int32 Select_index = -1;
public:
	FControlOtherCharacterMoveDelegate ControlOtherCharacterMove;
	FControlOtherCharacterRotateDelegate ControlOtherCharacerRotate;

	CharacterSlot * CharacterSlotInfo;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ToCharacterCreate();
	void ToCharacterSelect();
	void ToCharacterZoomInCamera();

	void SelectCharacter(int NewJobCode);

	int32 GetJobCode();
	int32 GetSelectIndex();

	void SetSelectIndex(int32 _SelectIndex);
	void SetClientState(EClientState _NewClientState);

	void C2S_MoveConfirm(FVector& Location);
	void C2S_RotationcConfirm(FRotator& Rotation);
};
