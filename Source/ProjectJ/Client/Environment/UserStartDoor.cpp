// Fill out your copyright notice in the Description page of Project Settings.

#include "UserStartDoor.h"
//클라 헤더
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

//서버 헤더

// Sets default values
AUserStartDoor::AUserStartDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorWall"));
	SetRootComponent(DoorWall);
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorWall);

	Door->SetRelativeLocation(FVector(0, 82.0f, -5.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_DoorWall(TEXT("StaticMesh'/Game/Assets/MedievalDungeon/Mesh/SM_Cell_Front.SM_Cell_Front'"));

	if (SM_DoorWall.Succeeded())
	{
		DoorWall->SetStaticMesh(SM_DoorWall.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Door(TEXT("StaticMesh'/Game/Assets/MedievalDungeon/Mesh/SM_Cell_Door.SM_Cell_Door'"));

	if (SM_Door.Succeeded())
	{
		Door->SetStaticMesh(SM_Door.Object);
	}


}

// Called when the game starts or when spawned
void AUserStartDoor::BeginPlay()
{
	Super::BeginPlay();

	Door->SetRelativeRotation(FRotator(0, 120.0f, 0));
}

// Called every frame
void AUserStartDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Door)
	//{
	//	FRotator Rotation = FMath::RInterpTo(Door->GetComponentRotation(), FRotator(0, -120.0f, 0), DeltaTime, 0.5f);
	//	
	//	Door->SetRelativeRotation(Rotation);
	//}
}

void AUserStartDoor::DoorOpen()
{

}

void AUserStartDoor::DoorClose()
{

}