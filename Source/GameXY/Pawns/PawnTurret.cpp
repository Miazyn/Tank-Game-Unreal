// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"

#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		FireRateTimerHandle,this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerPawn && ReturnDistanceToPlayer() <= FireRange)
	{
		RotateTurretFunction(PlayerPawn->GetActorLocation());
	}
}

void APawnTurret::CheckFireCondition()
{
	if(!PlayerPawn || !PlayerPawn->GetPlayerAlive())
	{
		return;
	}
	if(ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if(!PlayerPawn)
	{
		return 0.f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
