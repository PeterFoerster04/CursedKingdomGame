// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class AVillager;
class USphereComponent;
class AItem;

UCLASS()
class CURSEDKINGDOMGAME_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	USceneComponent* SpawnerRootPos;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	TSubclassOf<AItem> ItemToSpawn;

	//ability to attach spawned item to a villager (for example scarecrow)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	AVillager* VillagerToAttachTo;

	//spawn parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	FVector RelativeActorAttachSpawnPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	FRotator RelativeActorAttachRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	bool bShouldAttachToActor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	bool bUseMultiSpawn = false;

	//maximum three customizable spawn positions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	USceneComponent* PossibleSpawnPos1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	USceneComponent* PossibleSpawnPos2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	USceneComponent* PossibleSpawnPos3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	USphereComponent* RespawnTrigger;

	//container for current spawned items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	TArray<AItem*> ListOfSpawnedItems;

	//collection of all spawn positions for iterations
	//used to destroy last items spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	TArray<USceneComponent*> ListOfSpawnPositions;

	//used to destroy last item if single spawn is activated
	UPROPERTY()
	AItem* LastItem;

	//blueprint functions because to lazy to paste in overlap events again, again and again...
	//please unreal provide a better way to use overlap functions in c++, much more comfortable in blueprints
	UFUNCTION(BlueprintCallable)
	void SpawnItem(bool ShouldAttach);
	UFUNCTION(BlueprintCallable)
	void SpawnItems();

	void FlushAllItems();

	UFUNCTION(BlueprintCallable)
	void DeleteLastSpawnedItem();
};
