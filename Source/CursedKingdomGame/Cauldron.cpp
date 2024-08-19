// Fill out your copyright notice in the Description page of Project Settings.


#include "Cauldron.h"

#include <d3d12sdklayers.h>

#include "CursedKingdomGameCharacter.h"
#include "Inventory.h"
#include "Item.h"
#include "RecipeItem.h"
#include "RecipeList.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Recipe.h"
#include "KeyItem.h"
#include "KingdomGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACauldron::ACauldron()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemTrigger = CreateDefaultSubobject<USphereComponent>("ItemTrigger");
	RootComponent = ItemTrigger;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	PotionSoupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PotionSoupMesh");
	PotionSoupMesh->SetupAttachment(RootComponent);

	RecipeContainer = CreateDefaultSubobject<URecipeList>("RecipeContainer");
	IdleBrewer = CreateDefaultSubobject<UNiagaraComponent>("Brewer");
	IdleBrewer->SetupAttachment(RootComponent);

	ProcessBrewer = CreateDefaultSubobject<UNiagaraComponent>("ProcessBrewer");
	ProcessBrewer->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ACauldron::BeginPlay()
{
	Super::BeginPlay();
	ItemTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACauldron::OnSphereTriggerOverlap);
	CurrentPossibleRecipes = RecipeContainer->ListOfRecipes;
	UE_LOG(LogTemp, Display, TEXT("All recipe Num: %i"), RecipeContainer->ListOfRecipes.Num())
	IdleBrewer->ActivateSystem();

	//trying to load saved variables 
	Instance = Cast<UKingdomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(Instance != nullptr)
	{
		if(Instance->SaveGameObject->UpgradedCauldron)
		{
			UpgradeCauldron();
		}
	}
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
	//used to check if inserted actor is recipe item
	ARecipeItem* PossibleItem = Cast<ARecipeItem>(OtherActor);
	//used to check if actor is item but not recipe item
	AItem* MaybeItem = Cast<AItem>(OtherActor);

	//four scenarios:
	//1.Player overlaps: Do nothing
	//2.Actor overlaps and is recipe item: Checking recipes
	//3.Actor overlaps, is recipe item but cauldron is already brewing: just de-spawn item
	//4.Actor is item but not recipe item: explode

	if (OtherActor != nullptr && OtherActor->IsA(ACursedKingdomGameCharacter::StaticClass()))
	{
		UE_LOG(LogTemp,Display,TEXT("Player Overlap"))
	}
	else if (PossibleItem !=nullptr&&!CurrentlyBrewing)
	{
		PotionReady = false;
		UE_LOG(LogTemp, Display, TEXT("Item Overlap"))
		OnItemInsert();
		SpawnInsertSystem();
		DeactivateItem(PossibleItem);
		CheckItemForRecipe(PossibleItem);
	}
	else if(PossibleItem != nullptr && CurrentlyBrewing)
	{
		
		UE_LOG(LogTemp, Display, TEXT("Still Brewing"))
		SpawnInsertSystem();
		DeactivateItem(PossibleItem);
		OnItemInsertWhileBrewing();
	}
	else if(MaybeItem!= nullptr)
	{
		PotionReady = false;
		UE_LOG(LogTemp, Display, TEXT("Wrong Item KekW"))
		DeactivateItem(MaybeItem);
		
		OnWrongItemInsert();
		Explode();
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
	int currentSlotToCheck = CurrentItemsInCauldron.Num();
	bool itemIsContainedAtSlot = false;
	TArray<int> RecipeIndices;

	for (int i = 0; i < CurrentPossibleRecipes.Num(); i++)
	{
		if(CurrentPossibleRecipes[i]->Ingredients[currentSlotToCheck] !=Item->Name)
		{
			//adding index to deletion array if recipe does not fit
			UE_LOG(LogTemp, Display, TEXT("Removed Recipe: %s, because it does not contain item: %s at slot %i"),
				*CurrentPossibleRecipes[i]->GetName(),*Item->GetName(), currentSlotToCheck);
			RecipeIndices.Add(i);
		}
		else
		{
			itemIsContainedAtSlot = true;
		}
		
	}
	if(itemIsContainedAtSlot)
	{
		//putting item in cauldron if it is contained at given index
			//obviously also increments index, since array size is used
		CurrentItemsInCauldron.Add(Item);
	}
	//deletion starts from behind so no entry is skipped
	for (int i = RecipeIndices.Num()-1; i >= 0; i--)
	{
		CurrentPossibleRecipes.RemoveAt(RecipeIndices[i]);
	}

	//all possibilities gone -> explode
	//only one recipe left& all ingredients inserted -> start brewing
	UE_LOG(LogTemp, Display, TEXT("Number of available recipes: %i"), CurrentPossibleRecipes.Num())
	if(CurrentPossibleRecipes.Num() == 0)
	{
		Explode();
		DumpContents();
	}
	else if(CurrentPossibleRecipes.Num() == 1&& CurrentPossibleRecipes[0]->Ingredients.Num() == CurrentItemsInCauldron.Num())
	{
		UE_LOG(LogTemp, Display, TEXT("Brewing Potion"))
		CurrentlyBrewing = true;
		CurrentPotionInCauldron = CurrentPossibleRecipes[0]->ResultingPotion;
		OnStartBrewing();
		MakePotion();
		DumpContents();
	}
}

