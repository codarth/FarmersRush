// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerFarmerCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class LOCALMULTIPLAYER_API APlayerFarmerCharacter : public ACharacter
{
	GENERATED_BODY()

	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	// Move Forward Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

public:
	// Sets default values for this character's properties
	APlayerFarmerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called for Move Forward input
	void Move(const FInputActionValue& Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
