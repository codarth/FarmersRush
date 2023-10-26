// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenu_GameMode.generated.h"

class UMainMenu_UI;
class APlayerInputDummy;
class AMainMenuCamera;
class APlayerFarmerCharacter;
class APlayerCustomizePawn;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API AMainMenu_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	UFUNCTION()
	APlayerInputDummy* SpawnAndPossessDummy(const AActor* PlayerStart, const int32 Index);

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY()
	AMainMenuCamera* CameraRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
	TSubclassOf<APlayerInputDummy> DummyToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
	TSubclassOf<APlayerFarmerCharacter> CharacterToSpawn;

	UPROPERTY(BlueprintReadOnly, Category = "Character Info")
	TArray<APlayerFarmerCharacter*> CurrentCharacters;

	UPROPERTY(BlueprintReadOnly, Category = "Character Info")
	TArray<APlayerInputDummy*> CurrentDummies;

	UFUNCTION()
	void SpawnCharacterAtDummy(const APlayerInputDummy* Dummy, const int32 PlayerIndex);

	UFUNCTION()
	void DeactivatePlayer(const int32 PlayerIndex);

private:
	void BeginCountdown();

	void UpdateTimer();

	void StopCountdown();

	void StartGame();

	FTimerHandle CountdownTimerHandle;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
	TSubclassOf<UMainMenu_UI> MainMenuWidgetClass;
	
	UPROPERTY()
	UMainMenu_UI* MainMenuWidget;
};
