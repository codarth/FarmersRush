// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocalMultiplayer/Core/Interfaces/Interact_Interface.h"
#include "BaseInteractable.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	UStaticMeshComponent* Interactable_Mesh;

	// Material of player interacting
	UPROPERTY()
	UMaterialInstance* InteractingColor;

	// Interaction Widget 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Interactable")
	UWidgetComponent* InteractionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	FText InteractText;

	UFUNCTION(BlueprintPure, Category = "Interactable")
	FText GetInteractText() const { return InteractText; }

	virtual void Interact() override;

	virtual void ShowInteractionWidget() override;

	virtual void HideInteractionWidget() override;

};
