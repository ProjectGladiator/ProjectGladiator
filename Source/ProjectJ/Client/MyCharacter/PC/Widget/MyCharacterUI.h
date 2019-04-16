// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyCharacterUI.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTJ_API UMyCharacterUI : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyCharacterUI();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WidgetActorComponent, Meta = (AllowPrivateAccess = true))
		class UClickCharacterInteraction* MyCharacterInteraction;
	UPROPERTY()
		class UMainWidget* MainWidget = nullptr;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMyCharacterUI();

	UClickCharacterInteraction* GetMyCharacterInteraction();
	
	void AllUIHidden();
	void AllUIVisible();
	void AllUIDestroy();

	UMainWidget* GetMainWidget();

	void MainWidgetVisible();
	void MainWidgetHidden();
};
