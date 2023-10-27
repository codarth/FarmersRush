// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_GameMode.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Camera/MainMenuCamera.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"
#include "LocalMultiplayer/Character/MainMenu/PlayerInputDummy.h"
#include "LocalMultiplayer/UI/MainMenu_UI.h"

AMainMenu_GameMode::AMainMenu_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainMenu_GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the main menu widget
	MainMenuWidget = CreateWidget<UMainMenu_UI>(GetWorld(), MainMenuWidgetClass);
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
	}
	
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

void AMainMenu_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bStartingGame)
	{
		// get all player pawns
		TArray<AActor*> PlayerPawns;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerFarmerCharacter::StaticClass(), PlayerPawns);
		// loop through to see if all are ready
		int32 NumReady = 0;
		for (const auto Pawn : PlayerPawns)
		{
			if (const auto Character = Cast<APlayerFarmerCharacter>(Pawn))
			{
				if (Character->bIsPlayerReady)
				{
					NumReady++;
				}
			}
		}

		if (PlayerPawns.Num() > 0 && NumReady == PlayerPawns.Num())
		{
			BeginCountdown();
		}
		else
		{
			StopCountdown();
		}
	}
}

APlayerInputDummy* AMainMenu_GameMode::SpawnAndPossessDummy(const AActor* PlayerStart, const int32 Index)
{
	// Spawn the dummy
	const auto Dummy = GetWorld()->SpawnActorDeferred<APlayerInputDummy>(DummyToSpawn, PlayerStart->GetTransform());
	Dummy->PlayerIndex = Index;
	
	const auto PC = UGameplayStatics::GetPlayerController(this, Index);
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

	for (const auto Dummy : CurrentDummies)
	{
		if (Dummy->PlayerIndex == PlayerIndex)
		{
			PC->Possess(Dummy);
			for (const auto Character : CurrentCharacters)
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

void AMainMenu_GameMode::BeginCountdown()
{
	if (MainMenuWidget && !GetWorldTimerManager().IsTimerActive(CountdownTimerHandle))
	{
		MainMenuWidget->CurrentCountdownTime = MainMenuWidget->CountdownTime;
		MainMenuWidget->UpdateCountdown();
		MainMenuWidget->CountdownBorder->SetVisibility(ESlateVisibility::Visible);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AMainMenu_GameMode::UpdateTimer, 1.0f, true);
	}
}

void AMainMenu_GameMode::UpdateTimer()
{
	MainMenuWidget->UpdateCountdown();
	if (MainMenuWidget->CurrentCountdownTime < 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		StartGame();
	}
}

void AMainMenu_GameMode::StopCountdown()
{
	MainMenuWidget->CountdownBorder->SetVisibility(ESlateVisibility::Hidden);
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	MainMenuWidget->CurrentCountdownTime = MainMenuWidget->CountdownTime;
	
}

void AMainMenu_GameMode::StartGame()
{
	// TODO: Start the game
	bStartingGame = true;
	MainMenuWidget->CountdownText->SetText(FText::FromString("Let the farming commence!")); // TODO: Random saying
	UE_LOG(LogTemp, Warning, TEXT("Game started!"));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("Game started!"));
}
