// Fill out your copyright notice in the Description page of Project Settings.


#include "Cauldron.h"

#include "CursedKingdomGameCharacter.h"
#include "Item.h"
#include "RecipeList.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


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
	if (OtherActor != nullptr && OtherActor->IsA(ACursedKingdomGameCharacter::StaticClass()))
	{
		UE_LOG(LogTemp,Display,TEXT("Player Overlap"))
	}
	else if (OtherActor != nullptr && OtherActor->IsA(AItem::StaticClass()))
	{
		UE_LOG(LogTemp, Display, TEXT("Item Overlap"))
		Explode();
	}

}

void ACauldron::Explode()
{
	if (ExplosionSystem == nullptr) return;
	UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionSystem, Mesh, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
}

