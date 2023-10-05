// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/UI/MainMenuWidget.h"

void AMainMenu_GameMode::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	(MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass))->AddToViewport();
	PlayerController->bShowMouseCursor = true;
}

void AMainMenu_GameMode::PlayerSetup()
{
	// Hide current menu and load player customization menu
	MainMenuWidget->HideMainButtonsBorder();
}

void AMainMenu_GameMode::BackToMainMenu()
{
	// Hide current menu and load main menu
	MainMenuWidget->ShowMainButtonsBorder();
}

void AMainMenu_GameMode::QuitToDesktop()
{
}

