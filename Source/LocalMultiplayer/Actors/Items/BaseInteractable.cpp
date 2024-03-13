// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "LocalMultiplayer/UI/InteractionWidget.h"


// Sets default values
ABaseInteractable::ABaseInteractable()
{
	// Default Root Component
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	// set up the box component
	//OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	//OverlapBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	//OverlapBox->SetupAttachment(RootComponent);

	// set up the mesh component
	Interactable_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactable_Mesh"));
	Interactable_Mesh->SetupAttachment(SceneComponent);

	//InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	//InteractionWidget->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
	if (!IsValid(InteractionWidget))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interaction Widget Not Found"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interaction Widget Found"));


	}
}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseInteractable::Interact()
{
	// print to screen when interacted with
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *FString::Printf(TEXT("Interacted with %s"), *GetName()));

	// if the interactable has a widget, display it
	//if (InteractionWidget)
	//{
	//	// create the widget
	//	//InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
	//if (InteractionWidget)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interaction Widget Found"));
	//	//InteractionWidget->InteractionBorder->SetVisibility(ESlateVisibility::Visible);
	//	//InteractionWidget->InteractionBorder->SetBrushMaterial(InteractingColor);

	//	// Add widget to item

	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Interaction Widget"));
	//}
	//}
}

void ABaseInteractable::ShowInteractionWidget()
{
}

void ABaseInteractable::HideInteractionWidget()
{
}

