// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumLibrary.h"
#include "GameFramework/SaveGame.h"
#include "KingdomSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CURSEDKINGDOMGAME_API UKingdomSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TutorialDone = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform SpawnPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform DeathRespawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HealedSmith = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HealedScarecrow = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EItemName> SavedPlayerInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LoggedOutInCave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LoggedOutInForge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool NotFirstSpawn;

};