void ACauldron::Explode()
{
	OnExplode();
	if (ExplosionSystem == nullptr) return;
	UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionSystem, Mesh, NAME_None, ExplosionSpawnOffset, FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
}

void ACauldron::DumpContents()
{
	CurrentItemsInCauldron.Empty();
	//reset all possibilities to default
	CurrentPossibleRecipes = RecipeContainer->ListOfRecipes;
}

void ACauldron::MakePotion()
{
	ProcessBrewer->ActivateSystem();
	GetWorldTimerManager().SetTimer(TimerHandle,this,&ACauldron::SetPotionReady,PotionBrewingTime);
}

void ACauldron::SetPotionReady()
{
	ProcessBrewer->Deactivate();
	CurrentlyBrewing = false;
	PotionReady = true;
	UE_LOG(LogTemp, Display, TEXT("Success, brewed Potion"))
	OnFinishedBrewing();
}

void ACauldron::UpgradeCauldron()
{
	if(UpgradeMat != nullptr)Mesh->SetMaterial(0, UpgradeMat);
	//halfing brew time if upgraded
	PotionBrewingTime /= 2.0f;
	IsUpgraded = true;
	OnUpgradeCauldron();
}

void ACauldron::DeactivateItem(AItem* Item)
{
	PotionReady = false;
	Item->Mesh->SetVisibility(false);
	Item->SetActorEnableCollision(false);
	Item->SetActorHiddenInGame(true);
}

void ACauldron::SpawnInsertSystem()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ItemInsertSystem, Mesh->GetComponentLocation()+FVector(0,0,65.0f));
}

//not used anymore
void ACauldron::DetermineCurrentPotion()
{
}

//function is used to swap empty bottle in players hand with finished potion
//is called when player is in range of cauldron and interacts with empty bottle in hand
void ACauldron::SwapGlasForPotion(int CurrentOutIndex, ACursedKingdomGameCharacter* Player)
{
	
	if(Player == nullptr||Player->PlayerInventory->ItemBundle[CurrentOutIndex]==nullptr)
	{
		return;
	}
	AItem* ThrowAwayItem = Player->PlayerInventory->ItemBundle[CurrentOutIndex];

	Player->PlayerInventory->ActivateItemHidden();
	Player->ItemsInInventory--;
	Player->bPlayerInventoryFull = false;
	Player->NameOfCurrentItemInHand = EItemName::DEFAULT;

	if(CurrentPotionInCauldron == nullptr) return;

	OnTakeOutPotion();
	
	FActorSpawnParameters Parameters;
	AKeyItem* ItemActor = GetWorld()->SpawnActor<AKeyItem>(CurrentPotionInCauldron,Player->GetMesh()->GetComponentLocation(),FRotator(), Parameters);


	if(ItemActor != nullptr)
	{
		Player->PickUpItem(ItemActor);
	}
	
	

}


