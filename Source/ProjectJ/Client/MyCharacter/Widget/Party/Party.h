// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Client/MyCharacter/Widget/Party/Structure/FPartySlot.h"
#include "Party.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTJ_API UParty : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UParty();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		class UPartyWidget* PartyWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		class UPartyAcceptRejectWidget* PartyAcceptRejectWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		TArray<FPartySlot> PartySlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PartyWidget, Meta = (AllowPrivateAccess = true))
		int32 PartyMaxCount;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PartyWidgetVisible();
	void PartyWidgetHidden();

	void PartyAcceptRejectWidgetVisible();
	void PartyAcceptRejectWidgetHidden();

	UPartyWidget* GetPartyWidget();
	UPartyAcceptRejectWidget* GetPartyAcceptRejectWidget();

	void PartyJoin(char* _CharacterCode, int32 _JobCode, char* _NickName, float _HP, float _MP, bool _Leader);
	bool IsPartyJoin();
	int32 GetPartySize();
};
