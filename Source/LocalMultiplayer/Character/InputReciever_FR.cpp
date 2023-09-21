// Fill out your copyright notice in the Description page of Project Settings.


#include "InputReciever_FR.h"
#include "EnhancedInputComponent.h"

void AInputReciever_FR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Start
		Input->BindAction(StartAction, ETriggerEvent::Triggered, this, &AInputReciever_FR::Start);
	}
}

void AInputReciever_FR::Start(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Start"));
}
