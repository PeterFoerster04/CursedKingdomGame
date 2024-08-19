// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "KingdomSaveGame.h"
#include "KingdomSaveGameSettings.h"
#include "Engine/GameInstance.h"
#include "KingdomGameInstance.generated.h"



/**
 * 
 */
UCLASS()
class CURSEDKINGDOMGAME_API UKingdomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//splitting game save and settings save, deleting save should not reset settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Saves, meta = (AllowPrivateAccess))
	UKingdomSaveGame* SaveGameObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Saves, meta = (AllowPrivateAccess))
	UKingdomSaveGameSettings* SettingsSaveGameObject;

	//this list stores all Blueprint classes that can be picked up so that they can be spawned in again and added to the
	//player inventory on load
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Saves, meta = (AllowPrivateAccess))
	TArray<TSubclassOf<AItem>> ListOfSavableItemBlueprints;

	//custom spawn positions for the player to respawn for example if player dies in cave, spawn in front of cave (main map)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Static, meta = (AllowPrivateAccess))
	FVector HomePosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Static, meta = (AllowPrivateAccess))
	FVector MineRespawnPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Static, meta = (AllowPrivateAccess))
	FVector ForgeRespawnPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Static, meta = (AllowPrivateAccess))
	bool CameFromCave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Static, meta = (AllowPrivateAccess))
	bool CameFromForge;
	

	//can be called in blueprint, in case that widgets want to save something, settings etc.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadSaves();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SaveSaves();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadSettingsSave();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SaveSettingsSave();
};
