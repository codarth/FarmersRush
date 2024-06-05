// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerGameStatus.generated.h"

class UTextBlock;
class UOverlay;
class APlayerFarmerCharacter;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UPlayerGameStatus : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Player Game Status | Player Reference")
	APlayerFarmerCharacter* PlayerCharacter;

	void UpdatePlayerMoney();

protected:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Player Game Status")
	UOverlay* PlayerStatusOverlay;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Player Game Status")
	UTextBlock* PlayerCurrentMoneyText;
};
