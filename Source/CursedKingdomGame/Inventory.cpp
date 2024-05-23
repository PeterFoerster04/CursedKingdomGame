// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "CursedKingdomGameCharacter.h"
#include "Item.h"
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

void UInventory::AddItem(AItem* a_ItemToAdd)
{

	if(ItemBundle.Num()<InventorySize)
	{
		UE_LOG(LogTemp, Log, TEXT("Added Item To Inventory: %s"), *a_ItemToAdd->GetName());
		DeactivateItem(a_ItemToAdd);
		ItemBundle.Add(a_ItemToAdd);
	}
	
}

void UInventory::RemoveItem(AItem* a_ItemToAdd)
{
}

void UInventory::DeactivateItem(AItem* a_ItemToAdd)
{

	if (Player == nullptr) return;
	UE_LOG(LogTemp, Log, TEXT("Item Deactivated"));
	a_ItemToAdd->SetActorEnableCollision(false);
	
}

void UInventory::ActivateItem(AItem* a_Item)
{
}

void UInventory::MoveItemToHand(int a_InOrDecrement)
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

