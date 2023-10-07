// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSlot.generated.h"

class UVerticalBox;
class UButtonBase;
class UTextBlock;
class UBorder;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UPlayerSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	// Border for the player slot
	UPROPERTY(BlueprintReadWrite, Category = "Player Slot", meta = (BindWidget))
	UVerticalBox* PlayerSlotBox;

	// Player text
	UPROPERTY(BlueprintReadWrite, Category = "Player Slot", meta = (BindWidget))
	UTextBlock* JoinAndPlayerText;

	// Join/Ready text
	UPROPERTY(BlueprintReadWrite, Category = "Player Slot", meta = (BindWidget))
	UTextBlock* ReadyText;

	// Ready button
	UPROPERTY(BlueprintReadWrite, Category = "Player Slot", meta = (BindWidget))
	UButtonBase* ReadyButton;

	// Color for the player slot
	UPROPERTY(BlueprintReadWrite, Category = "Player Slot", meta = (BindWidget))
	UBorder* PlayerSlotColor;

	// Player Index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 PlayerIndex;

};
