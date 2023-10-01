// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LocalMultiplayer/Character/Player_FR.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DebugSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugSphere"));
	RootComponent = DebugSphere;
	DebugSphere->SetHiddenInGame(bDebuggingCamera);

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
	
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameCamera::GameStarted(TArray<APlayer_FR*> ActivePlayers)
{
}

