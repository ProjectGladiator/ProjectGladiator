// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMapOtherPlayerController.generated.h"

//DECLARE_DYNAMIC_DELEGATE_OneParam(FControlOtherCharacterMoveDelegate, FVector&, Location);
//DECLARE_DYNAMIC_DELEGATE_OneParam(FControlOtherCharacterRotateDelegate, FRotator&, Rotation);

/**
 * 
 */
UCLASS()
class PROJECTJ_API AMainMapOtherPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainMapOtherPlayerController();
	//FControlOtherCharacterMoveDelegate ControlOtherCharacterMove;
	//FControlOtherCharacterRotateDelegate ControlOtherCharacerRotate;
	virtual void Tick(float DeltaTime) override;
};
