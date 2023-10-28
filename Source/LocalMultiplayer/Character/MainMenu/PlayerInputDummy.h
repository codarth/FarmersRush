// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerInputDummy.generated.h"

class UPlayerInfo_UI;
class APlayerFarmerCharacter;
struct FInputActionValue;

UCLASS()
class LOCALMULTIPLAYER_API APlayerInputDummy : public APawn
{
	GENERATED_BODY()

	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;

	// Activate player input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ActivatePlayerAction;
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called for Activate Player input
	void ActivatePlayer(const FInputActionValue& Value);
	
public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Info")
	int32 PlayerIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	UMaterialInstance* PlayerDefaultColor;
};
