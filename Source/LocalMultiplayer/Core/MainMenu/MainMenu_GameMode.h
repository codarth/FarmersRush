// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu_GameMode.generated.h"

class UMainMenuWidget;
class APlayerCustomizer;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API AMainMenu_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:

	// Main menu widget class
	UPROPERTY(EditDefaultsOnly, Category = "Main Menu")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	// Main menu widget
	UPROPERTY(BlueprintReadOnly, Category = "Main Menu")
	UMainMenuWidget* MainMenuWidget;
	
	// Player selection customizer class
	UPROPERTY(EditDefaultsOnly, Category = "Main Menu|Player Customizer")
	TSubclassOf<APlayerCustomizer> PlayerCustomizerClass;
	
	// Player selection customizer
	UPROPERTY(BlueprintReadOnly, Category = "Main Menu|Player Customizer")
	APlayerCustomizer* PlayerCustomizer;
	
	// Player setup button pressed
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void PlayerSetup();

	// Back button pressed
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void BackToMainMenu();

	// Quit game button pressed
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void QuitToDesktop();

	
};
