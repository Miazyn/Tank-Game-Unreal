// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacleBase::AObstacleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle Mesh"));
	ObstacleMesh->SetupAttachment(RootComponent);

}


// Called when the game starts or when spawned
void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

