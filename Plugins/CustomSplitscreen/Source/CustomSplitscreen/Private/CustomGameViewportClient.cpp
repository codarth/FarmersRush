// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameViewportClient.h"

UCustomGameViewportClient::UCustomGameViewportClient()
	:Super(FObjectInitializer::Get())
{
	// Resize splitscreen to fit our custom config
	SplitscreenInfo.SetNum(ECustomSplitscreenType::SplitTypeCount, false);

	// Fill the custom config
	// TwoPlayer
	SplitscreenInfo[ECustomSplitscreenType::TwoPlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.50f, 1.00f, 0.00f, 0.00f)); //1
	SplitscreenInfo[ECustomSplitscreenType::TwoPlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.50f, 1.00f, 0.50f, 0.00f)); //2
	// ThreePlayer
	SplitscreenInfo[ECustomSplitscreenType::ThreePlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.33f, 1.00f, 0.00f, 0.00f)); //1
	SplitscreenInfo[ECustomSplitscreenType::ThreePlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.33f, 1.00f, 0.33f, 0.00f)); //2
	SplitscreenInfo[ECustomSplitscreenType::ThreePlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.33f, 1.00f, 0.66f, 0.00f)); //3
	// FourPlayer
	SplitscreenInfo[ECustomSplitscreenType::FourPlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.50f, 0.50f, 0.00f, 0.00f)); //1
	SplitscreenInfo[ECustomSplitscreenType::FourPlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.50f, 0.50f, 0.50f, 0.00f)); //2
	SplitscreenInfo[ECustomSplitscreenType::FourPlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.50f, 0.50f, 0.00f, 0.50f)); //3
	SplitscreenInfo[ECustomSplitscreenType::FourPlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.50f, 0.50f, 0.50f, 0.50f)); //4
	
}

void UCustomGameViewportClient::UpdateActiveSplitscreenType()
{
	// ECustomSplitscreenType::Type SplitscreenType = ECustomSplitscreenType::None;
	// const int32 NumPlayers = GEngine->GetNumGamePlayers(GetWorld());

	

	UE_LOG(LogTemp, Warning, TEXT("NumPlayers: %d"), ActivePlayers);

	switch (ActivePlayers)
	{
	case 2:
		ActiveSplitscreenType = static_cast<ESplitScreenType::Type>(ECustomSplitscreenType::TwoPlayer);
		break;
	case 3:
		ActiveSplitscreenType = static_cast<ESplitScreenType::Type>(ECustomSplitscreenType::ThreePlayer);
		break;
	case 4:
		ActiveSplitscreenType = static_cast<ESplitScreenType::Type>(ECustomSplitscreenType::FourPlayer);
		break;
	default:
		Super::UpdateActiveSplitscreenType();
	}
	
	// if (NumPlayers == 3)
	// {
	// 	// If Player count is equal 3, select custom SplitScreenType
	// 	ActiveSplitscreenType = static_cast<ESplitScreenType::Type>(ECustomSplitscreenType::ThreePlayer);
	// }
	// else
	// {
	// 	Super::UpdateActiveSplitscreenType();
	// }
}
