// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "PlayerGameStatus.h"

APlayerHUD::APlayerHUD()
{
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerGameStatusClass)
	{
		PlayerGameStatusWidget = CreateWidget<UPlayerGameStatus>(GetWorld(), PlayerGameStatusClass);
		PlayerGameStatusWidget->AddToViewport();
		PlayerGameStatusWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::DisplayPlayerStatus()
{
	if (PlayerGameStatusWidget)
	{
		PlayerGameStatusWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerHUD::HidePlayerStatus()
{
	if (PlayerGameStatusWidget)
	{
		PlayerGameStatusWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::UpdatePlayerMoney()
{
	if (PlayerGameStatusWidget)
	{
		PlayerGameStatusWidget->UpdatePlayerMoney();
	}
}
