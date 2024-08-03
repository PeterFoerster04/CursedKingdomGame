// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KingdomSaveGame.h"
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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadSaves();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SaveSaves();
};
