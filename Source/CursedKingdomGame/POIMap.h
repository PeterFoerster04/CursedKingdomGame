// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyItem.h"
#include "POIMap.generated.h"

class APointOfInterest;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class CURSEDKINGDOMGAME_API APOIMap : public AKeyItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map, meta = (AllowPrivateAccess))
	bool MapInHandAndActivated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map, meta = (AllowPrivateAccess))
	TArray<APointOfInterest*> ListOfPoints;

	UPROPERTY()
	TArray<AActor*> ListOfPointActors;


	void TogglePOIVisibility(bool SetVisible);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
