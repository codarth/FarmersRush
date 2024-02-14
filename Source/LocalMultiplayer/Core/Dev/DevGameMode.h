// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DevGameMode.generated.h"


class APlayerFarmerCharacter;

/**
 *
 */
UCLASS()
class LOCALMULTIPLAYER_API ADevGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ADevGameMode();

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "Character")
	TSubclassOf<APlayerFarmerCharacter> CharacterToSpawn;

};
