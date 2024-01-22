// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_UI.h"

#include "PlayerInfo_UI.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void UMainMenu_UI::NativeConstruct()
{
	CountdownBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu_UI::UpdateCountdown(bool bIsGameStart){
	// Is the game started
	if (bIsGameStart)
	{
		// Are we trying to go back to the main menu
		if (bQuitToMainMenu) // Quiting to main menu
		{
			CountdownText->SetText(FText::FromString("Quitting to main menu in " + FString::FromInt(CurrentCountdownTime)));
			CountdownText->SetColorAndOpacity(FLinearColor(1.0f, 0.5f, 0.0f, 0.8f));
		}
		else // Starting the game
		{
			CountdownText->SetText(FText::FromString("Begin in " + FString::FromInt(CurrentCountdownTime)));
			CountdownText->SetColorAndOpacity(FLinearColor(1.0f, 0.04f, 0.0f, 0.8f));
		}
	}
	else // Quiting the game
	{
		CountdownText->SetText(FText::FromString("Quitting Game in " + FString::FromInt(CurrentCountdownTime)));
		CountdownText->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 0.8f));
	}

	// Are we just starting the countdown, if not, decrement the time
	if (!bInitialUpdate) 
	{
		CurrentCountdownTime -= 1;
	}
	bInitialUpdate = false;
}

void UMainMenu_UI::ResetCountdown()
{
	CurrentCountdownTime = CountdownTime;
	bInitialUpdate = true;
}

