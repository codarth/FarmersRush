// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMainMenuCamera::AMainMenuCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(false);

	DebugSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugSphere"));
	RootComponent = DebugSphere;
	DebugSphere->SetHiddenInGame(!bDebuggingCamera);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.0f;
	CameraBoom->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
}

// Called when the game starts or when spawned
void AMainMenuCamera::BeginPlay()
{
	Super::BeginPlay();

	DebugSphere->SetHiddenInGame(!bDebuggingCamera);
}

// Called every frame
void AMainMenuCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

