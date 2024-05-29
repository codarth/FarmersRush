// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class UBorder;
class UTextBlock;

/**
 *
 */
UCLASS()
class LOCALMULTIPLAYER_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

	// virtual void NativeConstruct() override;

public:

	FORCEINLINE UBorder* GetInteractionBorder() const { return InteractionBorder; }
	FORCEINLINE UTextBlock* GetInteractionText() const { return InteractionText; }

private:
	
	UPROPERTY(meta = (BindWidget))
	UBorder* InteractionBorder;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractionText;

};
