// Fill out your copyright notice in the Description page of Project Settings.


#include "Potion.h"

#include "KingdomGameInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "Villager.h"
#include "Kismet/GameplayStatics.h"

void APotion::BeginPlay()
{
	Super::BeginPlay();

	Instance = Cast<UKingdomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(Instance == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Potion: Game Instance Null"));
	}
}

//returns true if Healing was successful 
bool APotion::HealVillager(AVillager* VillagerToHeal,EItemName NameOfPotion)
{
	
	if(bUsed) return false;
	
	if (VillagerToHeal->WasHealed) return false;


	VillagerToHeal->WasHealed = true;
	bUsed = true;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HealExplosionSystem, Mesh->GetComponentLocation());

	VillagerToHeal->SwapToHealMesh();
	OnPotionExplode();
	if(Instance == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Potion: Could not save Villager heal"));
		return false;
	}

	if(NameOfPotion == EItemName::Schmiedintrank)
	{
		Instance->SaveGameObject->HealedSmith = true;
		VillagerToHeal->GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	else if(NameOfPotion == EItemName::Vogelscheuchentrank)
	{
		Instance->SaveGameObject->HealedScarecrow = true;
	}

	Instance->SaveSaves();
	return true;
}
