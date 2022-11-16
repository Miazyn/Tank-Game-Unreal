// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlInversionPickUp.h"

// Sets default values
AControlInversionPickUp::AControlInversionPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AControlInversionPickUp::InvertPlayerControls(APawnTank* _Tank)
{
	if(_Tank)
	{
		_Tank->SetUpInversion(InversionTime);
	}	
}

// Called when the game starts or when spawned
void AControlInversionPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AControlInversionPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

