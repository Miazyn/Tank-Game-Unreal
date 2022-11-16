// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameXY/PickUp.h"
#include "GameXY/Pawns/PawnTank.h"
#include "ControlInversionPickUp.generated.h"

UCLASS()
class GAMEXY_API AControlInversionPickUp : public APickUp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AControlInversionPickUp();

	UFUNCTION(BlueprintCallable)
	void InvertPlayerControls(APawnTank* _Tank);
private:
	UPROPERTY(EditAnywhere)
	float InversionTime = 3.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
