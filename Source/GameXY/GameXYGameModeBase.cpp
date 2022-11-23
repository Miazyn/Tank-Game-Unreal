// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameXYGameModeBase.h"
#include "Pawns/PawnTank.h"
#include "Pawns/PawnTurret.h"
#include "PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void AGameXYGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//Hole alle Turrets im Level
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
	TargetTurrets = GetTargetTurretCount();

	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this,0));
	
	HandleGameStart();
	//Win/Lose Condition, Ref var
	//Call HandleGameStart, init Countdown, pawn check
}

void AGameXYGameModeBase::HandleGameStart()
{
	//Start countdown, call blueprint version Gamestart
	GameStart();

	if(PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnableState(false);
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnableState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void AGameXYGameModeBase::HandleGameOver(bool PlayerWon)
{
	//All turrets dead -> win
	//Player dead -> gameover
	//call blueprint version, gameover
	GameOver(PlayerWon);
	
	PlayerTank->HandleDestruction();
	if(PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnableState(false);
		PlayerControllerRef->SetActorTickEnabled(false);
	}
}

void AGameXYGameModeBase::ActorDied(AActor* DeadActor)
{
	//Player -> Lost
	if(DeadActor == PlayerTank)
	{
		HandleGameOver(false);
	}
	else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		TargetTurrets --;
		if(TargetTurrets <= 0)
		{
			HandleGameOver(true);
		}
	}
}

int32 AGameXYGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	
	return TurretActors.Num();
}

FString AGameXYGameModeBase::GetCurrentMap()
{
	FString CurrentMap = GetWorld()->GetMapName();
	return  CurrentMap;
}

void AGameXYGameModeBase::LoadNextLevel(FString currentLevel)
{
	
	//LOAD NEXT LEVEL HERE
	if(currentLevel == "Main_Map")
	{
		UE_LOG(LogTemp, Warning, TEXT("Loading next level"));
	}
	//UGameplayStatics::OpenLevel((UObject*)GGameInstance, FName(TEXT("NewMap1")));
}

