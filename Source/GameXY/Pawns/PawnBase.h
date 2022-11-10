// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;
class UMatineeCameraShake;

UCLASS()
class GAMEXY_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

	void RotateTurretFunction(FVector LookAtTarget);
	void Fire();
	virtual void HandleDestruction();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta= (AllowPrivateAccess = true))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile Base", meta= (AllowPrivateAccess = true))
	TSubclassOf<AProjectileBase> ProjectileClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component", meta = (AllowPrivateAccess = true))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "VFX")
	FVector VFXScale = FVector(8.f, 8.f, 8.f);
	UPROPERTY(EditAnywhere, Category = "VFX")
	TSubclassOf<UMatineeCameraShake> DeathCameraShake;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
