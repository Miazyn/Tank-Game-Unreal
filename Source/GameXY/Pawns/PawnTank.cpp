// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameXY/Components/HealthComponent.h"

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
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APawnTank::HandleFiringMode);

}

void APawnTank::HandleFiringMode()
{
	if(!hasFiredRecently)
	{
		Fire();
	}
}
void APawnTank::Fire()
{
	Super::Fire();
	hasFiredRecently = true;
	if(FastFireModeOn)
	{
		FireDefaultCooldown = FastFireCooldown;
	}else
	{
		FireDefaultCooldown = FireCooldown;
	}
	GetWorld()->GetTimerManager().SetTimer(
		FireCooldownTimerHandle,
		this,
		&APawnTank::ResetFiring,
		FireDefaultCooldown,
		false);
}

void APawnTank::ResetFiring()
{
	hasFiredRecently = false;
}

void APawnTank::SetFastFireValue(float _FastFireCooldown, float _PickUpTimer)
{
	FastFireCooldown = _FastFireCooldown;
	FirePickUpTimer = _PickUpTimer;
	SetFastFireMode();
}

void APawnTank::SetFastFireMode()
{
	FastFireModeOn = !FastFireModeOn;
	if(FastFireModeOn)
	{
		UE_LOG(LogTemp, Error,TEXT("Fast Fire on"));
		GetWorld()->GetTimerManager().SetTimer(
		FiringPickUpTimerHandle,
		this,
		&APawnTank::SetFastFireMode,
		FirePickUpTimer,
		false);
	}
	else
	{
		UE_LOG(LogTemp, Error,TEXT("Fast Fire off"));
		GetWorld()->GetTimerManager().ClearTimer(FiringPickUpTimerHandle);
	}
}

void APawnTank::FreezeMovement(float _FreezeMultiplier, float _FreezeCooldown)
{
	if(!IsFrozen)
	{
		CurrentMoveSpeed = CurrentMoveSpeed * _FreezeMultiplier;
		CurrentRotateSpeed = CurrentRotateSpeed * _FreezeMultiplier;
		IsFrozen = true;
		UE_LOG(LogTemp, Error,TEXT("Freeze is on"));
	//Only make time longer?
	GetWorld()->GetTimerManager().SetTimer(
			FreezeTimeHandle,
			this,
			&APawnTank::UnfreezeMovement,
			_FreezeCooldown,
			false);
	}
}

void APawnTank::UnfreezeMovement()
{
	IsFrozen = false;
	ResetTankSpeed();
}

bool APawnTank::GetPlayerAlive()
{
	return bIsPlayerAlive;
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


