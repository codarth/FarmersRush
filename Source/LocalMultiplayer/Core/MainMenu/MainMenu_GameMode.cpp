// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainMenu_GameMode::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	CreateWidget(PlayerController, MainMenuWidgetClass)->AddToViewport();
	PlayerController->bShowMouseCursor = true;
}
