// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "CursedKingdomGameCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void AItem::HighlightObject(bool Highlight)
{
	if(OutlineMat != nullptr && Highlight)
	{
		Mesh->SetOverlayMaterial(OutlineMat);
	}
	else if(OutlineMat != nullptr && !Highlight)
	{
		Mesh->SetOverlayMaterial(nullptr);
	}

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACursedKingdomGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isFocused&&!alreadyHighlighted)
	{
		alreadyHighlighted = true;
		HighlightObject(true);
	}
	if(alreadyHighlighted &&Player!= nullptr&& !Player->bIsFocusingItem)
	{
		alreadyHighlighted = false;
		isFocused = false;
		HighlightObject(false);
	}

}

