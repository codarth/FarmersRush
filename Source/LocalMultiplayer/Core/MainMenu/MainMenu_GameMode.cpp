// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_GameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Camera/MainMenuCamera.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"

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

			SpawnAndPossessCharacter(PlayerStart, Index);
		}
	}
}

APlayerFarmerCharacter* AMainMenu_GameMode::SpawnAndPossessCharacter(const AActor* PlayerStart, const int32 Index)
{
	const auto Character = GetWorld()->SpawnActorDeferred<APlayerFarmerCharacter>(CharacterToSpawn, PlayerStart->GetTransform());

	const auto PlayerController = UGameplayStatics::GetPlayerController(this, Index);
	if (PlayerController)
	{
		PlayerController->Possess(Character);
	}

	Character->FinishSpawning(PlayerStart->GetTransform());

	PlayerController->SetViewTarget(CameraRef);
	
	return Character;
}

