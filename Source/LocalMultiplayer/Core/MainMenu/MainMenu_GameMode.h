// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu_GameMode.generated.h"

class APlayerCustomizePawn;
class UInputMappingContext;
class UInputAction;
class UMainMenuWidget;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API AMainMenu_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	// void RemoveUnusedCameras();
	
public:

	// Main menu widget class
	UPROPERTY(EditDefaultsOnly, Category = "Main Menu")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	// Main menu widget
	UPROPERTY(BlueprintReadOnly, Category = "Main Menu")
	UMainMenuWidget* MainMenuWidget;

	// Player customizer class
	UPROPERTY(EditDefaultsOnly, Category = "Main Menu")
	TSubclassOf<APlayerCustomizePawn> PlayerCustomizerPawnClass;

	// Player customizer
	UPROPERTY(BlueprintReadOnly, Category = "Main Menu")
	APlayerCustomizePawn* PlayerCustomizerPawn;

	UPROPERTY(BlueprintReadOnly, Category = "Main Menu")
	TArray<APlayerCustomizePawn*> PlayerCustomizers;

	// Spawn and possess player customizer
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void SpawnAndPossessPlayerCustomizer(const int32 PlayerIndex);

};
