// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "CursedKingdomGameCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UInventory::InitInventory()
{
}

void UInventory::AddItem(AActor* a_ItemToAdd)
{
	if(ItemBundle.Count()<static_cast<uint32>(InventorySize))
	{
		UE_LOG(LogTemp, Log, TEXT("Added Item To Inventory: %s"), *a_ItemToAdd->GetName());
		DeactivateItem(a_ItemToAdd);
		ItemBundle.Enqueue(a_ItemToAdd);
	}
	
}

void UInventory::RemoveItem(AActor* a_ItemToAdd)
{
}

void UInventory::DeactivateItem(AActor* a_ItemToAdd)
{
	if (Player == nullptr) return;
	UE_LOG(LogTemp, Log, TEXT("Item Deactivated"));

	a_ItemToAdd->SetActorLocation(Player->ItemStoreSpot->GetComponentLocation());
	a_ItemToAdd->SetActorEnableCollision(false);
	a_ItemToAdd->SetActorHiddenInGame(true);
}

void UInventory::ActivateItem(AActor* a_Item)
{
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

