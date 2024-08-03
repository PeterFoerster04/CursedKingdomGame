// Fill out your copyright notice in the Description page of Project Settings.


#include "POIMap.h"

#include "PointOfInterest.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


void APOIMap::TogglePOIVisibility(bool SetVisible)
{
	if (ListOfPoints.IsEmpty()) return;
	ESlateVisibility Visibility;
	if(SetVisible)
	{
		Visibility = ESlateVisibility::Visible;
	}else
	{
		Visibility = ESlateVisibility::Hidden;
	}
	for (APointOfInterest* Point : ListOfPoints)
	{
		Point->WidgetComp->GetWidget()->SetVisibility(Visibility);
	}
}

void APOIMap::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APointOfInterest::StaticClass(), ListOfPointActors);

	for (AActor* Actor : ListOfPointActors)
	{
		APointOfInterest* point = Cast<APointOfInterest>(Actor);
		if(point != nullptr)
		{
			ListOfPoints.Add(point);
		}
	}
}

void APOIMap::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
