// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"

#include "Components/BoxComponent.h"


// Sets default values
ABaseInteractable::ABaseInteractable()
{
	// Default Root Component
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	// set up the box component
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	OverlapBox->SetupAttachment(RootComponent);

	// set up the mesh component
	Interactable_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactable_Mesh"));
	Interactable_Mesh->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseInteractable::Interact()
{
	// print to screen when interacted with
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *FString::Printf(TEXT("Interacted with %s"), *GetName()));
}

