// Fill out your copyright notice in the Description page of Project Settings.


#include "IceProjectile.h"

#include "GameXY/Pawns/PawnTank.h"

// Sets default values
AIceProjectile::AIceProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AIceProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	
}


// Called when the game starts or when spawned
void AIceProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIceProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

