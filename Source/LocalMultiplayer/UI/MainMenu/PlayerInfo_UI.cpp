// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfo_UI.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "LocalMultiplayer/Character/MainMenu/PlayerInputDummy.h"

void UPlayerInfo_UI::NativeConstruct()
{
	Join_NameText->SetText(FText::FromString("Press Start To Join"));
	PlayerColor_Border->SetVisibility(ESlateVisibility::Hidden);
	Ready_Icon->SetVisibility(ESlateVisibility::Hidden);
	Ready_Text->SetVisibility(ESlateVisibility::Hidden);
}
