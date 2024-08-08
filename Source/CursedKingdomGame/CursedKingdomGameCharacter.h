// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnumLibrary.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CursedKingdomGameCharacter.generated.h"

class AItem;
class UKingdomGameInstance;
class UInventory;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACursedKingdomGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemSwapAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemDropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemThrowAction;


public:
	ACursedKingdomGameCharacter();

protected:
	virtual void BeginPlay()override;
	virtual  void Tick(float DeltaSeconds) override;

public:
	UPROPERTY()
	UKingdomGameInstance* Instance = nullptr;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY()
	UWorld* CurrentWorld;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess))
	float MouseSens = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
	float SprintMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float WalkFOV = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float SprintFOV = 120.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float FOVTransitionSpeed = 1.5f;

	FVector2D MovementVector;
	FVector CameraStartLoc;


	//Stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
	bool PlayerDied = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess))
	float HealthReGenPerSec = 2.0f;

	//Movement Values
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float MaxMovementSpeedDefault = 500.0f;
	float MaxSprintMovementSpeed;
	bool bIsWalking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float ThrowForce = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float MaxInteractRange = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess))
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess))
	float MaxStamina = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess))
	float CurrentStamina = 0.0f;
	float StaminaSubtractionAmount = 10.0f;
	float StaminaRechargeAmount = 5.0f;

	float StaminaCooldownTime = 5.0f;
	float StaminaCurrentCooldownTime = 0.0f;

	bool bIsOnCooldown = false;
	bool bTestBool = false;
	bool bIsFocusingItem = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map, meta = (AllowPrivateAccess))
	bool bHasMapInHand = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess))
	bool bIsInWater = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map, meta = (AllowPrivateAccess))
	bool bPressedInteract = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tuto, meta = (AllowPrivateAccess))
	int CurrentTutoIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tuto, meta = (AllowPrivateAccess))
	bool TutoBlocked = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	bool bJustPickedUpItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	bool bPlayerInventoryFull = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess))
	EItemName NameOfLastPickedItem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess))
	EItemName NameOfCurrentItemInHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	int ItemsInInventory = 0;

	void ManageStamina(float a_Delta);
	void ManageHealth(float a_Delta);
	UFUNCTION(BlueprintCallable)
	void TakePlayerDamage(float a_Damage);
	void ManagePostProcessEffects(float a_Delta);
	void CheckForItemInFront();
	void ManageViewBobbing(float a_Delta);

	//usually these functions belong into the inventory class
	//but attaching actors in component classes caused issues
	UFUNCTION(BlueprintCallable)
	void SaveInventory();

	void LoadInventory();


	void TryToLoadSaveData();

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	UFUNCTION(BlueprintCallable)
	void CheckJumpTuto();

	void HandlePOIMap(AItem* ItemToCheck, bool SetVisibility);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	USceneComponent* ItemStoreSpot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	USceneComponent* ItemHoldSpot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess))
	UInventory* PlayerInventory;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void SwapItem(const FInputActionValue& Value);

	void DropItem(const FInputActionValue& Value);

	void ThrowItem(const FInputActionValue& Value);

	void ChangeFOV(float a_Delta);

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemSwap();
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerDied();
	
	void Die();

	void Resurrect();


	FTimerHandle DeathTimerHandle;


	//quick and dirty pls do not kill me :(
	struct TutorialBools
	{
		bool pressedW;
		bool pressedA;
		bool pressedS;
		bool pressedD;
	};
	TutorialBools TutoBoolsToCheck;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

