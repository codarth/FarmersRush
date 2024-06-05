// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UPlayerGameStatus;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:

	APlayerHUD();

protected:
	
	virtual void BeginPlay() override;

public:

	void DisplayPlayerStatus();
	void HidePlayerStatus();

	void UpdatePlayerMoney();
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UPlayerGameStatus> PlayerGameStatusClass;

protected:

	UPROPERTY()
	UPlayerGameStatus* PlayerGameStatusWidget;
};
