// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Character/MainMenu/PlayerCustomizePawn.h"
#include "LocalMultiplayer/UI/MainMenu/MainMenuWidget.h"
#include "LocalMultiplayer/UI/MainMenu/PlayerSlot.h"

void AMainMenu_GameMode::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	(MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass))->AddToViewport();

	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->bShowMouseCursor = true;

	auto PlayerSlots = MainMenuWidget->PlayerSlotBox->GetAllChildren();
	if (PlayerSlots.Num() > 0)
	{
		for (const auto Widget : PlayerSlots)
		{
			if(const auto Slot = Cast<UPlayerSlot>(Widget))
			{
				if (!UGameplayStatics::GetPlayerController(this, Slot->PlayerIndex))
				{
					UGameplayStatics::CreatePlayer(this, Slot->PlayerIndex,true);
				}

				SpawnAndPossessPlayerCustomizer(Slot->PlayerIndex);
			}
		}
	}
}

void AMainMenu_GameMode::SpawnAndPossessPlayerCustomizer(const int32 PlayerIndex)
{
	PlayerCustomizerPawn = GetWorld()->SpawnActorDeferred<APlayerCustomizePawn>(PlayerCustomizerPawnClass, FTransform::Identity);
	PlayerCustomizerPawn->SetPlayerIndex(PlayerIndex);

	auto PC = UGameplayStatics::GetPlayerController(this, PlayerIndex);
	PC->Possess(PlayerCustomizerPawn);

	PlayerCustomizerPawn->FinishSpawning(FTransform::Identity);

	PlayerCustomizers.AddUnique(PlayerCustomizerPawn);
}



