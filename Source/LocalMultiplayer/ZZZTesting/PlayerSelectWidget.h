// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSelectWidget.generated.h"

class UCharacterCustomizeWidget;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UPlayerSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// Adds a new character customize widget to the main panel
	UFUNCTION(BlueprintCallable, Category = "Player Info")
	UCharacterCustomizeWidget* AddCharacterCustomizeWidget(int32 PlayerIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	TSubclassOf<UCharacterCustomizeWidget> CharacterCustomizeWidgetClass;

	UPROPERTY()
	UCharacterCustomizeWidget* CharacterCustomizeWidget;
	
	UPROPERTY(BlueprintReadWrite, Category = "Player Info", meta = (BindWidget))
	UUniformGridPanel* MainPanel;

};