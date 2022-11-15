// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"


// Sets default values
AHealthPickUp::AHealthPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHealthPickUp::ApplyHealthPickUp(UHealthComponent* HealthComponent)
{
	if(HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Health component exists on object"));
		HealthComponent->AddHealth(AddedHealth);
	}
}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

