// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyCharacterUI.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJ_API UMyCharacterUI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyCharacterUI();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WidgetActorComponent, Meta = (AllowPrivateAccess = true))
		class UInventory* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WidgetActorComponent, Meta = (AllowPrivateAccess = true))
		class UParty* PartyComponent;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WidgetActorComponent, Meta = (AllowPrivateAccess = true))
		class UClickCharacterInteraction* ClickCharacterIntreaciton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyCharacterInfoWidget, Meta = (AllowPrivateAccess = true))
		class UMyCharacterWidget* MyCharacterWidget;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
			
	void SetMyCharacterUI();

	UInventory* GetInventoryComponent();

	UParty* GetPartyComponent();

	UClickCharacterInteraction* GetClickCharacterInteractionComponent();

	void MyCharacterWidgetVisible();
	void MyCharacterWidgetHidden();

	void AllUIWidgetHidden();
};
