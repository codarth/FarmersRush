// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Engine/ViewportSplitScreen.h"
#include "CustomGameViewportClient.generated.h"

UENUM(BlueprintType)
namespace ECustomSplitscreenType
{
	enum Type
	{
		// 0 value required by UE
		None,
		// Custom splitscreen, next value after last built-in splitscreen type
		TwoPlayer = ESplitScreenType::SplitTypeCount,
		ThreePlayer = ESplitScreenType::SplitTypeCount + 1,
		FourPlayer = ESplitScreenType::SplitTypeCount + 2,
		SplitTypeCount
	};
}

/**
 * 
 */
UCLASS()
class CUSTOMSPLITSCREEN_API UCustomGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

	UCustomGameViewportClient();

	virtual void UpdateActiveSplitscreenType() override;

public:

	UPROPERTY()
	int32 ActivePlayers = 0;
};
