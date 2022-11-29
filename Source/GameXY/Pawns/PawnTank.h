// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class GAMEXY_API APawnTank : public APawnBase
{
	GENERATED_BODY()
public:
	APawnTank();
	
	virtual void HandleDestruction() override;
	virtual void Fire() override;
	
	void IncreaseTankSpeed(float AddedMoveSpeed, float AddedRotateSpeed);
	void ResetTankSpeed();
	
	void SetFastFireValue(float _FastFireCooldown, float _PickUpTimer);

	UFUNCTION(BlueprintCallable)
	void FreezeMovement(float _FreezeMultiplier, float _FreezeCooldown);

	void SetUpInversion(float _InversionTime);
private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool IsControlInverted = false;
	void InvertControls();
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FTimerHandle InversionTimerHandle;
	/*****FREEZE******/
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FTimerHandle FreezeTimeHandle;
	bool IsFrozen = false;

	void UnfreezeMovement();
	
	/*****SPEEDUP******/
	UPROPERTY(EditAnywhere)
	float SpeedTimer = 2.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FTimerHandle SpeedUpgradeTimerHandle;
	
	/*****COMPONENTS******/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	UCameraComponent* Camera;
	
	bool bIsPlayerAlive = true;
	
	APlayerController* PlayerControllerRef;
	
	/*****MOVEMENT******/
	UPROPERTY(VisibleAnywhere)
	float CurrentMoveSpeed = 0.f;
	UPROPERTY(VisibleAnywhere)
	float CurrentRotateSpeed = 0.f;
	UPROPERTY(EditAnywhere)
	float DefaultMoveSpeed = 800.f;
	UPROPERTY(EditAnywhere)
	float DefaultRotateSpeed = 150.f;

	FVector MoveDirection;
	FQuat RotationDirection;

	void CalculateMovementInput(float Value);
	void CalculateRotationInput(float Value);

	void Move();
	void Rotate();

	void InvertedMove();
	void InvertedRotate();

	/*****FIREMODE******/
	void HandleFiringMode();
	void ResetFiring();
	void SetFastFireMode();

	bool FastFireModeOn = false;
	bool hasFiredRecently = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FTimerHandle FiringPickUpTimerHandle;
	float FirePickUpTimer = 0.f;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FTimerHandle FireCooldownTimerHandle;
	UPROPERTY(EditAnywhere)
	float FireCooldown = 1.f;
	
	float FastFireCooldown = 0.f;
	float FireDefaultCooldown = 0.f;
	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetPlayerAlive();
};
