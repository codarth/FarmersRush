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

	virtual void NativeConstruct() override;

public:


	UPROPERTY(BlueprintReadWrite, Category = "Interaction", meta = (BindWidget))
	UBorder* InteractionBorder;

	UPROPERTY(BLueprintReadWrite, Category = "Interaction", meta = (BindWidget))
	UTextBlock* InteractionText;

};
