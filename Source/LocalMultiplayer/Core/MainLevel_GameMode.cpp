// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevel_GameMode.h"

#include "FarmersRush_GameState.h"
#include "GameFramework/PlayerState.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"

void AMainLevel_GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Enable Splitscreen
	GetWorld()->GetGameViewport()->SetForceDisableSplitscreen(false);

	// const auto GameState = GetGameState<AFarmersRush_GameState>();
	for (const auto Player : GameState->PlayerArray)
	{
		const auto PC = Player->GetPlayerController();
		const auto Character = Cast<APlayerFarmerCharacter>(PC->GetPawn());

		Character->AddCamera();
		
		HandleStartingNewPlayer(PC);
	}


	// TODO Do I need a main UI to display information?


}

