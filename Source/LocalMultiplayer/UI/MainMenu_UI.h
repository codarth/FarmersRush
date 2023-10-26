// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu_UI.generated.h"

class UBorder;
class UTextBlock;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UMainMenu_UI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
public:

	UPROPERTY(BlueprintReadWrite, Category = "Counddown", meta = (BindWidget))
	UBorder* CountdownBorder;
	
	UPROPERTY(BlueprintReadWrite, Category = "Counddown", meta = (BindWidget))
	UTextBlock* CountdownText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Counddown")
	int32 CountdownTime = 3;

	UPROPERTY(BlueprintReadOnly, Category = "Counddown")
	int32 CurrentCountdownTime;

	UFUNCTION()
	void UpdateCountdown();
};
