// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelectWidget.h"

#include "CharacterCustomizeWidget.h"
#include "Components/UniformGridPanel.h"

UCharacterCustomizeWidget* UPlayerSelectWidget::AddCharacterCustomizeWidget(int32 PlayerIndex)
{
	CharacterCustomizeWidget = CreateWidget<UCharacterCustomizeWidget>(GetWorld(), CharacterCustomizeWidgetClass);
	CharacterCustomizeWidget->PlayerIndex = PlayerIndex;
	CharacterCustomizeWidget->AddToViewport();
	MainPanel->AddChildToUniformGrid(CharacterCustomizeWidget, 0, PlayerIndex);
	return CharacterCustomizeWidget;	
}
