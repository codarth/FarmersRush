// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LocalMultiplayer/Core/Interfaces/Countdown_Interface.h"
#include "PlayerFarmerCharacter.generated.h"

class AFarmersRush_GameMode;
class UPlayerInfo_UI;

UCLASS()
class LOCALMULTIPLAYER_API APlayerFarmerCharacter : public ACharacter, public ICountdown_Interface
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayerFarmerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	AFarmersRush_GameMode* GameModeRef = nullptr;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AddCamera();

	/** End Countdown Interface */
	virtual void BeginQuitCountdown(bool bToMainMenu) override;
	virtual void UpdateQuitTimer() override;
	virtual void StopQuitCountdown() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Info")
	int32 PlayerIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Info")
	UMaterialInstance* PlayerDefaultColor;

	UPROPERTY(VisibleAnywhere, BlueprintreadWrite, Category = "Player Info")
	bool bIsPlayerReady = false;

public:

	/** Interaction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionCheckFrequency = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionCheckDistance = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionCheckHalfHeight = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionCheckRadius = 50.f;

private:

	FTimerHandle InteractionCheckTimerHandle;

	void CheckForInteractable();

	/** End Interaction */
};
