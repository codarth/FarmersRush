// Fill out your copyright notice in the Description page of Project Settings.


#include "InputReciever_FR.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/ZZZTesting/GameMode_FR.h"
#include "LocalMultiplayer/ZZZTesting/CharacterCustomizeWidget.h"

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
		// Menu Left
		Input->BindAction(MenuLeftAction, ETriggerEvent::Triggered, this, &AInputReciever_FR::MenuLeft);
		// Menu Right
		Input->BindAction(MenuRightAction, ETriggerEvent::Triggered, this, &AInputReciever_FR::MenuRight);
	}
}

void AInputReciever_FR::Start(const FInputActionValue& Value)
{
	auto* GM = Cast<AGameMode_FR>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		if (!GM->bIsInGame)
		{
			if (CharacterCustomizeWidget)
			{
				GM->Execute_SpawnPlayerAtInputReceiver(GM, PlayerIndex, this, CharacterCustomizeWidget->CharacterColorChoice);
				CharacterCustomizeWidget->RemoveFromParent();
				CharacterCustomizeWidget = nullptr;
			}
			else
			{
				GM->Execute_DisplayCharacterCustomize(GM, PlayerIndex);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get GameMode"));
	}

}

void AInputReciever_FR::MenuLeft(const FInputActionValue& Value)
{
	if (CharacterCustomizeWidget)
	{
		CharacterCustomizeWidget->SwitchCharacterColor(-1);
	}
}

void AInputReciever_FR::MenuRight(const FInputActionValue& Value)
{
	if (CharacterCustomizeWidget)
	{
		CharacterCustomizeWidget->SwitchCharacterColor(1);
	}
}
