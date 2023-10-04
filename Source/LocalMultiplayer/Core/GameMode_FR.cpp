// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_FR.h"

#include "Camera/CameraActor.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Character/GameCamera.h"
#include "LocalMultiplayer/Character/InputReciever_FR.h"
#include "LocalMultiplayer/Character/Player_FR.h"
#include "LocalMultiplayer/UI/PlayerSelectWidget.h"

void AGameMode_FR::BeginPlay()
{
	Super::BeginPlay();

	// Get all GameCamera actors
	TArray<AActor*> GameCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameCamera::StaticClass(), GameCameras);
	if (GameCameras.Num() > 0)
	{
		CameraRef = Cast<AGameCamera>(GameCameras[0]);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No GameCamera found!"));
	}
	
	// Get all PlayerStart actors
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	
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

			SpawnAndPossessInputReceiver(PlayerStart, Index);
		}
	}

	RemoveUnusedCameras();

	PlayerSelectWidget = CreateWidget<UPlayerSelectWidget>(GetWorld(), PlayerSelectWidgetClass);
	if (PlayerSelectWidget)
	{
		PlayerSelectWidget->AddToViewport();
	}
	
}

AInputReciever_FR* AGameMode_FR::SpawnAndPossessInputReceiver(AActor* PlayerStart, const int32 Index)
{
	const auto InputReceiver = GetWorld()->SpawnActorDeferred<AInputReciever_FR>(InputReceiverToSpawn, PlayerStart->GetActorTransform());
	InputReceiver->PlayerIndex = Index;

	// PC needs to possess the input receiver before finish spawning
	auto PC = UGameplayStatics::GetPlayerController(this, Index);
	PC->Possess(InputReceiver);

	InputReceiver->FinishSpawning(PlayerStart->GetActorTransform());
	
	InputReceivers.AddUnique(InputReceiver);

	PC->SetViewTargetWithBlend(CameraRef);
	
	return InputReceiver;
}

void AGameMode_FR::SpawnPlayerAtInputReceiver_Implementation(int32 CurrentPlayerIndex, AInputReciever_FR* InputReceiver, int32 CharacterChoice)
{
	UE_LOG(LogTemp, Display, TEXT("SpawnPlayer %d"), CurrentPlayerIndex);

	// Spawn actor
	const auto Player = GetWorld()->SpawnActorDeferred<APlayer_FR>(PlayerToSpawn, InputReceiver->GetActorTransform());
	Player->CharacterChoice = CharacterChoice;
	Player->FinishSpawning(InputReceiver->GetActorTransform());
	CurrentPlayers.AddUnique(Player);

	// Possess
	auto PC = UGameplayStatics::GetPlayerController(this, CurrentPlayerIndex);
	PC->Possess(Player);

	PC->SetViewTargetWithBlend(CameraRef);

}

void AGameMode_FR::DisplayCharacterCustomize_Implementation(int32 CurrentPlayerIndex)
{
	PlayerSelectWidget->AddCharacterCustomizeWidget(CurrentPlayerIndex);

	InputReceivers[CurrentPlayerIndex]->CharacterCustomizeWidget = PlayerSelectWidget->CharacterCustomizeWidget;
}

void AGameMode_FR::StartGame_Implementation()
{
	if (CurrentPlayers.Num() >= MinPlayersToStart)
	{
		GameStarted();
		
		// print to screen
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Game Started!")));

	}
}

bool AGameMode_FR::GetIsInGame_Implementation()
{
	return bIsInGame;
}

void AGameMode_FR::RemoveUnusedCameras()
{
	TArray<AActor*> Cameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), Cameras);

	for (auto Camera : Cameras)
	{
		Camera->Destroy();
	}
}

void AGameMode_FR::GameStarted()
{
	bIsInGame = true;
	CameraRef->GameStarted(CurrentPlayers);
}

