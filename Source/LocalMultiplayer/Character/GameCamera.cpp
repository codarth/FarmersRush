// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Character/Player_FR.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	DebugSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugSphere"));
	RootComponent = DebugSphere;
	DebugSphere->SetHiddenInGame(!bDebuggingCamera);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(DebugSphere);
	CameraBoom->TargetArmLength = 2000.0f;
	CameraBoom->SetRelativeRotation(FRotator(0.f,40.f,0.f));
	CameraBoom->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();

	DebugSphere->SetHiddenInGame(!bDebuggingCamera);
}

void AGameCamera::CalculateCameraMovement()
{
	auto PreviousLocation = DebugSphere->GetComponentLocation();

	TArray<AActor*> ActorArray;
	for (APlayer_FR* Player : ActivePlayers)
	{
		ActorArray.Add(Player); 
	}

	DebugSphere->SetWorldLocation(FMath::Lerp(PreviousLocation, UGameplayStatics::GetActorArrayAverageLocation(ActorArray), LerpSpeed));
}

void AGameCamera::CalculateCameraZoom()
{
	TArray<float> Distances;
	for (int32 i = 0; i < ActivePlayers.Num(); i++)
	{
		for (int32 j = i + 1; j < ActivePlayers.Num(); j++)
		{
			Distances.Add(FVector::Dist(ActivePlayers[i]->GetActorLocation(), ActivePlayers[j]->GetActorLocation()));
		}
	}

	float Max = 0.f;
	for (int32 i = 0; i < Distances.Num(); i++)
	{
		Max = FMath::Max(Distances[i], Max);
	}

	CameraBoom->TargetArmLength = FMath::Clamp(Max, MinBoom, MaxBoom);
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGameStarted)
	{
		CalculateCameraMovement();

		CalculateCameraZoom();
	}
}

void AGameCamera::GameStarted(TArray<APlayer_FR*> InActivePlayers)
{
	ActivePlayers = InActivePlayers;
	bIsGameStarted = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
}

