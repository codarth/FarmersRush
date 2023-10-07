// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCustomizer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Called when the game starts or when spawned
void APlayerCustomizer::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void APlayerCustomizer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Joining
		EnhancedInputComponent->BindAction(JoinAction, ETriggerEvent::Triggered, this, &APlayerCustomizer::Join);
	}
}

void APlayerCustomizer::Join(const FInputActionValue& Value)
{
	// Print Join to screen
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Join"));
}

