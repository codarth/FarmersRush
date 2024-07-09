// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMoneyWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "LocalMultiplayer/LocalMultiplayer.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"

void UPlayerMoneyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerMoneyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APlayerFarmerCharacter>(GetOwningPlayerPawn());
}

void UPlayerMoneyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!PlayerCharacter.IsValid())
	{
		return;
	}

	UpdatePlayerMoney();
	
}

void UPlayerMoneyWidget::SetOwner(APlayerFarmerCharacter* Player)
{
	if (!Player)
	{
		LOG_ERROR("Player is nullptr for %s", *GetName());
		return;
	}
	
	PlayerCharacter = Player;
}

void UPlayerMoneyWidget::UpdatePlayerMoney() const
{
	PlayerCurrentMoneyText->SetText(FText::Format(FText::FromString("${0}"),PlayerCharacter->GetPlayerMoney()));
}

void UPlayerMoneyWidget::ShowMoneyWidget() const
{
	MoneyBox->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerMoneyWidget::HideMoneyWidget() const
{
	MoneyBox->SetVisibility(ESlateVisibility::Collapsed);
}
