// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu_GameMode.generated.h"

class AMainMenuCamera;
class APlayerFarmerCharacter;
class APlayerCustomizePawn;
class UInputMappingContext;
class UInputAction;
class UMainMenuWidget;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API AMainMenu_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	UFUNCTION()
	APlayerFarmerCharacter* SpawnAndPossessCharacter(const AActor* PlayerStart, const int32 Index);
	
	virtual void BeginPlay() override;

public:
	
	UPROPERTY()
	AMainMenuCamera* CameraRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
	TSubclassOf<APlayerFarmerCharacter> CharacterToSpawn;
};
