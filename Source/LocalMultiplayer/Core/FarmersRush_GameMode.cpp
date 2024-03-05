// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmersRush_GameMode.h"

#include "CustomGameViewportClient.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Camera/MainMenuCamera.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"
#include "LocalMultiplayer/Character/MainMenu/PlayerInputDummy.h"
#include "LocalMultiplayer/UI/MainMenu/MainMenu_UI.h"
#include "LocalMultiplayer/UI/MainMenu/PlayerInfo_UI.h"

AFarmersRush_GameMode::AFarmersRush_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFarmersRush_GameMode::BeginPlay()
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

	// Disable splitscreen
	GetWorld()->GetGameViewport()->SetForceDisableSplitscreen(true);

	SetupForDummies();
}

void AFarmersRush_GameMode::Tick(float DeltaSeconds)
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

		if (!QuitCountdownTimerHandle.IsValid())
		{
			if (PlayerPawns.Num() > 0 && NumReady == PlayerPawns.Num())
			{
				BeginStartCountdown();
			}
			else
			{
				StopStartCountdown();
			}
		}
	}
}

void AFarmersRush_GameMode::SetupForDummies()
{
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
				const auto PC = UGameplayStatics::CreatePlayer(this, Index, true);
				if (!PC)
				{
					UE_LOG(LogTemp, Warning, TEXT("PC at index %d is invalid!"), Index);
				}
			}

			SpawnAndPossessDummy(PlayerStart, Index);
		}
	}
}

APlayerInputDummy* AFarmersRush_GameMode::SpawnAndPossessDummy(const AActor* PlayerStart, const int32 Index)
{
	// Spawn the dummy
	const auto Dummy = GetWorld()->SpawnActorDeferred<APlayerInputDummy>(DummyToSpawn, PlayerStart->GetTransform());
	Dummy->PlayerIndex = Index;
	Dummy->PlayerDefaultColor = PlayerColors[Index];
	Dummy->bCanActivate = true;

	const auto PC = UGameplayStatics::GetPlayerController(this, Index);
	if (PC)
	{
		PC->Possess(Dummy);

		Dummy->FinishSpawning(PlayerStart->GetTransform());

		CurrentDummies.AddUnique(Dummy);

		PC->SetViewTarget(CameraRef);

		SetupPlayerInfoUI(Index, PC);

		return Dummy;
	}

	return nullptr;
}

void AFarmersRush_GameMode::SpawnCharacterAtDummy(APlayerInputDummy* Dummy, const int32 PlayerIndex)
{
	const auto Character = GetWorld()->SpawnActorDeferred<APlayerFarmerCharacter>(CharacterToSpawn, Dummy->GetTransform());
	Character->PlayerIndex = PlayerIndex;
	Character->PlayerDefaultColor = Dummy->PlayerDefaultColor;
	Character->FinishSpawning(Dummy->GetTransform());

	Dummy->bCanActivate = false;

	CurrentCharacters.AddUnique(Character);

	const auto PC = UGameplayStatics::GetPlayerController(this, PlayerIndex);
	PC->Possess(Character);
	PC->SetViewTarget(CameraRef);

	// Get direction to origin
	const auto Origin = FVector(0.0f, 0.0f, 0.0f);
	const auto Direction = Origin - Character->GetActorLocation();
	const auto NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	Character->SetActorRotation(NewRotation);


	SetupPlayerInfoUI(PlayerIndex, PC);
}

