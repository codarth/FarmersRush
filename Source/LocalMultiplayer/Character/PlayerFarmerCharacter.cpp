// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFarmerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Core/FarmersRush_GameMode.h"
#include "Components/CapsuleComponent.h"
#include "LocalMultiplayer/Actors/Items/BaseInteractable.h"
#include "LocalMultiplayer/Core/Interfaces/Interact_Interface.h"
#include <LocalMultiplayer/Core/Dev/DevGameMode.h>

// cvar for debugging character
static TAutoConsoleVariable<int32> CVarDebugCharacter(
	TEXT("LocalMultiplayer.DebugCharacter"),
	0,
	TEXT("Enable Debug for PlayerFarmerCharacter"),
	ECVF_Cheat);


// Sets default values
APlayerFarmerCharacter::APlayerFarmerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 225.0f;
}

// Called when the game starts or when spawned
void APlayerFarmerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context
	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	// Interaction
	InteractionCheckHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	InteractionCheckRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();

	GetWorldTimerManager().SetTimer(InteractionCheckTimerHandle, this, &APlayerFarmerCharacter::CheckForInteractable,
	                                InteractionCheckFrequency, true, 1.0f);

	// Set the player color
	GetMesh()->SetMaterial(1, PlayerDefaultColor);

	// Set the game mode reference
	GameModeRef = Cast<AFarmersRush_GameMode>(UGameplayStatics::GetGameMode(this));

	if (auto CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		CameraManager->ViewPitchMin = MinPitch;
		CameraManager->ViewPitchMax = MaxPitch;
	}
}

void APlayerFarmerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(InteractionCheckTimerHandle);
}

// Called every frame
void APlayerFarmerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

// Called to bind functionality to input
void APlayerFarmerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerFarmerCharacter::Move);
		Input->BindAction(CameraMovementAction, ETriggerEvent::Triggered, this,
		                  &APlayerFarmerCharacter::CameraMovement);
		Input->BindAction(ZoomCameraAction, ETriggerEvent::Triggered, this, &APlayerFarmerCharacter::ZoomCamera);
		Input->BindAction(DeactivatePlayerAction, ETriggerEvent::Triggered, this,
		                  &APlayerFarmerCharacter::DeactivatePlayer);

		Input->BindAction(InteractionAction, ETriggerEvent::Started, this, &APlayerFarmerCharacter::BeginInteract);
		Input->BindAction(InteractionAction, ETriggerEvent::Completed, this, &APlayerFarmerCharacter::EndInteract);
	}
}

void APlayerFarmerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// Forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerFarmerCharacter::CameraMovement(const FInputActionValue& Value)
{
	if (Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this)) || GameModeRef->bStartingGame)
	{
		const FVector2D RotationVector = Value.Get<FVector2D>();

		if (IsValid(Controller))
		{
			AddControllerYawInput(RotationVector.X * CameraSensitivity);
			AddControllerPitchInput(RotationVector.Y * CameraSensitivity);
		}
	}
}

void APlayerFarmerCharacter::ZoomCamera(const FInputActionValue& Value)
{
	if (Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this)) || GameModeRef->bStartingGame)
	{
		const float ZoomValue = Value.Get<float>();

		if (IsValid(Controller) && IsValid(SpringArm))
		{
			float NewLength = SpringArm->TargetArmLength + ZoomValue * CameraZoomSensitivity;
			SpringArm->TargetArmLength = FMath::Clamp(NewLength, MinCameraZoom, MaxCameraZoom);
		}
	}
}

void APlayerFarmerCharacter::DeactivatePlayer(const FInputActionValue& Value)
{
	if (!GameModeRef->bStartingGame)
	{
		// Remove camera and deactivate player
		SpringArm = nullptr;
		Camera = nullptr;

		GameModeRef->DeactivatePlayer(PlayerIndex);
	}
}

