// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "KingdomSaveGameSettings.generated.h"

/**
 * 
 */
//container for settings values
UCLASS()
class CURSEDKINGDOMGAME_API UKingdomSaveGameSettings : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseSens = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Volume = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DeactivateTips;

	
};
