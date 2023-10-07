// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputReciever_FR.generated.h"

class UCharacterCustomizeWidget;
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

	/** Menu Left Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuLeftAction;

	/** Menu Right Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuRightAction;

protected:

	// To add mapping context
	virtual void BeginPlay() override;
	
	/** APawn interface */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for start input */
	void Start(const FInputActionValue& Value);

	/** Called for Menu Left input */
	void MenuLeft(const FInputActionValue& Value);

	/** Called for Menu Right input */
	void MenuRight(const FInputActionValue& Value);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	int32 PlayerIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
	UCharacterCustomizeWidget* CharacterCustomizeWidget;
};
