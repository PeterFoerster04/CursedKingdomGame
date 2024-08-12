// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	TSubclassOf<AItem> ItemToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	AActor* ActorToAttachTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	FVector RelativeActorAttachSpawnPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	bool bShouldAttachToActor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	bool bUseMultiSpawn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	USceneComponent* PossibleSpawnPos1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	USceneComponent* PossibleSpawnPos2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess))
	USceneComponent* PossibleSpawnPos3;

	UFUNCTION(BlueprintCallable)
	void SpawnItems();
};
