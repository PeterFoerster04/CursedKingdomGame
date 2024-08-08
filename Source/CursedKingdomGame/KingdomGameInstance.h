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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Saves, meta = (AllowPrivateAccess))
	UKingdomSaveGame* SaveGameObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Saves, meta = (AllowPrivateAccess))
	UKingdomSaveGameSettings* SettingsSaveGameObject;

	//this list stores all Blueprint classes that can be picked up so that they can be spawned in again and added to the
	//player inventory on load
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Saves, meta = (AllowPrivateAccess))
	TArray<TSubclassOf<AItem>> ListOfSavableItemBlueprints;

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
	


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadSaves();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SaveSaves();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadSettingsSave();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SaveSettingsSave();
};
