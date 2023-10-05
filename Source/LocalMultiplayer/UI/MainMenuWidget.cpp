// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Border.h"

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
}

void UMainMenuWidget::Back()
{
	HideBackButtonBorder();
	ShowMainButtonsBorder();
}

void UMainMenuWidget::Quit()
{
	
}
