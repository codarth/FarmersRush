// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_UI.h"

#include "Components/TextBlock.h"

void UMainMenu_UI::NativeConstruct()
{
	Super::NativeConstruct();
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
