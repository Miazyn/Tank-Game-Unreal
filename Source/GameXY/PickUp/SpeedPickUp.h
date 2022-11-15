// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameXY/PickUp.h"
#include "GameXY/Pawns/PawnTank.h"
#include "SpeedPickUp.generated.h"

UCLASS()
class GAMEXY_API ASpeedPickUp : public APickUp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpeedPickUp();

	UFUNCTION(BlueprintCallable)
	void IncreaseSpeed(APawnTank* _Tank);

private:

	UPROPERTY(EditAnywhere)
	float AddedMoveSpeed = 500.f;
	UPROPERTY(EditAnywhere)
	float AddedRotateSpeed = 100.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
