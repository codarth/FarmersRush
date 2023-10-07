// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonBase.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UButtonBase : public UUserWidget
{
	GENERATED_BODY()

public:

	// Button
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	UButton* Button;

	// Button text
	UPROPERTY(BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	UTextBlock* ButtonText;
	
};
