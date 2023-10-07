// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCustomizeSlot.h"


// Sets default values
APlayerCustomizeSlot::APlayerCustomizeSlot()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCustomizeSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCustomizeSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCustomizeSlot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCustomizeSlot::SetPlayerIndex(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

