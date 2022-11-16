// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class GAMEXY_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	APawnTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	float ReturnDistanceToPlayer();
	UPROPERTY(EditAnywhere)
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere)
	float FireRange = 2000.f;
                                   
	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn;
                                   
	void CheckFireCondition();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

	
};