void AFarmersRush_GameMode::DeactivatePlayer(const int32 PlayerIndex)
{
	const auto PC = UGameplayStatics::GetPlayerController(this, PlayerIndex);

	for (const auto Dummy : CurrentDummies)
	{
		if (Dummy->PlayerIndex == PlayerIndex)
		{
			PC->Possess(Dummy);
			Dummy->bCanActivate = true;

			for (const auto Character : CurrentCharacters)
			{
				if (Character->PlayerIndex == PlayerIndex)
				{
					SetupPlayerInfoUI(PlayerIndex, PC);
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

void AFarmersRush_GameMode::BeginQuitCountdown(bool bToMainMenu)
{
	if (MainMenuWidget && !GetWorldTimerManager().IsTimerActive(QuitCountdownTimerHandle))
	{
		bExitToMainMenu = bToMainMenu;
		MainMenuWidget->SetQuitTo(bToMainMenu);
		MainMenuWidget->ResetCountdown();
		MainMenuWidget->UpdateCountdown(false);
		MainMenuWidget->CountdownBorder->SetVisibility(ESlateVisibility::Visible);
		GetWorldTimerManager().SetTimer(QuitCountdownTimerHandle, this, &AFarmersRush_GameMode::UpdateQuitTimer, 1.0f, true);
	}
}

void AFarmersRush_GameMode::UpdateQuitTimer()
{
	MainMenuWidget->UpdateCountdown(false);
	if (MainMenuWidget->CurrentCountdownTime < 0)
	{
		if (bExitToMainMenu)
		{
			StopQuitCountdown();
			BackToMainMenu();
		}
		else
		{
			// Exit the game
			UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
		}
	}
}

void AFarmersRush_GameMode::StopQuitCountdown()
{
	MainMenuWidget->CountdownBorder->SetVisibility(ESlateVisibility::Hidden);
	GetWorldTimerManager().ClearTimer(QuitCountdownTimerHandle);
	MainMenuWidget->ResetCountdown();
}

void AFarmersRush_GameMode::BeginStartCountdown()
{
	if (MainMenuWidget && !GetWorldTimerManager().IsTimerActive(StartCountdownTimerHandle))
	{
		MainMenuWidget->ResetCountdown();
		MainMenuWidget->UpdateCountdown(true);
		MainMenuWidget->CountdownBorder->SetVisibility(ESlateVisibility::Visible);
		GetWorldTimerManager().SetTimer(StartCountdownTimerHandle, this, &AFarmersRush_GameMode::UpdateStartTimer, 1.0f, true);
	}
}

void AFarmersRush_GameMode::UpdateStartTimer()
{
	MainMenuWidget->UpdateCountdown(true);
	if (MainMenuWidget->CurrentCountdownTime < 0)
	{
		GetWorldTimerManager().ClearTimer(StartCountdownTimerHandle);
		StartGame();
	}
}

void AFarmersRush_GameMode::StopStartCountdown()
{
	MainMenuWidget->CountdownBorder->SetVisibility(ESlateVisibility::Hidden);
	GetWorldTimerManager().ClearTimer(StartCountdownTimerHandle);
	MainMenuWidget->ResetCountdown();
}

void AFarmersRush_GameMode::StartGame()
{
	bStartingGame = true;
	MainMenuWidget->CountdownText->SetText(FText::FromString("Let the farming commence!")); // TODO: Random saying

	GetWorldTimerManager().SetTimer(StartCountdownTimerHandle, this, &AFarmersRush_GameMode::TransitionToGame, 2.0f, false);

	// UE_LOG(LogTemp, Warning, TEXT("Game started!"));
	// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, TEXT("Game started!"));
}

void AFarmersRush_GameMode::TransitionToGame()
{
	MainMenuWidget->PlayerInfo_1->SetVisibility(ESlateVisibility::Hidden);
	MainMenuWidget->PlayerInfo_2->SetVisibility(ESlateVisibility::Hidden);
	MainMenuWidget->PlayerInfo_3->SetVisibility(ESlateVisibility::Hidden);
	MainMenuWidget->PlayerInfo_4->SetVisibility(ESlateVisibility::Hidden);

	MainMenuWidget->CountdownBorder->SetVisibility(ESlateVisibility::Hidden);

	LevelLoading();
}

void AFarmersRush_GameMode::FadeCamera(bool bFadeIn /*= false*/)
{
	for (auto Character : CurrentCharacters)
	{
		if (const auto PC = UGameplayStatics::GetPlayerController(this, Character->PlayerIndex))
		{
			if (bFadeIn)
			{
				PC->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, 2.0f, FLinearColor::Black, false, true);
			}
			else
			{
				PC->PlayerCameraManager->StartCameraFade(0.0f, 1.0f, 1.5f, FLinearColor::Black, false, true);
			}
		}
	}
}

void AFarmersRush_GameMode::SetupPlayerCamera()
{
	// Add Camera to player and set it as view target
	for (const auto Character : CurrentCharacters)
	{
		Character->AddCamera();

		if (const auto PC = UGameplayStatics::GetPlayerController(this, Character->PlayerIndex))
		{
			PC->SetViewTarget(Character);
		}
	}
}

void AFarmersRush_GameMode::CleanupDummies()
{
	for (const auto Dummy : CurrentDummies)
	{
		Dummy->SetActorTickEnabled(false);
	}

	// Disable all dummy controllers
	for (const auto Dummy : CurrentDummies)
	{
		//Get controller and remove it
		if (const auto PC = UGameplayStatics::GetPlayerController(this, Dummy->PlayerIndex))
		{
			if (Cast<APlayerInputDummy>(PC->GetPawn()))
			{
				PC->UnPossess();
				//PC->Destroy();
			}
		}
		// Delete All Dummies
		Dummy->Destroy();
	}
	CurrentDummies.Empty();

	GEngine->ForceGarbageCollection();
}

void AFarmersRush_GameMode::LevelLoading()
{
	FadeCamera();

	GetWorldTimerManager().SetTimer(DummyCleanupTimer, this, &AFarmersRush_GameMode::CleanupDummies, 1.5f, false);
	GetWorldTimerManager().SetTimer(LoadLevelTimer, this, &AFarmersRush_GameMode::LoadLevel, 2.5f, false);
	GetWorldTimerManager().SetTimer(UnloadLevelTimer, this, &AFarmersRush_GameMode::UnloadMainMenu, 2.5f, false);
}

void AFarmersRush_GameMode::LoadLevel()
{
	CurrentLevelIndex = CurrentCharacters.Num() - 1;
	const auto LevelToLoad = MainLevelNames[CurrentLevelIndex];

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = 1;
	UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);

	if (CurrentCharacters.Num() > 1)
	{
		// Enable splitscreen
		auto Viewport = GetWorld()->GetGameViewport();
		Viewport->SetForceDisableSplitscreen(false);
		Cast<UCustomGameViewportClient>(Viewport)->ActivePlayers = CurrentCharacters.Num();
	}

	AdjustCharacterLocation();
	SetupPlayerCamera();

	FadeCamera(true);
}

void AFarmersRush_GameMode::UnloadLevel()
{
	const auto LevelToUnload = MainLevelNames[CurrentLevelIndex];;

	FLatentActionInfo LatentInfo;
	UGameplayStatics::UnloadStreamLevel(this, LevelToUnload, LatentInfo, true);
}

void AFarmersRush_GameMode::LoadMainMenu()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = 1;
	UGameplayStatics::LoadStreamLevel(this, MainMenuLevelName, true, true, LatentInfo);

	// Disable splitscreen
	auto Viewport = GetWorld()->GetGameViewport();
	Viewport->SetForceDisableSplitscreen(false);
	Cast<UCustomGameViewportClient>(Viewport)->ActivePlayers = 1;

	FadeCamera(true);

	for (const auto Character : CurrentCharacters)
	{
		if (const auto PC = UGameplayStatics::GetPlayerController(this, Character->PlayerIndex))
		{
			if (Cast<APlayerInputDummy>(PC->GetPawn()))
			{
				PC->UnPossess();
				PC->Destroy();
			}
		}

		Character->Destroy();
	}
	CurrentCharacters.Empty();

	bStartingGame = false;
}

void AFarmersRush_GameMode::UnloadMainMenu()
{
	const FLatentActionInfo LatentInfo;
	UGameplayStatics::UnloadStreamLevel(this, MainMenuLevelName, LatentInfo, true);
}

void AFarmersRush_GameMode::BackToMainMenu()
{
	FadeCamera();

	GetWorldTimerManager().SetTimer(DummyCleanupTimer, this, &AFarmersRush_GameMode::SetupForDummies, 2.8f, false);
	GetWorldTimerManager().SetTimer(LoadLevelTimer, this, &AFarmersRush_GameMode::LoadMainMenu, 2.5f, false);
	GetWorldTimerManager().SetTimer(UnloadLevelTimer, this, &AFarmersRush_GameMode::UnloadLevel, 2.5f, false);
}

void AFarmersRush_GameMode::AdjustCharacterLocation()
{
	for (auto Character : CurrentCharacters)
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

		for (auto* PlayerStart : PlayerStarts)
		{
			const int32 Index = FCString::Atoi(*Cast<APlayerStart>(PlayerStart)->PlayerStartTag.ToString());

			if (PlayerStart && Index == Character->PlayerIndex)
			{
				Character->SetActorLocation(PlayerStart->GetActorLocation());
			}
		}
	}
}

void AFarmersRush_GameMode::ActivatePlayerUI(const int32 Index, const APlayerController* PC, UPlayerInfo_UI* const UI)
{
	UI->PlayerCharacter = PC->GetPawn();
	if (UI->PlayerCharacter)
	{
		const auto Pawn = UI->PlayerCharacter;
		if (const auto Player = Cast<APlayerFarmerCharacter>(Pawn))
		{
			UI->Join_NameText->SetText(FText::FromString("Player " + FString::FromInt(Index + 1)));
			UI->PlayerColor_Border->SetBrushFromMaterial(Player->PlayerDefaultColor);
			UI->PlayerColor_Border->SetVisibility(ESlateVisibility::Visible);
			UI->Ready_Text->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UI->Join_NameText->SetText(FText::FromString("Press Start To Join"));
			UI->PlayerColor_Border->SetVisibility(ESlateVisibility::Hidden);
			UI->Ready_Text->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AFarmersRush_GameMode::SetupPlayerInfoUI(const int32 Index, const APlayerController* PC)
{
	UPlayerInfo_UI* UI;
	switch (Index)
	{
	case 0:
		UI = MainMenuWidget->PlayerInfo_1;
		ActivatePlayerUI(Index, PC, UI);
		break;
	case 1:
		UI = MainMenuWidget->PlayerInfo_2;
		ActivatePlayerUI(Index, PC, UI);
		break;
	case 2:
		UI = MainMenuWidget->PlayerInfo_3;
		ActivatePlayerUI(Index, PC, UI);
		break;
	case 3:
		UI = MainMenuWidget->PlayerInfo_4;
		ActivatePlayerUI(Index, PC, UI);
		break;;
	default:
		break;
	}
}
