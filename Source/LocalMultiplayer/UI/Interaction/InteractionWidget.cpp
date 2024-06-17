// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UInteractionWidget::HideInteractionWidget() const
{
	InteractionBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UInteractionWidget::ShowInteractionWidget() const
{
	InteractionBox->SetVisibility(ESlateVisibility::Visible);
}

void UInteractionWidget::SetInteractionText(const FText& Text) const
{
	InteractionText->SetText(Text);
}
