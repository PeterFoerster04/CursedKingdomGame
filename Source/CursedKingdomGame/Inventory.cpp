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

	InitInventory();
}

void UInventory::InitInventory()
{
	for (int i = 0; i < InventorySize; ++i)
	{
		ItemBundle.Add(nullptr);
	}
}

void UInventory::AddItem(AItem* a_ItemToAdd)
{
	for (int i = 1; i < InventorySize; ++i)
	{
		if(ItemBundle[i] == nullptr)
		{
			ItemBundle[i] = a_ItemToAdd;
			UE_LOG(LogTemp, Log, TEXT("Added Item To Inventory: %s"), *a_ItemToAdd->GetName());
			DeactivateItem(a_ItemToAdd);
			return;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Inventory Full"));
}

void UInventory::RemoveItem(AItem* a_ItemToAdd)
{
}

void UInventory::DeactivateItem(AItem* a_ItemToAdd)
{

	UE_LOG(LogTemp, Log, TEXT("Item Deactivated"));
	a_ItemToAdd->SetActorEnableCollision(false);
	a_ItemToAdd->SetActorHiddenInGame(true);
	
}

void UInventory::ActivateItem(bool a_bUseForce, FVector a_ThrowDirection, float a_Force)
{
	ItemBundle[CurrentItemOutIndex]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	ItemBundle[CurrentItemOutIndex]->SetActorEnableCollision(true);
	ItemBundle[CurrentItemOutIndex]->SetActorHiddenInGame(false);
	ItemBundle[CurrentItemOutIndex]->Mesh->SetSimulatePhysics(true);
	if (a_bUseForce) ItemBundle[CurrentItemOutIndex]->Mesh->AddImpulse(a_ThrowDirection * a_Force);
	UE_LOG(LogTemp, Log, TEXT("Throw Direction %f,%f,%f"),a_ThrowDirection.X, a_ThrowDirection.Y, a_ThrowDirection.Z);
	UE_LOG(LogTemp, Log, TEXT("Force %f"), a_Force);
	ItemBundle[CurrentItemOutIndex] = nullptr;

}

void UInventory::MoveItem(bool a_ToBack)
{
	ItemBundle[CurrentItemOutIndex]->SetActorHiddenInGame(a_ToBack);
}



//returns true if inventory is full and false if a slot is unoccupied
bool UInventory::CheckInventoryFull()
{
	for (int i = 1; i < InventorySize; ++i)
	{
		if (ItemBundle[i] == nullptr) return false;
	}
	return true;
}

//function takes parameter instead of just checking the current index to include more use cases
//for example checking slots that do not represent the current index
bool UInventory::DoesInvHaveItemAtIndex(int a_Index)
{
	if (ItemBundle[a_Index] != nullptr) return true;
	return false;
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

