// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameXY/PickUp.h"
#include "GameXY/Pawns/PawnTank.h"
#include "FiringSpeedBoostPickUp.generated.h"

UCLASS()
class GAMEXY_API AFiringSpeedBoostPickUp : public APickUp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFiringSpeedBoostPickUp();

	UFUNCTION(BlueprintCallable)
	void StartFastFireMode(APawnTank* Tank);

private:
	UPROPERTY(EditAnywhere)
	float FastFireCooldown = .2f;
	UPROPERTY(EditAnywhere)
	float PickUpCooldown = 5.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
