// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "Cauldron.generated.h"

class UKingdomGameInstance;
class AKeyItem;
class UNiagaraComponent;
class URecipe;
class ARecipeItem;
class URecipeList;
class USphereComponent;
class UNiagaraSystem;

UCLASS()
class CURSEDKINGDOMGAME_API ACauldron : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACauldron();

	//components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		USphereComponent* ItemTrigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		UStaticMeshComponent* PotionSoupMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mat, meta = (AllowPrivateAccess))
	UMaterialInterface* UpgradeMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	URecipeList* RecipeContainer;
	//to calculate possibilities while inserting ingredients 
	UPROPERTY()
	TArray<URecipe*> CurrentPossibleRecipes;

	//spawn this every time cauldron explodes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	UNiagaraSystem* ExplosionSystem;
	//spawn this on item insert
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	UNiagaraSystem* ItemInsertSystem;
	//system spawns constantly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	UNiagaraComponent* IdleBrewer;
	//system is activated when correct recipe is inserted
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	UNiagaraComponent* ProcessBrewer;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects, meta = (AllowPrivateAccess))
		FVector ExplosionSpawnOffset;
	//the actual item container of cauldron
	UPROPERTY()
	TArray<ARecipeItem*> CurrentItemsInCauldron;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Brewing, meta = (AllowPrivateAccess))
	float PotionBrewingTime = 8.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Brewing, meta = (AllowPrivateAccess))
	bool CurrentlyBrewing = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Brewing, meta = (AllowPrivateAccess))
	bool PotionReady;


	FTimerHandle TimerHandle;

	bool IsUpgraded = false;
	//container for finished potions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Brewing, meta = (AllowPrivateAccess))
	TSubclassOf<AKeyItem> CurrentPotionInCauldron;


	UPROPERTY()
	UKingdomGameInstance* Instance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnSphereTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);

	void CheckItemForRecipe(ARecipeItem* Item);
	void Explode();
	void DumpContents();
	void MakePotion();
	void SetPotionReady();
	void UpgradeCauldron();
	void DeactivateItem(AItem* Item);
	void SpawnInsertSystem();
	void DetermineCurrentPotion();

	//is called when player interacts with cauldron while holding empty bottle
	UFUNCTION(BlueprintCallable)
	void SwapGlasForPotion(int CurrentOutIndex, ACursedKingdomGameCharacter* Player);


	//events for audio implementation
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemInsert();
	UFUNCTION(BlueprintImplementableEvent)
	void OnExplode();
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartBrewing();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFinishedBrewing();
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemInsertWhileBrewing();
	UFUNCTION(BlueprintImplementableEvent)
	void OnWrongItemInsert();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpgradeCauldron();
	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeOutPotion();
};
