// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStartSpot.h"

#include "Components/BoxComponent.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"

APlayerStartSpot::APlayerStartSpot()
{
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerStartSpot::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &APlayerStartSpot::OnOverlapEnd);
	OverlapBox->SetBoxExtent(FVector(100.f, 100.f, 100.f), true);
	OverlapBox->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	StartSpot_Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartSpot_Plane"));
	StartSpot_Plane->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerStartSpot::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < PlayerMaterials.Num(); i++)
	{
		StartSpot_Plane->SetMaterial(i, DefaultMaterial);
	}
}

// Called every frame
void APlayerStartSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerStartSpot::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Player = Cast<APlayerFarmerCharacter>(OtherActor);
	if (Player)
	{
		StartSpot_Plane->SetMaterial(Player->PlayerIndex, PlayerMaterials[Player->PlayerIndex]);
		Player->bIsPlayerReady = true;
	}
}

void APlayerStartSpot::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const auto Player = Cast<APlayerFarmerCharacter>(OtherActor);
	if (Player)
	{
		StartSpot_Plane->SetMaterial(Player->PlayerIndex, DefaultMaterial);
		Player->bIsPlayerReady = false;
	}

}

