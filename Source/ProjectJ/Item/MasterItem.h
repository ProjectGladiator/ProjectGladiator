// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/DataTable/ItemDataTable.h"
#include "MasterItem.generated.h"

UCLASS()
class PROJECTJ_API AMasterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Mesh; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* Sphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UDataTableComponent* DTComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FItemDataTable ItemInfo;

	
};
