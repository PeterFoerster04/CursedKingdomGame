// Fill out your copyright notice in the Description page of Project Settings.


#include "PointOfInterest.h"
#include "Components/WidgetComponent.h"


// Sets default values
APointOfInterest::APointOfInterest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APointOfInterest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APointOfInterest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

