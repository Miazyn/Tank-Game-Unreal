// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameXY/GameXYGameModeBase.h"
#include "HealthComponent.generated.h"

class AGameXYGameModeBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEXY_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();


private:
	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100;
	float CurrentHealth = 0.f;

	AGameXYGameModeBase* GameModeRef;
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
};
