// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameStatus.h"
#include "Components/TextBlock.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"

void UPlayerGameStatus::NativeConstruct()
{
	Super::NativeConstruct();

	// PlayerCurrentMoneyText->SetText(FText::FromString(FString::FromInt(0)));
}

void UPlayerGameStatus::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPlayerGameStatus::UpdatePlayerMoney()
{
	PlayerCharacter = Cast<APlayerFarmerCharacter>(GetOwningPlayerPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is nullptr for %s"), *GetName());
	}
	PlayerCurrentMoneyText->SetText(FText::FromString(FString::FromInt(PlayerCharacter->GetPlayerMoney())));
}
