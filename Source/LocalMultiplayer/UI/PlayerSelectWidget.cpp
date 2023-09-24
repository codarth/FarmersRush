// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelectWidget.h"
#include "CharacterSelectWidget.h"
#include "Widgets/Layout/SUniformGridPanel.h"

UUserWidget* UPlayerSelectWidget::AddCharacterSelectWidget(int32 CurrentPlayerIndex)
{
	CharacterSelectWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), CharacterSelectWidgetClass);
	if (CharacterSelectWidget)
	{
		CharacterSelectWidget->AddToViewport();
	}

	auto GridSlot = MainPanel->AddSlot(CurrentPlayerIndex, 0);
	GridSlot.AttachWidget(CharacterSelectWidget->TakeWidget());
	
	return CharacterSelectWidget;
}
