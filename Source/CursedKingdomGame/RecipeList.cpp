// Fill out your copyright notice in the Description page of Project Settings.


#include "RecipeList.h"

// Sets default values for this component's properties
URecipeList::URecipeList()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ListOfRecipes.Add(Recipe1);
	ListOfRecipes.Add(Recipe2);

	
}


// Called when the game starts
void URecipeList::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URecipeList::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

