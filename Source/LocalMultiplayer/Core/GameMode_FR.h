// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_FR.generated.h"

class APlayer_FR;
/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API AGameMode_FR : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void SpawnPlayerAtInputReceiver_Implementation(int32 CurrentPlayerIndex, AInputReciever_FR* InputReceiver) override;

	AInputReciever_FR* SpawnInputReceiver(AActor* PlayerStart, int32 Index);

public:

	UPROPERTY(EditDefaultsOnly, Category = "Player Info")
	TSubclassOf<AInputReciever_FR> InputReceiverToSpawn;
	
	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
	TArray<AInputReciever_FR*> InputReceivers;

	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
	TArray<APlayerController*> PlayerControllers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Info")
	TSubclassOf<APlayer_FR> PlayerToSpawn;
};
