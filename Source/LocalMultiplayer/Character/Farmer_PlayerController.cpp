// Fill out your copyright notice in the Description page of Project Settings.


#include "Farmer_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"
#include "LocalMultiplayer/Core/FarmersRush_GameMode.h"
#include "Kismet/GameplayStatics.h"

void AFarmer_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = Cast<APlayerFarmerCharacter>(GetCharacter());

	//if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	//{
	//	Subsystem->AddMappingContext(MappingContext, 0);
	//}
}

void AFarmer_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFarmer_PlayerController::Move);
	}
}

void AFarmer_PlayerController::Move(const FInputActionValue& Value)
{
	// print debug message
	UE_LOG(LogTemp, Warning, TEXT("Move"));

	//// input is a Vector2D
	//const FVector2D MovementVector = Value.Get<FVector2D>();

	//if (CharacterRef != nullptr)
	//{
	//	// find out which way is forward
	//	const FRotator Rotation = GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//	// get forward vector
	//	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//	// get right vector 
	//	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//	// add movement 
	//	CharacterRef->AddMovementInput(ForwardDirection, MovementVector.Y);
	//	CharacterRef->AddMovementInput(RightDirection, MovementVector.X);
	//}
}
