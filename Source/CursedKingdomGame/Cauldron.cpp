// Fill out your copyright notice in the Description page of Project Settings.


#include "Cauldron.h"

#include <d3d12sdklayers.h>

#include "CursedKingdomGameCharacter.h"
#include "Item.h"
#include "RecipeItem.h"
#include "RecipeList.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Recipe.h"


// Sets default values
ACauldron::ACauldron()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemTrigger = CreateDefaultSubobject<USphereComponent>("ItemTrigger");
	RootComponent = ItemTrigger;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	RecipeContainer = CreateDefaultSubobject<URecipeList>("RecipeContainer");

	
}

// Called when the game starts or when spawned
void ACauldron::BeginPlay()
{
	Super::BeginPlay();
	ItemTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACauldron::OnSphereTriggerOverlap);
	CurrentPossibleRecipes = RecipeContainer->ListOfRecipes;
	UE_LOG(LogTemp, Display, TEXT("All recipe Num: %i"), RecipeContainer->ListOfRecipes.Num())
}

// Called every frame
void ACauldron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACauldron::OnSphereTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Overlap"))
	ARecipeItem* PossibleItem = Cast<ARecipeItem>(OtherActor);

	if (OtherActor != nullptr && OtherActor->IsA(ACursedKingdomGameCharacter::StaticClass()))
	{
		UE_LOG(LogTemp,Display,TEXT("Player Overlap"))
	}
	else if (PossibleItem !=nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Item Overlap"))
		PossibleItem->SetActorEnableCollision(false);
		PossibleItem->SetActorHiddenInGame(true);
		
		CheckItemForRecipe(PossibleItem);
		//OtherActor->Destroy();
		//Explode();
	}

}

void ACauldron::CheckItemForRecipe(ARecipeItem* Item)
{
	
	UE_LOG(LogTemp, Display, TEXT("Item thrown in: %s"), *(UEnum::GetValueAsString(Item->Name)))

	UE_LOG(LogTemp, Display, TEXT("Number of available recipes: %i"), CurrentPossibleRecipes.Num())
	//iterating through all possible recipes to check if recipe contains item at given index
	//index is determined by the current amount of items in cauldron
	//storing all to be removed recipes indices to delete later
	//example:
	//5 recipes currently available
	//2 are removed because they do not contain item 1 at slot 0 (0 Items in Cauldron Array)
	//next iteration
	//1 more recipe is removed because it does not contain item 2 at slot 1 (1 Item in Cauldron Array)
	//...

	TArray<int> RecipeIndices;

	for (int i = 0; i < CurrentPossibleRecipes.Num(); i++)
	{
		if(CurrentPossibleRecipes[i]->Ingredients[CurrentItemsInCauldron.Num()] !=Item->Name)
		{
			//adding index to deletion array if recipe does not fit
			UE_LOG(LogTemp, Display, TEXT("Removed Recipe: %s, because it does not contain item: %s at slot %i"),
				*CurrentPossibleRecipes[i]->GetName(),*Item->GetName(),i);
			RecipeIndices.Add(i);
		}
		else
		{
			//putting item in cauldron if it is contained at given index
			//obviously also increments index, since array size is used
			CurrentItemsInCauldron.Add(Item);
		}
		
	}
	//deletion starts from behind so no entry is skipped
	for (int i = RecipeIndices.Num()-1; i >= 0; i--)
	{
		CurrentPossibleRecipes.RemoveAt(RecipeIndices[i]);
	}


	UE_LOG(LogTemp, Display, TEXT("Number of available recipes: %i"), CurrentPossibleRecipes.Num())
	if(CurrentPossibleRecipes.Num() == 0)
	{
		Explode();
		DumpContents();
		
	}
	else if(CurrentPossibleRecipes.Num() == 1&& CurrentPossibleRecipes[0]->Ingredients.Num() == CurrentItemsInCauldron.Num())
	{
		UE_LOG(LogTemp, Display, TEXT("Success, brewed Potion"))
		DumpContents();
	}


	
}

void ACauldron::Explode()
{
	if (ExplosionSystem == nullptr) return;
	UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionSystem, Mesh, NAME_None, ExplosionSpawnOffset, FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
}

void ACauldron::DumpContents()
{
	
	CurrentItemsInCauldron.Empty();
	//reset all possibilities to default
	CurrentPossibleRecipes = RecipeContainer->ListOfRecipes;
}


