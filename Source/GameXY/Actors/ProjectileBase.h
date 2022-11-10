// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

UCLASS()
class GAMEXY_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component", meta=(AllowPrivateAccess=true))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Component", meta=(AllowPrivateAccess=true))
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Component", meta=(AllowPrivateAccess=true))
	float Damage = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Component", meta=(AllowPrivateAccess=true))
	float MovementSpeed = 200.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* HitParticle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
