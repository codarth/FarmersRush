// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "LocalMultiplayer/UI/Utilities/ButtonBase.h"
#include "Components/Border.h"
#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup button events
	PlayButton->Button->OnClicked.AddDynamic(this, &UMainMenuWidget::Play);
	BackButton->Button->OnClicked.AddDynamic(this, &UMainMenuWidget::Back);
	QuitButton->Button->OnClicked.AddDynamic(this, &UMainMenuWidget::Quit);
	
}

void UMainMenuWidget::HideMainButtonsBorder()
{
	MainButtonsBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuWidget::ShowMainButtonsBorder()
{
	MainButtonsBorder->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::ShowBackButtonBorder()
{
	BackButtonBorder->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::HideBackButtonBorder()
{
	BackButtonBorder->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuWidget::Play()
{
	HideMainButtonsBorder();
	ShowBackButtonBorder();

	bIsInPlayerCustomization = true;
}

void UMainMenuWidget::Back()
{
	HideBackButtonBorder();
	ShowMainButtonsBorder();

	bIsInPlayerCustomization = false;
}

void UMainMenuWidget::Quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
