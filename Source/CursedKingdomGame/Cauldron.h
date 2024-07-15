// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cauldron.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		USphereComponent* ItemTrigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	URecipeList* RecipeContainer;
	UPROPERTY()
	TArray<URecipe*> CurrentPossibleRecipes;

	//spawn this every time cauldron explodes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Comps, meta = (AllowPrivateAccess))
	UNiagaraSystem* ExplosionSystem;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects, meta = (AllowPrivateAccess))
		FVector ExplosionSpawnOffset;
	UPROPERTY()
	TArray<ARecipeItem*> CurrentItemsInCauldron;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Brewing, meta = (AllowPrivateAccess))
	float PotionBrewingTime = 8.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Brewing, meta = (AllowPrivateAccess))
	bool CurrentlyBrewing = false;

	FTimerHandle TimerHandle;



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
};
