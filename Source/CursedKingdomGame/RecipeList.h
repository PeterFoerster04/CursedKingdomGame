// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnumLibrary.h"
#include "RecipeList.generated.h"


class URecipe;
//container class for cauldron 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURSEDKINGDOMGAME_API URecipeList : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecipeList();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,Category=Recipe,meta=(AllowPrivateAccess))
	TArray<URecipe*> ListOfRecipes;

};
