// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

#include "IDetailTreeNode.h"
#include "Item.h"
#include "Villager.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnerRootPos = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SpawnerRootPos);


	PossibleSpawnPos1 = CreateDefaultSubobject<USceneComponent>("Pos1");
	PossibleSpawnPos1->SetupAttachment(RootComponent);
	ListOfSpawnPositions.Add(PossibleSpawnPos1);

	PossibleSpawnPos2 = CreateDefaultSubobject<USceneComponent>("Pos2");
	PossibleSpawnPos2->SetupAttachment(RootComponent);
	ListOfSpawnPositions.Add(PossibleSpawnPos2);

	PossibleSpawnPos3 = CreateDefaultSubobject<USceneComponent>("Pos3");
	PossibleSpawnPos3->SetupAttachment(RootComponent);
	ListOfSpawnPositions.Add(PossibleSpawnPos3);

	RespawnTrigger = CreateDefaultSubobject<USphereComponent>("RespawnTrigger");
	RespawnTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnItem(bool ShouldAttach)
{
	if (ItemToSpawn == nullptr) return;
	if (ShouldAttach && VillagerToAttachTo == nullptr) return;

	FlushAllItems();

	if(ShouldAttach)
	{
		LastItem = GetWorld()->SpawnActor<AItem>(ItemToSpawn);
		if (LastItem == nullptr) return;
		LastItem->AttachToComponent(VillagerToAttachTo->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		LastItem->SetActorRelativeLocation(RelativeActorAttachSpawnPos);
		LastItem->SetActorRelativeRotation(RelativeActorAttachRotation);
		ListOfSpawnedItems.Add(LastItem);
	}
	else
	{
		//attaching disabled -> spawn at pos 1
		LastItem = GetWorld()->SpawnActor<AItem>(ItemToSpawn, PossibleSpawnPos1->GetComponentLocation(), FRotator::ZeroRotator);
		ListOfSpawnedItems.Add(LastItem);
	}
}

void AItemSpawner::SpawnItems()
{
	if (ItemToSpawn == nullptr) return;

	FlushAllItems();

	for (int i = 0; i < ListOfSpawnPositions.Num(); ++i)
	{
		if (ListOfSpawnPositions[i] == nullptr) continue;

		AItem* Item = GetWorld()->SpawnActor<AItem>(ItemToSpawn, ListOfSpawnPositions[i]->GetComponentLocation(), FRotator::ZeroRotator);
		ListOfSpawnedItems.Add(Item);
		
	}
}
//Deletes all items from list accept for picked up ones
void AItemSpawner::FlushAllItems()
{
	TArray<int> Indices;
	if (ListOfSpawnedItems.IsEmpty()) return;

	for (int i = 0; i < ListOfSpawnedItems.Num(); ++i)
	{
		if(ListOfSpawnedItems[i] != nullptr && !ListOfSpawnedItems[i]->wasPickedUp)
		{
			//do not destroy items that were picked up
			Indices.Add(i);
		}
		else if(ListOfSpawnedItems[i] != nullptr && ListOfSpawnedItems[i]->wasPickedUp){

			ListOfSpawnedItems[i] = nullptr;
		}
	}
	//deleting all items at cached index
	for (int Index : Indices)
	{
		ListOfSpawnedItems[Index]->Destroy();
	}
	
}

void AItemSpawner::DeleteLastSpawnedItem()
{
	if (LastItem == nullptr) return;

	LastItem->Destroy(); 

}

