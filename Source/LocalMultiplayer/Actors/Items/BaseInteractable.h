// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocalMultiplayer/Core/Interfaces/Interact_Interface.h"
#include "BaseInteractable.generated.h"

class APlayerFarmerCharacter;
class UItemBase;
class UBoxComponent;
class UInteractionWidget;
class UWidgetComponent;

UCLASS()
class LOCALMULTIPLAYER_API ABaseInteractable : public AActor, public IInteract_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseInteractable();

	virtual void BeginFocus() override;
	virtual void EndFocus() override;

	// Initialize the interactable
	void InitializeInteractable(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Data for interaction
	UPROPERTY(VisibleAnywhere, Category = "Interactable")
	FInteractableData InstanceInteractableData;

	// // Interaction widget
	// UPROPERTY(EditInstanceOnly, Category = "Interactable")
	// UInteractionWidget* InteractionWidget;

	// Item reference
	UPROPERTY(VisibleAnywhere, Category = "Interactable")
	UItemBase* ItemReference;

	// Item quantity
	UPROPERTY(EditInstanceOnly, Category = "Interactable")
	int32 ItemQuantity;

	// Item row handle
	UPROPERTY(EditInstanceOnly, Category = "Interactable")
	FDataTableRowHandle ItemRowHandle;

	FORCEINLINE UItemBase* GetItemData() const { return ItemReference; }

	// Implement Interaction
	virtual void Interact(APlayerFarmerCharacter* PlayerCharacter) override;

	// Update the interactable data
	void UpdateInteractableData();

	// Perform the interaction
	void TakeInteractable(APlayerFarmerCharacter* Taker);

public:

	FORCEINLINE FDataTableRowHandle GetItemRowHandle() const { return ItemRowHandle; }
	void SetItemRowHandle(const FDataTableRowHandle& InRowHandle) { ItemRowHandle = InRowHandle; }
	
	// Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	UStaticMeshComponent* Interactable_Mesh;

	/** Interaction Widget */
	
	// Interaction widget component
	UPROPERTY(VisibleAnywhere, Category = "Interactable")
	UWidgetComponent* InteractionWidgetComponent;

	// Hide the interaction widget
	virtual void HideInteractionWidget() override;
	// Show the interaction widget
	virtual void ShowInteractionWidget() override;

protected:
#if WITH_EDITOR
	// When changes are made in the editor
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
