// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_UI.h"

#include "PlayerInfo_UI.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void UMainMenu_UI::NativeConstruct()
{
	CountdownBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu_UI::UpdateCountdown()
{
	CountdownText->SetText(FText::FromString(FString::FromInt(CurrentCountdownTime)));
	if (!bInitialUpdate)
	{
		CurrentCountdownTime -= 1;
	}
	bInitialUpdate = false;
}
