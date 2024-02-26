// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFarmerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Core/FarmersRush_GameMode.h"
#include "Components/CapsuleComponent.h"
#include "LocalMultiplayer/Actors/Items/BaseInteractable.h"
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

void APlayerFarmerCharacter::AddCamera()
{
	const auto SpringArm = NewObject<USpringArmComponent>(this, USpringArmComponent::StaticClass(), FName("Boom"));
	SpringArm->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
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
		if (const auto Interactable = Cast<ABaseInteractable>(HitActor))
		{
			if (const auto Interface = Cast<IInteract_Interface>(Interactable))
			{
				Interface->Interact();
			}
		}
	}
}





