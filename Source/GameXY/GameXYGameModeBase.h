// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameXYGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;
UCLASS()
class GAMEXY_API AGameXYGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


private:
	APlayerControllerBase* PlayerControllerRef;
	APawnTank* PlayerTank;
	int32 TargetTurrets = 0; //Anzahl der zu zerstörenden Turrets

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

public:
	void ActorDied(AActor* DeadActor);

	int32 GetTargetTurretCount();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Game Loop")
	int32 StartDelay = 3;
protected:
	virtual  void BeginPlay() override;


	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
};
