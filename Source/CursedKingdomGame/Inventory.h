// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/CircularQueue.h"
#include "Inventory.generated.h"


class AItem;
class ACursedKingdomGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURSEDKINGDOMGAME_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	int InventorySize = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	TArray<AItem*> ItemBundle;
	

	void InitInventory();
	void AddItem(AItem* a_ItemToAdd);
	void RemoveItem(AItem* a_ItemToAdd);
	void DeactivateItem(AItem* a_ItemToAdd);
	void ActivateItem(AItem* a_Item);
	void MoveItemToHand(int a_InOrDecrement);

	UPROPERTY()
	ACursedKingdomGameCharacter* Player;

	int CurrentItemOutIndex = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
