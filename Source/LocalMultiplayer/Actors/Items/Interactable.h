// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocalMultiplayer/Core/Interfaces/Interact_Interface.h"
#include "Interactable.generated.h"

class UBoxComponent;

UCLASS()
class LOCALMULTIPLAYER_API AInteractable : public AActor, public IInteract_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	UStaticMeshComponent* Interactable_Mesh;

	virtual void Interact() override;
};
