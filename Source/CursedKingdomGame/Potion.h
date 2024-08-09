// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyItem.h"
#include "NiagaraSystem.h"
#include "Potion.generated.h"

class UMaterialInterface;
/**
 * 
 */
UCLASS()
class CURSEDKINGDOMGAME_API APotion : public AKeyItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Systems,meta=(AllowPrivateAccess))
	UNiagaraSystem* HealExplosionSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess))
	bool bUsed;

};
