// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_GameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Camera/MainMenuCamera.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"
#include "LocalMultiplayer/Character/MainMenu/PlayerInputDummy.h"

void AMainMenu_GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Get all GameCamera actors
	TArray<AActor*> GameCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainMenuCamera::StaticClass(), GameCameras);
	if (GameCameras.Num() > 0)
	{
		CameraRef = Cast<AMainMenuCamera>(GameCameras[0]);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No GameCamera found!"));
	}	
	
	// Get all player starts
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

	// For each player start create a player controller
	for (auto* PlayerStart : PlayerStarts)
	{
		const int32 Index = FCString::Atoi(*Cast<APlayerStart>(PlayerStart)->PlayerStartTag.ToString());;

		if (PlayerStart)
		{
			// Create a new player if not already created for this player start
			if (!UGameplayStatics::GetPlayerController(this, Index))
			{
				UGameplayStatics::CreatePlayer(this, Index, true);
			}

			SpawnAndPossessDummy(PlayerStart, Index);
		}
	}
}

APlayerInputDummy* AMainMenu_GameMode::SpawnAndPossessDummy(const AActor* PlayerStart, const int32 Index)
{
	// Spawn the dummy
	const auto Dummy = GetWorld()->SpawnActorDeferred<APlayerInputDummy>(DummyToSpawn, PlayerStart->GetTransform());
	Dummy->PlayerIndex = Index;
	
	auto PC = UGameplayStatics::GetPlayerController(this, Index);
	PC->Possess(Dummy);

	Dummy->FinishSpawning(PlayerStart->GetTransform());

	CurrentDummies.AddUnique(Dummy);
	
	PC->SetViewTarget(CameraRef);

	return Dummy;
}

void AMainMenu_GameMode::SpawnCharacterAtDummy(const APlayerInputDummy* Dummy, const int32 PlayerIndex)
{
	const auto Character = GetWorld()->SpawnActorDeferred<APlayerFarmerCharacter>(CharacterToSpawn, Dummy->GetTransform());
	Character->PlayerIndex = PlayerIndex;
	Character->FinishSpawning(Dummy->GetTransform());
	
	CurrentCharacters.AddUnique(Character);
	
	const auto PC = UGameplayStatics::GetPlayerController(this, PlayerIndex);
	PC->Possess(Character);
	PC->SetViewTarget(CameraRef);
}

void AMainMenu_GameMode::DeactivatePlayer(const int32 PlayerIndex)
{
	const auto PC = UGameplayStatics::GetPlayerController(this, PlayerIndex);

	for (auto Dummy : CurrentDummies)
	{
		if (Dummy->PlayerIndex == PlayerIndex)
		{
			PC->Possess(Dummy);
			for (auto Character : CurrentCharacters)
			{
				if (Character->PlayerIndex == PlayerIndex)
				{
					CurrentCharacters.Remove(Character);
					Character->Destroy();
					break;
				}
			}
			break;
		}
	}
	PC->SetViewTarget(CameraRef);
}

