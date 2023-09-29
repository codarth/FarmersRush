// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCustomizeWidget.generated.h"

class UBorder;
class UTextBlock;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UCharacterCustomizeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Player Info")
	void SwitchCharacterColor(int32 Direction);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 CharacterColorChoice;

	UPROPERTY(BlueprintReadOnly, Category = "Player Info", meta = (BindWidget))
	UTextBlock* PlayerText;

	UPROPERTY(BlueprintReadOnly, Category = "Player Info", meta = (BindWidget))
	UBorder* PlayerColorBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	TArray<FLinearColor> PlayerColors;
};
