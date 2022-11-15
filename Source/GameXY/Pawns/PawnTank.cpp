// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
	CurrentRotateSpeed = DefaultRotateSpeed;
	CurrentMoveSpeed = DefaultMoveSpeed;
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	if(PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;

		RotateTurretFunction(HitLocation);
	}

}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMovementInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotationInput);
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APawnTank::Fire);

}

bool APawnTank::GetPlayerAlive()
{
	return bIsPlayerAlive;
}


float APawnTank::GetDefaultMoveSpeed()
{
	return DefaultMoveSpeed;
}

float APawnTank::GetDefaultRotateSpeed()
{
	return DefaultRotateSpeed;
}

void APawnTank::IncreaseTankSpeed(float AddedMoveSpeed, float AddedRotateSpeed)
{
	UE_LOG(LogTemp, Error, TEXT("Added Speed"));
	CurrentMoveSpeed += AddedMoveSpeed;
	CurrentRotateSpeed += AddedRotateSpeed;

	GetWorld()->GetTimerManager().SetTimer(
		SpeedUpgradeTimerHandle,this, &APawnTank::ResetTankSpeed, SpeedTimer, false);
}

void APawnTank::ResetTankSpeed()
{
	UE_LOG(LogTemp, Error, TEXT("Reset Speed"));
	CurrentRotateSpeed = DefaultRotateSpeed;
	CurrentMoveSpeed = DefaultMoveSpeed;
}

void APawnTank::CalculateMovementInput(float Value)
{
	MoveDirection = FVector(Value * CurrentMoveSpeed * GetWorld()->DeltaTimeSeconds,0,0);
}

void APawnTank::CalculateRotationInput(float Value)
{
	float RotateAmount = Value * CurrentRotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotator = FRotator(0,RotateAmount,0);
	RotationDirection =FQuat(Rotator);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);

}

