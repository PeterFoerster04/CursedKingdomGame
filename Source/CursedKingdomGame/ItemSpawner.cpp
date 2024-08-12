// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PossibleSpawnPos1 = CreateDefaultSubobject<USceneComponent>("Pos1");
	PossibleSpawnPos1->SetupAttachment(RootComponent);
	PossibleSpawnPos2 = CreateDefaultSubobject<USceneComponent>("Pos2");
	PossibleSpawnPos2->SetupAttachment(RootComponent);
	PossibleSpawnPos3 = CreateDefaultSubobject<USceneComponent>("Pos3");
	PossibleSpawnPos3->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnItems();
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnItems()
{
}

