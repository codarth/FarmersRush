// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FarmersRush_GameMode.generated.h"


class UPlayerInfo_UI;
class UMainMenu_UI;
class APlayerFarmerCharacter;
class APlayerInputDummy;
class AMainMenuCamera;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API AFarmersRush_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	UFUNCTION()
	APlayerInputDummy* SpawnAndPossessDummy(const AActor* PlayerStart, const int32 Index);

	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaSeconds) override;
	void SetupPlayerInfoUI(int32 Index, const APlayerController* PC);

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

	void TransitionToGame();
	void ActivatePlayerUI(int32 Index, const APlayerController* PC, UPlayerInfo_UI* UI);

	FTimerHandle CountdownTimerHandle;

	bool bStartingGame = false;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
	TSubclassOf<UMainMenu_UI> MainMenuWidgetClass;
	
	UPROPERTY()
	UMainMenu_UI* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	TArray<UMaterialInstance*> PlayerColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelInfo")
	FName MainLevelName;

};
