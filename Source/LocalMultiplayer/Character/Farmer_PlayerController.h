// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Farmer_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 *
 */
UCLASS()
class LOCALMULTIPLAYER_API AFarmer_PlayerController : public APlayerController
{
	GENERATED_BODY()

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

public:

	// Bind Functions to Inputs
	virtual void SetupInputComponent() override;

protected:

	// Called for Move Forward input
	void Move(const FInputActionValue& Value);
};
