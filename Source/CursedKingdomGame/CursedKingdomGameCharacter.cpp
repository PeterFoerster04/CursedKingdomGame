// Copyright Epic Games, Inc. All Rights Reserved.

#include "CursedKingdomGameCharacter.h"
#include "CursedKingdomGameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Inventory.h"
#include "Item.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACursedKingdomGameCharacter

ACursedKingdomGameCharacter::ACursedKingdomGameCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	CurrentWorld = GetWorld();
	if(CurrentWorld ==nullptr)
	{
		UE_LOG(LogTemp,Display,TEXT("Failed to get world"))
	}

	ItemStoreSpot = CreateDefaultSubobject<USceneComponent>("ItemStoreSpot");
	ItemStoreSpot->SetupAttachment(RootComponent);
	ItemHoldSpot = CreateDefaultSubobject<USceneComponent>("ItemHoldSpot");
	ItemHoldSpot->SetupAttachment(FirstPersonCameraComponent);
	PlayerInventory = CreateDefaultSubobject<UInventory>("Inventory");

	PlayerInventory->Player = this;
}

void ACursedKingdomGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	MaxSprintMovementSpeed = MaxMovementSpeedDefault * SprintMultiplier;
	CurrentStamina = MaxStamina;
	StaminaCurrentCooldownTime = StaminaCooldownTime;

	GetCharacterMovement()->MaxWalkSpeed = MaxMovementSpeedDefault;

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	//UE_LOG(LogTemp,Display,TEXT("%f"),FirstPersonCameraComponent->FieldOfView)
	FirstPersonCameraComponent->FieldOfView = WalkFOV;

}

void ACursedKingdomGameCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ChangeFOV(DeltaSeconds);
	ManageStamina(DeltaSeconds);
}

//////////////////////////////////////////////////////////////////////////// Input

void ACursedKingdomGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACursedKingdomGameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACursedKingdomGameCharacter::Look);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACursedKingdomGameCharacter::Sprint);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACursedKingdomGameCharacter::Interact);

		EnhancedInputComponent->BindAction(ItemSwapAction, ETriggerEvent::Triggered, this, &ACursedKingdomGameCharacter::SwapItem);

		EnhancedInputComponent->BindAction(ItemDropAction, ETriggerEvent::Triggered, this, &ACursedKingdomGameCharacter::DropItem);

		EnhancedInputComponent->BindAction(ItemThrowAction, ETriggerEvent::Triggered, this, &ACursedKingdomGameCharacter::ThrowItem);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ACursedKingdomGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
	if(MovementVector == FVector2D::ZeroVector)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = MaxMovementSpeedDefault;
	}


}

void ACursedKingdomGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X*MouseSens);
		AddControllerPitchInput(LookAxisVector.Y*MouseSens);
	}
}

void ACursedKingdomGameCharacter::Sprint(const FInputActionValue& Value)
{
	if (bIsOnCooldown) {
		bIsSprinting = false;
		return;
	}

	bIsSprinting = Value.Get<bool>();

	GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? MaxSprintMovementSpeed : MaxMovementSpeedDefault;

	//UE_LOG(LogTemp,Display,TEXT("%i"), bIsSprinting)
}

void ACursedKingdomGameCharacter::Interact(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Display,TEXT("Interact press"))

	FHitResult Hit;
	FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
	FVector TraceEnd = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * MaxInteractRange;

	//ignore own actor
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	CurrentWorld->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Pawn, QueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && Hit.GetActor() != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}
	AItem* PossibleItem = Cast<AItem>(Hit.GetActor());

	
	if (PossibleItem != nullptr && !PlayerInventory->CheckInventoryFull())
	{
		UE_LOG(LogTemp, Log, TEXT("Picked Up Actor: %s"), *PossibleItem->GetName());
		PossibleItem->Mesh->SetSimulatePhysics(false);
		PossibleItem->AttachToComponent(ItemStoreSpot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PlayerInventory->AddItem(PossibleItem);
	}
	else if(PlayerInventory->CheckInventoryFull())
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory Full"));
	}

	
}

