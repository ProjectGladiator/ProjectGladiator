// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClickCharacterInteraction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJ_API UClickCharacterInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClickCharacterInteraction();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WidgetActorComponent, Meta = (AllowPrivateAccess = true))
		class UMyCharacterWidget* MyCharacterWidget;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MyCharacterWidgetVisible();
	void MyCharacterWidgetHidden();
	
	UMyCharacterWidget* GetMyCharacterWidget();

	void MyCharacterSetInfo(class AMyCharacter * _ClickCharacter, APlayerController* _PlayerController);


};
