// Fill out your copyright notice in the Description page of Project Settings.


#include "InputReciever_FR.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Core/GameMode_FR.h"

void AInputReciever_FR::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context
	if (const APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

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

	auto* GM = Cast<AGameMode_FR>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->Execute_SpawnPlayerAtInputReceiver(GM, PlayerIndex, this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get GameMode"));
	}
}
