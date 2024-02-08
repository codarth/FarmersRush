// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFarmerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Core/FarmersRush_GameMode.h"
#include "Components/CapsuleComponent.h"
#include "LocalMultiplayer/Actors/Items/Interactable.h"
#include "LocalMultiplayer/Core/Interfaces/Interact_Interface.h"

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
}

// Called when the game starts or when spawned
void APlayerFarmerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context
	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	InteractionCheckHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	InteractionCheckRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	
	GetWorldTimerManager().SetTimer(InteractionCheckTimerHandle, this, &APlayerFarmerCharacter::CheckForInteractable, InteractionCheckFrequency, true, 1.0f);
	
	GetMesh()->SetMaterial(1, PlayerDefaultColor);

	GameModeRef = Cast<AFarmersRush_GameMode>(UGameplayStatics::GetGameMode(this));
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
}

// Called to bind functionality to input
void APlayerFarmerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerFarmerCharacter::Move);
		Input->BindAction(DeactivatePlayerAction, ETriggerEvent::Triggered, this, &APlayerFarmerCharacter::DeactivatePlayer);
	}
}

void APlayerFarmerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerFarmerCharacter::DeactivatePlayer(const FInputActionValue& Value)
{
	if (const auto GM = Cast<AFarmersRush_GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (!GM->bStartingGame)
		{
			GM->DeactivatePlayer(PlayerIndex);
		}
	}
}

void APlayerFarmerCharacter::AddCamera()
{
	const auto SpringArm = NewObject<USpringArmComponent>(this, USpringArmComponent::StaticClass(), FName("Boom"));
	SpringArm->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArm->RegisterComponent();
	AddInstanceComponent(SpringArm);

	const auto Camera = NewObject<UCameraComponent>(SpringArm, UCameraComponent::StaticClass(), FName("Camera"));
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
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + GetActorForwardVector() * InteractionCheckDistance;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(InteractionCheckRadius, InteractionCheckHalfHeight);

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, TraceStart, TraceEnd, FQuat::Identity, ECC_Visibility, CollisionShape, QueryParams);

	if (CVarDebugCharacter.GetValueOnGameThread())
	{
		// Debug line
		DrawDebugCapsule(GetWorld(), TraceStart, InteractionCheckHalfHeight, InteractionCheckRadius, FQuat::Identity, FColor::Red, false, 1.0f, 0, 1.0f);
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 1, 0, 1);
	}

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (const auto Interactable = Cast<AInteractable>(HitActor))
		{
			if (const auto Interface = Cast<IInteract_Interface>(Interactable))
			{
				Interface->Interact();
			}
		}
	}
}





