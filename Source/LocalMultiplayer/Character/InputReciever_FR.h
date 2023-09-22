// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputReciever_FR.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class LOCALMULTIPLAYER_API AInputReciever_FR : public APawn
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;
	
	/** Start Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StartAction;

protected:

	// To add mapping context
	virtual void BeginPlay() override;
	
	/** APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for start input */
	void Start(const FInputActionValue& Value);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 PlayerIndex;
};
