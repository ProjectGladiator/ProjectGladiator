// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UserStartDoor.generated.h"

UCLASS()
class PROJECTJ_API AUserStartDoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUserStartDoor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* DoorWall;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Door;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DoorOpen();
	void DoorClose();
};
