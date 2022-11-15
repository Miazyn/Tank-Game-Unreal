// Fill out your copyright notice in the Description page of Project Settings.


#include "FiringSpeedBoostPickUp.h"

// Sets default values
AFiringSpeedBoostPickUp::AFiringSpeedBoostPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFiringSpeedBoostPickUp::StartFastFireMode(APawnTank* Tank)
{
	if(Tank)
	{
		Tank->SetFastFireValue(FastFireCooldown, PickUpCooldown);
	}
}

// Called when the game starts or when spawned
void AFiringSpeedBoostPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFiringSpeedBoostPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

