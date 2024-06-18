// Fill out your copyright notice in the Description page of Project Settings.


#include "Couldron.h"

// Sets default values
ACouldron::ACouldron()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACouldron::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACouldron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

