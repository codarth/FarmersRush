// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UHorizontalBox;
class UButtonBase;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	/** Buttons */
	
	// Hide main buttons border
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void HideMainButtonsBorder();

	// Show main buttons border
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void ShowMainButtonsBorder();

	// Show back button border
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void ShowBackButtonBorder();

	// Hide back button border
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void HideBackButtonBorder();
	
	// Play button pressed
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void Play();

	// Back button pressed
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void Back();

	// Quit button pressed
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void Quit();
	
	// Play button
	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
	UButtonBase* PlayButton;
	
	// Back button
	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
	UButtonBase* BackButton;
	
	// Quit button
	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
	UButtonBase* QuitButton;
	
	// Main menu buttons border
	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
	class UBorder* MainButtonsBorder;

	// Back button border
	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
	class UBorder* BackButtonBorder;

	/** Character Customization */

	// Player Slot Box
	UPROPERTY(BlueprintReadWrite, Category = "Character Customization", meta = (BindWidget))
	UHorizontalBox* PlayerSlotBox;
};
