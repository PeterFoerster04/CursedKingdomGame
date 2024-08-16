// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnumLibrary.h"
#include "Recipe.generated.h"

class ARecipeItem;
/**
 * 
 */
UCLASS()
class CURSEDKINGDOMGAME_API URecipe : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Contents, meta = (AllowPrivateAccess))
	TArray<EItemName> Ingredients;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Contents, meta = (AllowPrivateAccess))
	TSubclassOf<AKeyItem> ResultingPotion;
	
};
