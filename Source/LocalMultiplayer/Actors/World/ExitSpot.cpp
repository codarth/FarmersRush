// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitSpot.h"

#include "Components/BoxComponent.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"
#include "LocalMultiplayer/Core/Interfaces/Countdown_Interface.h"

// Sets default values
AExitSpot::AExitSpot()
{
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
	OverlapBox->SetBoxExtent(FVector(100.f, 100.f, 100.f), true);
	OverlapBox->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	ExitSpot_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExitSpot_Mesh"));
	ExitSpot_Mesh->SetupAttachment(RootComponent);

	ExitSpot_Destination = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExitSpot_Destination"));
	ExitSpot_Destination->SetupAttachment(ExitSpot_Mesh);

}

// Called when the game starts or when spawned
void AExitSpot::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AExitSpot::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AExitSpot::OnOverlapEnd);

}

// Called every frame
void AExitSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExitSpot::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto Player = Cast<APlayerFarmerCharacter>(OtherActor))
	{
		if (const auto Interface = Cast<ICountdown_Interface>(Player))
		{
			Interface->BeginQuitCountdown(bToMainMenu);
		}
	}
}

void AExitSpot::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (const auto Player = Cast<APlayerFarmerCharacter>(OtherActor))
	{
		if (const auto Interface = Cast<ICountdown_Interface>(Player))
		{
			Interface->StopQuitCountdown();
		}
	}
}

