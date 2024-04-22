// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CursedKingdomGameCharacter.generated.h"

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

public:
	ACursedKingdomGameCharacter();

protected:
	virtual void BeginPlay();
	virtual  void Tick(float DeltaSeconds) override;

public:
		
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
	float MouseSens = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess))
	float SprintMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float WalkFOV = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float SprintFOV = 120.0f;

	FVector2D MovementVector;

	bool bIsSprinting = false;

	//Movement Values
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess))
	float MaxMovementSpeedDefault = 500.0f;
	float MaxSprintMovementSpeed;
	

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);


	void ChangeFOV(float a_Delta);

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

