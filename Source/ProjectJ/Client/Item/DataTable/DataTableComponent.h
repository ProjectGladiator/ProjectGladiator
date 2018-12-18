// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Client/Item/DataTable/ItemDataTable.h"
#include "DataTableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJ_API UDataTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDataTableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UDataTable* DataTable;

	UFUNCTION(BlueprintCallable, Category = "Data")
		FItemDataTable& GetItemData(int ItemIndex);

	
		
};