//sadly attaching actors with physics via code without complications can only be achieved by attaching in this script
//thats why the move item function seems kind of useless now
void ACursedKingdomGameCharacter::SwapItem(const FInputActionValue& Value)
{
	float scroll = Value.Get<float>();

	//if scrolling gets out of range of (into negative or max inventory size) return
	if ((scroll < 0 && PlayerInventory->CurrentItemOutIndex == 0) ||
		(scroll > 0 && PlayerInventory->CurrentItemOutIndex == PlayerInventory->InventorySize - 1)) return;

	if (PlayerInventory->DoesInvHaveItemAtIndex(PlayerInventory->CurrentItemOutIndex))
	{
		PlayerInventory->ItemBundle[PlayerInventory->CurrentItemOutIndex]->
		AttachToComponent(ItemStoreSpot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PlayerInventory->MoveItem();
	}
	
	//in-decrementing the index for item to pull out
	if (scroll > 0) PlayerInventory->CurrentItemOutIndex++;
	else if (scroll < 0) PlayerInventory->CurrentItemOutIndex--;

	if (PlayerInventory->DoesInvHaveItemAtIndex(PlayerInventory->CurrentItemOutIndex))
	{
		PlayerInventory->ItemBundle[PlayerInventory->CurrentItemOutIndex]->
		AttachToComponent(ItemHoldSpot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PlayerInventory->MoveItem(false);
	}
	
	UE_LOG(LogTemp, Display, TEXT("%i"), PlayerInventory->CurrentItemOutIndex)
	
	
}

void ACursedKingdomGameCharacter::DropItem(const FInputActionValue& Value)
{
	float input = Value.Get<float>();

	if(PlayerInventory->DoesInvHaveItemAtIndex(PlayerInventory->CurrentItemOutIndex))
	{
		PlayerInventory->ActivateItem();
	}

	//UE_LOG(LogTemp, Display, TEXT("%f"), input)
}

void ACursedKingdomGameCharacter::ThrowItem(const FInputActionValue& Value)
{
	
	float input = Value.Get<float>();

	if (PlayerInventory->DoesInvHaveItemAtIndex(PlayerInventory->CurrentItemOutIndex))
	{
		PlayerInventory->ActivateItem(true,FirstPersonCameraComponent->GetForwardVector(),ThrowForce);

	}
	
	//UE_LOG(LogTemp, Display, TEXT("%f"), input)
}

void ACursedKingdomGameCharacter::ChangeFOV(float a_Delta)
{
	

	if (bIsSprinting&&MovementVector.Length() > 0)
	{
		FirstPersonCameraComponent->FieldOfView = FMath::Lerp(FirstPersonCameraComponent->FieldOfView, SprintFOV, FOVTransitionSpeed*a_Delta);
	}
	else
	{
		FirstPersonCameraComponent->FieldOfView = FMath::Lerp(FirstPersonCameraComponent->FieldOfView, WalkFOV, FOVTransitionSpeed * a_Delta);
	}
}

void ACursedKingdomGameCharacter::ManageStamina(float a_Delta)
{

	if(bIsSprinting&&!bIsOnCooldown)
	{
		CurrentStamina -= a_Delta * StaminaSubtractionAmount;
	}
	else if(!bIsOnCooldown)
	{
		CurrentStamina += a_Delta * StaminaRechargeAmount;
		if (CurrentStamina > MaxStamina) CurrentStamina = MaxStamina;
	}
	if(CurrentStamina <=0&&!bIsOnCooldown)
	{
		CurrentStamina = 0;
		bIsOnCooldown = true;
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = MaxMovementSpeedDefault;
	}
	if(bIsOnCooldown)
	{
		StaminaCurrentCooldownTime -= a_Delta;
	}
	if(StaminaCurrentCooldownTime <=0)
	{
		StaminaCurrentCooldownTime = StaminaCooldownTime;
		bIsOnCooldown = false;
	}

	
}

void ACursedKingdomGameCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ACursedKingdomGameCharacter::GetHasRifle()
{
	return bHasRifle;
}