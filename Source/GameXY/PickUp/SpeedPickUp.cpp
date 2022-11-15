// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPickUp.h"

// Sets default values
ASpeedPickUp::ASpeedPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpeedPickUp::IncreaseSpeed(APawnTank* _Tank)
{
	if(_Tank)
	{
		_Tank->IncreaseTankSpeed(AddedMoveSpeed, AddedRotateSpeed);
	}
}


// Called when the game starts or when spawned
void ASpeedPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpeedPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

