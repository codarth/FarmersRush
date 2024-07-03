// Fill out your copyright notice in the Description page of Project Settings.


#include "DevGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Character/PlayerFarmerCharacter.h"


ADevGameMode::ADevGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADevGameMode::BeginPlay()
{
	Super::BeginPlay();

	const auto PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		auto Character = Cast<APlayerFarmerCharacter>(PC->GetCharacter());
		if (Character)
		{
			Character->AddCamera();
		}
	}
}