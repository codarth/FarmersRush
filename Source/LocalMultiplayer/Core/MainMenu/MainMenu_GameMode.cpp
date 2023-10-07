// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Character/MainMenu/PlayerCustomizeSlot.h"
#include "LocalMultiplayer/UI/MainMenu/MainMenuWidget.h"
#include "LocalMultiplayer/UI/MainMenu/PlayerSlot.h"

void AMainMenu_GameMode::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	(MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass))->AddToViewport();
	PlayerController->bShowMouseCursor = true;

	auto PlayerSlots = MainMenuWidget->PlayerSlotBox->GetAllChildren();
	if (PlayerSlots.Num() > 0)
	{
		for (const auto Widget : PlayerSlots)
		{
			if(const auto Slot = Cast<UPlayerSlot>(Widget); !UGameplayStatics::GetPlayerController(this, Slot->PlayerIndex))
			{
				UGameplayStatics::CreatePlayer(this, Slot->PlayerIndex,true);
			}
		}
	}

	// RemoveUnusedCameras();
}

// void AMainMenu_GameMode::RemoveUnusedCameras()
// {
// 	TArray<AActor*> Cameras;
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), Cameras);
//
// 	for (auto* Camera : Cameras)
// 	{
// 		Camera->Destroy();
// 	}
// }

void AMainMenu_GameMode::SpawnAndPossessPlayerCustomizer(const int32 PlayerIndex)
{
	PlayerCustomizerSlot = GetWorld()->SpawnActorDeferred<APlayerCustomizeSlot>(PlayerCustomizerSlotClass, FTransform::Identity);
	PlayerCustomizerSlot->SetPlayerIndex(PlayerIndex);

	auto PC = UGameplayStatics::GetPlayerController(this, PlayerIndex);
	PC->Possess(PlayerCustomizerSlot);

	PlayerCustomizerSlot->FinishSpawning(FTransform::Identity);	
}



