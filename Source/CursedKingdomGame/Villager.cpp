// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager.h"

#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVillager::AVillager()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereTrigger = CreateDefaultSubobject<USphereComponent>("Trigger");
	SphereTrigger->SetupAttachment(RootComponent);
	//GetCharacterMovement()->MaxWalkSpeed = 8.0f;
}

// Called when the game starts or when spawned
void AVillager::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVillager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVillager::SwapToHealMesh()
{
	if (VillagerHealedMesh == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Heal Mesh Null"));
		return;
	}
	GetMesh()->SetSkeletalMesh(VillagerHealedMesh);
}

