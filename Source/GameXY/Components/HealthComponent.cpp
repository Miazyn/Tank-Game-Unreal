// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameXY/GameXYGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = DefaultHealth;
	GameModeRef = Cast<AGameXYGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage == 0 || CurrentHealth <= 0)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);

	if(CurrentHealth <= 0)
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Gamemode is invalid or wrong parent!!!"));
		}
	}
}




