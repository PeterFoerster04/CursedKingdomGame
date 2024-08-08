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
	void RemoveItemInHand();

	void DeactivateItem(AItem* a_ItemToAdd);
	void ActivateItem(bool a_bUseForce = false, FVector a_ThrowDirection = FVector::ZeroVector, float a_Force = 0.0f);

	void MoveItem(bool a_ToBack = true);
	bool CheckInventoryFull();
	bool DoesInvHaveItemAtIndex(int a_Index);

	UPROPERTY()
	ACursedKingdomGameCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	int CurrentItemOutIndex = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
