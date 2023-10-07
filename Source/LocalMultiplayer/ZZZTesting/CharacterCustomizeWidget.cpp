// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCustomizeWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

void UCharacterCustomizeWidget::NativeConstruct()
{
	PlayerText->SetText(FText::FromString("Player " + FString::FromInt(CharacterColorChoice + 1)));
	PlayerColorBorder->SetBrushColor(PlayerColors[CharacterColorChoice]);
}

void UCharacterCustomizeWidget::SwitchCharacterColor(int32 Direction)
{
	CharacterColorChoice += Direction;
	
	CharacterColorChoice = FMath::Clamp(CharacterColorChoice, 0, PlayerColors.Num() - 1);

	PlayerColorBorder->SetBrushColor(PlayerColors[CharacterColorChoice]);
}
