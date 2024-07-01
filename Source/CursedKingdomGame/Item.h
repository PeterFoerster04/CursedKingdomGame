// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnumLibrary.h"
#include "Item.generated.h"





UCLASS()
class CURSEDKINGDOMGAME_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess))
	EItemName Name;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Comps, meta= (AllowPrivateAccess))
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	UFUNCTION(BlueprintImplementableEvent)
	void OnItemThrow();
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemPickUp();
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemDrop();

	
};
