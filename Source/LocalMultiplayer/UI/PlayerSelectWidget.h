// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSelectWidget.generated.h"

class SUniformGridPanel;
class UCharacterSelectWidget;
/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UPlayerSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Select Widget")
	UUserWidget* AddCharacterSelectWidget(int32 CurrentPlayerIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UCharacterSelectWidget> CharacterSelectWidgetClass;

	UPROPERTY()
	UCharacterSelectWidget* CharacterSelectWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	SUniformGridPanel* MainPanel;

};
