// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "HealthPickUp.generated.h"


UCLASS()
class GAMEXY_API AHealthPickUp : public APickUp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickUp();

	UFUNCTION(BlueprintCallable)
    void ApplyHealthPickUp(UHealthComponent* HealthComponent);

	
	float AddedHealth = 20.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
