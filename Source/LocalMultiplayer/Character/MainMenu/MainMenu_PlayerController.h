// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenu_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 *
 */
UCLASS()
class LOCALMULTIPLAYER_API AMainMenu_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Character Reference
	UPROPERTY(Transient)
	class APlayerFarmerCharacter* CharacterRef;

	/** Input */

private:
	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	// Move Forward Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	// Deactivate Player Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* DeactivatePlayerAction;

public:

	// Bind Functions to Inputs
	virtual void SetupInputComponent() override;

protected:

	// Called for Move Forward input
	void Move(const FInputActionValue& Value);

	// Called for Deactivate Player input
	void DeactivatePlayer(const FInputActionValue& Value);

};
