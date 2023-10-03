// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "LocalMultiplayer/Character/GameCamera.h"
#include "GameMode_FR.generated.h"

class UPlayerSelectWidget;
class APlayer_FR;
class AGameCamera;

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API AGameMode_FR : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void SpawnPlayerAtInputReceiver_Implementation(int32 CurrentPlayerIndex, AInputReciever_FR* InputReceiver, int32 CharacterChoice) override;
	virtual void DisplayCharacterCustomize_Implementation(int32 CurrentPlayerIndex) override;
	virtual void StartGame_Implementation() override;
	virtual bool GetIsInGame_Implementation() override;
	
	AInputReciever_FR* SpawnAndPossessInputReceiver(AActor* PlayerStart, int32 Index);

	void RemoveUnusedCameras();
	void GameStarted();
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Player Info")
	TSubclassOf<AInputReciever_FR> InputReceiverToSpawn;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
	TArray<AInputReciever_FR*> InputReceivers;

	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
	TArray<APlayerController*> PlayerControllers;

	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
    TArray<APlayer_FR*> CurrentPlayers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Info")
	TSubclassOf<APlayer_FR> PlayerToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Info")
	int32 MinPlayersToStart = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	TSubclassOf<UPlayerSelectWidget> PlayerSelectWidgetClass;

	UPROPERTY()
	UPlayerSelectWidget* PlayerSelectWidget;

	UPROPERTY()
	AGameCamera* CameraRef;

	UPROPERTY()
	bool bIsInGame = false;
};