void APlayerFarmerCharacter::AddCamera()
{
	SpringArm = NewObject<USpringArmComponent>(this, USpringArmComponent::StaticClass(), FName("Boom"));
	SpringArm->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->RegisterComponent();
	AddInstanceComponent(SpringArm);

	Camera = NewObject<UCameraComponent>(SpringArm, UCameraComponent::StaticClass(), FName("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	Camera->RegisterComponent();
	AddInstanceComponent(Camera);
}

void APlayerFarmerCharacter::BeginQuitCountdown(bool bToMainMenu)
{
	GameModeRef->BeginQuitCountdown(bToMainMenu);
}

void APlayerFarmerCharacter::UpdateQuitTimer()
{
	GameModeRef->UpdateQuitTimer();
}

void APlayerFarmerCharacter::StopQuitCountdown()
{
	GameModeRef->StopQuitCountdown();
}

/** Interaction */
void APlayerFarmerCharacter::CheckForInteractable()
{
	// FVector TraceStart = GetActorLocation();
	// FVector TraceEnd = TraceStart + GetActorForwardVector() * InteractionCheckDistance;
	//
	// FHitResult HitResult;
	// FCollisionQueryParams QueryParams;
	// QueryParams.AddIgnoredActor(this);
	//
	// FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(InteractionCheckRadius, InteractionCheckHalfHeight);
	//
	// bool bHit = GetWorld()->SweepSingleByChannel(HitResult, TraceStart, TraceEnd, FQuat::Identity, ECC_Visibility,
	//                                              CollisionShape, QueryParams);
	//
	// if (CVarDebugCharacter.GetValueOnGameThread())
	// {
	// 	// Debug line
	// 	DrawDebugCapsule(GetWorld(), TraceStart, InteractionCheckHalfHeight, InteractionCheckRadius, FQuat::Identity,
	// 	                 FColor::Red, false, 1.0f, 0, 1.0f);
	// 	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 1, 0, 1);
	// }
	//
	// if (bHit)
	// {
	// 	AActor* HitActor = HitResult.GetActor();
	// 	if (const auto Interactable = Cast<ABaseInteractable>(HitActor))
	// 	{
	// 		if (const auto Interface = Cast<IInteract_Interface>(Interactable))
	// 		{
	// 			Interactable->InteractingColor = PlayerDefaultColor;
	// 			Interface->Interact();
	// 		}
	// 	}
	// }
}

void APlayerFarmerCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart{GetPawnViewLocation()};
	FVector TraceEnd{TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance)};

	// Are we looking in the same direction as the character
	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());
	if (LookDirection > 0) // Changing 0 to some thing greater will reduce the angle of interaction
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f, 0, 2.0f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;

		if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
		{
			if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteract_Interface::StaticClass()))
			{
				const float Distance = (TraceStart - TraceHit.ImpactPoint).Size();
				if (TraceHit.GetActor() != InteractionData.CurrentInteractable && Distance <= InteractionCheckDistance)
				{
					FoundInteractable(TraceHit.GetActor());
					return;
				}

				if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
				{
					return;
				}
			}
		}
	}

	NoInteractableFound();
}

void APlayerFarmerCharacter::FoundInteractable(AActor* NewInteractable)
{
	// Somehow we found a new interactable when we had one. Should not happen (often).
	if (IsInteracting())
	{
		EndInteract();
	}

	// Already have an interactable, clear the focus
	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	// Set the new interactable
	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	// Begin focus on the new interactable
	TargetInteractable->BeginFocus();
}

void APlayerFarmerCharacter::NoInteractableFound()
{
	// Clear the timer
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	// End focus on the current interactable
	if (InteractionData.CurrentInteractable)
	{
		// Make sure interactable is not destroyed before we end focus
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		// Hide the interaction widget on the HUD

		// Clear the current interactable
		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void APlayerFarmerCharacter::BeginInteract()
{
	// Fail safe, Verify nothing has changed with the interactable state since we last checked
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();

			// Check if the interaction is instant
			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction, this, &APlayerFarmerCharacter::Interact,
				                                TargetInteractable->InteractableData.InteractionDuration, false);
			}
		}
	}
}

void APlayerFarmerCharacter::EndInteract()
{
	// Clear the timer
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	// End the interaction
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void APlayerFarmerCharacter::Interact()
{
	// Clear the timer
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	// Interact with the interactable
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact();
	}

}
