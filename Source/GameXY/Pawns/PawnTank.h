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
private:
	UPROPERTY(EditAnywhere)
	float SpeedTimer = 2.f;

	FTimerHandle SpeedUpgradeTimerHandle;

	bool bIsPlayerAlive = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	float CurrentMoveSpeed = 0.f;
	UPROPERTY(VisibleAnywhere)
	float CurrentRotateSpeed = 0.f;
	UPROPERTY(EditAnywhere)
	float DefaultMoveSpeed = 800.f;
	UPROPERTY(EditAnywhere)
	float DefaultRotateSpeed = 150.f;

	UFUNCTION(BlueprintCallable)
	float GetDefaultMoveSpeed();
	UFUNCTION(BlueprintCallable)
	float GetDefaultRotateSpeed();

	
	FVector MoveDirection;
	FQuat RotationDirection;

	void CalculateMovementInput(float Value);
	void CalculateRotationInput(float Value);

	void Move();
	void Rotate();

	void HandleFiringMode();
	void ResetFiring();
	void SetFastFireMode();

	bool FastFireModeOn = false;
	bool hasFiredRecently = false;

	FTimerHandle FiringPickUpTimerHandle;
	float FirePickUpTimer = 0.f;
	
	FTimerHandle FireCooldownTimerHandle;
	UPROPERTY(EditAnywhere)
	float FireCooldown = 1.f;
	
	float FastFireCooldown = 0.f;
	float FireDefaultCooldown = 0.f;
	
	APlayerController* PlayerControllerRef;
	
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
