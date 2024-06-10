// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMoneyWidget.h"
#include "Components/TextBlock.h"
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
		UE_LOG(LogTemp, Error, TEXT("Player is nullptr for %s"), *GetName());
		return;
	}
	
	PlayerCharacter = Player;
}

void UPlayerMoneyWidget::UpdatePlayerMoney()
{
	PlayerCurrentMoneyText->SetText(FText::Format(FText::FromString("${0}"),PlayerCharacter->GetPlayerMoney()));
}
