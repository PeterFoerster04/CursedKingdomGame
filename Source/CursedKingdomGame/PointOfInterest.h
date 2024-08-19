// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "PointOfInterest.generated.h"


class UWidgetComponent;

UCLASS()
class CURSEDKINGDOMGAME_API APointOfInterest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointOfInterest();


	//to display icon in world
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Comps,meta=(AllowPrivateAccess))
	UWidgetComponent* WidgetComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
