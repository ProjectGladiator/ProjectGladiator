// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMapPlayerController.generated.h"

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
	class ClientState* ClientCharacterState;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	virtual void Tick(float DeltaTime) override;
public:
	CharacterSlot * CharacterSlotInfo;

	void ToCharacterCreate();
	void ToCharacterSelect();
	void ToCharacterZoomInCamera();

	void SelectCharacter(int NewJobCode);

	int32 GetJobCode();
	int32 GetSelectIndex();

	void SetSelectIndex(int32 _SelectIndex);

	void C2S_MoveConfirm(FVector& Location);
	void C2S_RotationcConfirm(FRotator& Rotation);
	void C2S_ReqMenuChannelInfo();
	void C2S_ReqMenuCharacterSelect();
	void C2S_ReqMenuLogOut();

	UFUNCTION()
		virtual void Possess(APawn* InPawn) override;

	void SetClientPCState(ClientState * _NewClientCharacterState);
};
