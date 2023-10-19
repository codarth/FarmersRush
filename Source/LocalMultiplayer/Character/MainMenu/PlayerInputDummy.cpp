// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputDummy.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Core/MainMenu/MainMenu_GameMode.h"


// Called when the game starts or when spawned
void APlayerInputDummy::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context
	if (const auto PC = Cast<APlayerController>(Controller))
	{
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void APlayerInputDummy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(ActivatePlayerAction, ETriggerEvent::Triggered, this, &APlayerInputDummy::ActivatePlayer);
	}
}

void APlayerInputDummy::ActivatePlayer(const FInputActionValue& Value)
{
	auto GM = Cast<AMainMenu_GameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->SpawnCharacterAtDummy(this, PlayerIndex);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get GameMode"));
	}
}

