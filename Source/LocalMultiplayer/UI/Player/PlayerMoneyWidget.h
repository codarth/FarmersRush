// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMoneyWidget.generated.h"

class APlayerFarmerCharacter;
class UTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class LOCALMULTIPLAYER_API UPlayerMoneyWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	
	void SetOwner(APlayerFarmerCharacter* Player);
	void UpdatePlayerMoney();

protected:
	TWeakObjectPtr<APlayerFarmerCharacter> PlayerCharacter;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Player Game Status")
	UTextBlock* PlayerCurrentMoneyText;

};
