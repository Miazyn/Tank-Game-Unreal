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
private:

	bool bIsPlayerAlive = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 200.f;
	UPROPERTY(EditAnywhere)
	float RotateSpeed = 100.f;

	FVector MoveDirection;
	FQuat RotationDirection;

	void CalculateMovementInput(float Value);
	void CalculateRotationInput(float Value);

	void Move();
	void Rotate();

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
