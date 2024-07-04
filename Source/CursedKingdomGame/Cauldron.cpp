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
		//iterate through all available recipes

	int Iterations = DetermineLongestRecipeLength();
	UE_LOG(LogTemp, Display, TEXT("Longest Recipe Length: %i"), Iterations);


	for (int i = 0; i < Iterations; ++i)
	{

		for (URecipe* Recipe : RecipeContainer->ListOfRecipes)
		{
			if (Recipe->Ingredients.Num() - 1 < Iterations) break;
			if(Recipe->Ingredients[i] ==Item->Name)
			{
				
			}
		}

	}


	for (URecipe* Recipe : RecipeContainer->ListOfRecipes)
	{
		//iterate through all ingredients of a recipe
		for (int i = 0; i<Recipe->Ingredients.Num();i++)
		{
			//item is contained in recipe but order is false
			if(Item->Name == Recipe->Ingredients[i] && i != CurrentItemsInCauldron.Num())
			{

				UE_LOG(LogTemp, Display, TEXT("Process Canceled, Recipe: %s"), *Recipe->GetName());
				UE_LOG(LogTemp, Display, TEXT("Wrong Order -> Item should be: %s"), *(UEnum::GetValueAsString(Recipe->Ingredients[i])))
				break;
				
			}

		}
	}
	//Explode();
	//DumpContents();
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

int ACauldron::DetermineLongestRecipeLength()
{
	int LongestLength = 0;
	for (URecipe* Recipe : CurrentPossibleRecipes)
	{
		if(Recipe->Ingredients.Num()>LongestLength)
		{
			LongestLength = Recipe->Ingredients.Num();
		}
	}
	return LongestLength;
}

