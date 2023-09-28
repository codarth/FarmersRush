// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCustomizeWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UCharacterCustomizeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 PlayerIndex;
};
