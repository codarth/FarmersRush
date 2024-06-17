// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class UHorizontalBox;
class UTextBlock;

/**
 *
 */
UCLASS()
class LOCALMULTIPLAYER_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void HideInteractionWidget() const;
	void ShowInteractionWidget() const;

	void SetInteractionText(const FText& Text) const;

protected:
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* InteractionBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractionText;

};
