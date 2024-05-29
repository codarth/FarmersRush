// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact_Interface.generated.h"

class APlayerFarmerCharacter;

UENUM()
enum class EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	NonPlayerCharacter UMETA(DisplayName = "NonPlayerCharacter"),
	FarmPlot UMETA(DisplayName = "FarmPlot"),
	Tool UMETA(DisplayName = "Tool"),
	Container UMETA(DisplayName = "Container")
};

USTRUCT()
struct FInteractableData
{
	GENERATED_BODY()

	FInteractableData() : InteractableType(EInteractableType::Pickup), Name(FText::GetEmpty()), Action(FText::GetEmpty()), Quantity(1), InteractionDuration(0.0f)
	{
	};

	// Type of interactable
	EInteractableType InteractableType;

	// A clear name of the interactable
	UPROPERTY(EditInstanceOnly)
	FText Name;

	// The action that will be displayed to the player
	UPROPERTY(EditInstanceOnly)
	FText Action;

	// Quantity of the item. May not be relevant for all interactables
	UPROPERTY(EditInstanceOnly)
	int8 Quantity;

	// Duration of the interaction if they need to hold a button or something
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;
};

// This class does not need to be modified.
UINTERFACE()
class UInteract_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class LOCALMULTIPLAYER_API IInteract_Interface
{
	GENERATED_BODY()

public:
	// virtual void Interact();

	// Reveals the interaction widget
	virtual void ShowInteractionWidget();

	// Hides the interaction widget
	virtual void HideInteractionWidget();

	// Called when the player begins to focus on the interactable
	virtual void BeginFocus();
	// Called when the player stops focusing on the interactable
	virtual void EndFocus();
	
	// Character based interactions
	// Called when the player begins to interact with the interactable
	virtual void BeginInteract();
	// Called when the player stops interacting with the interactable
	virtual void EndInteract();
	// The actual call for interaction
	virtual void Interact(APlayerFarmerCharacter* PlayerCharacter);

	// Data for the interactable
	FInteractableData InteractableData;
};
