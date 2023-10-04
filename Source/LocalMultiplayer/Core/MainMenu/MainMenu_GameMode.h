// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu_GameMode.generated.h"

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
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};
