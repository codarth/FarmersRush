// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"

#include "EditorMetadataOverrides.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "LocalMultiplayer/UI/InteractionWidget.h"


// Sets default values
ABaseInteractable::ABaseInteractable()
{
	// Default Root Component
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	// Setup the mesh component
	Interactable_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactable_Mesh"));
	Interactable_Mesh->SetupAttachment(SceneComponent);

	// Setup the widget component
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(FName("Interaction Widget"));
	if (InteractionWidget)
	{
		InteractionWidget->SetupAttachment(RootComponent);
		InteractionWidget->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
		InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Interaction Widget Found"));
	}
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();

	// InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
	if (InteractionWidget)
	{
		// 	UE_LOG(LogTemp, Warning, TEXT("No Interaction Widget Found"));
		// }
		// else
		// {
		// 	InteractionWidget->AddToViewport();
		// 	InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
		// }
		// InteractionWidget->InitWidget();
		// const auto Widget = Cast<UInteractionWidget>(InteractionWidget->GetUserWidgetObject());
		// if (!Widget)
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("%s: Failed to Cast to UInteractionWidget"), *GetOwner()->GetName());
		// 	return;
		// }
		// Widget->GetInteractionText()->TextDelegate.BindUFunction(this, "GetInteractText");
		InteractionWidget->SetWidgetClass(InteractionWidgetClass);
		InteractionWidget->SetVisibility(false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction Widget Not Found"));
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

	// If the interactable has a widget, display it
	if (InteractionWidget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interaction Widget Found"));
		InteractionWidget->SetVisibility(true);
		// InteractionWidget->InteractionBorder->SetVisibility(ESlateVisibility::Visible);
		// // InteractionWidget->InteractionBorder->SetBrushFromMaterial(InteractingColor);
		// InteractionWidget->InteractionText->SetVisibility(ESlateVisibility::Visible);
		// InteractionWidget->InteractionText->SetText(FText::FromString("Interact"));
	}
}

void ABaseInteractable::ShowInteractionWidget()
{
}

void ABaseInteractable::HideInteractionWidget()
{
}
