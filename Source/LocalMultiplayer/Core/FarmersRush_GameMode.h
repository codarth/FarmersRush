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

	AFarmersRush_GameMode();

	void SetupForDummies();

	UFUNCTION()
	APlayerInputDummy* SpawnAndPossessDummy(const AActor* PlayerStart, const int32 Index);

	virtual void BeginPlay() override;

	//virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;

public:

	virtual void Tick(float DeltaSeconds) override;
	void SetupPlayerInfoUI(int32 Index, const APlayerController* PC);

	UPROPERTY()
	AMainMenuCamera* CameraRef = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
	TSubclassOf<APlayerInputDummy> DummyToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
	TSubclassOf<APlayerFarmerCharacter> CharacterToSpawn;

	UPROPERTY(BlueprintReadOnly, Category = "Character Info")
	TArray<APlayerFarmerCharacter*> CurrentCharacters;

	UPROPERTY(BlueprintReadOnly, Category = "Character Info")
	TArray<APlayerInputDummy*> CurrentDummies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
	TSubclassOf<APlayerController> MainMenuPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Info")
	TSubclassOf<APlayerController> FarmerPlayerController;

	UFUNCTION()
	void SpawnCharacterAtDummy(APlayerInputDummy* Dummy, const int32 PlayerIndex);

	UFUNCTION()
	void DeactivatePlayer(const int32 PlayerIndex);

	/** Begin exit countdown */
	void BeginQuitCountdown(bool bToMainMenu);
	void UpdateQuitTimer();
	void StopQuitCountdown();

	/** Begin start countdown */
	void BeginStartCountdown();
	void UpdateStartTimer();
	void StopStartCountdown();

private:

	void StartGame();

	void TransitionToGame();
	void ActivatePlayerUI(int32 Index, const APlayerController* PC, UPlayerInfo_UI* UI);

	void FadeCamera(bool bFadeIn = false);
	void SetupPlayerCamera();
	void CleanupDummies();

	void LevelLoading();
	void LoadLevel();
	void UnloadLevel();
	int32 CurrentLevelIndex;

	void LoadMainMenu();
	void UnloadMainMenu();
	void BackToMainMenu();

	void AdjustCharacterLocation();

	FTimerHandle StartCountdownTimerHandle;
	FTimerHandle QuitCountdownTimerHandle;
	FTimerHandle LoadLevelTimer;
	FTimerHandle UnloadLevelTimer;
	FTimerHandle DummyCleanupTimer;

	bool bExitToMainMenu;

public:

	bool bStartingGame = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
	TSubclassOf<UMainMenu_UI> MainMenuWidgetClass;

	UPROPERTY()
	UMainMenu_UI* MainMenuWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerInfo")
	TArray<UMaterialInstance*> PlayerColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelInfo")
	FName MainMenuLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelInfo")
	TArray<FName> MainLevelNames;

};
