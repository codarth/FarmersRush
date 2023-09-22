// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode_FR.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Character/InputReciever_FR.h"

void AGameMode_FR::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Change this to just find a random player start
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	
	for (auto* PlayerStart : PlayerStarts)
	{
		const int32 Index = FCString::Atoi(*Cast<APlayerStart>(PlayerStart)->PlayerStartTag.ToString());;
		
		if (PlayerStart)
		{
			// Create a new player if not already created for this player start, or get and possess
			if (!UGameplayStatics::GetPlayerController(this, Index))
			{
				UGameplayStatics::CreatePlayer(this, Index, true);

				const auto InputReceiver = SpawnInputReceiver(PlayerStart, Index);

				const auto PC = UGameplayStatics::GetPlayerController(this, Index);
				PlayerControllers.AddUnique(PC);

				PC->Possess(InputReceiver);
			}
			else
			{
				auto PC = UGameplayStatics::GetPlayerController(this, Index);
				
				const auto InputReceiver = SpawnInputReceiver(PlayerStart, Index);

				PC->Possess(InputReceiver);
			}
		}
	}
}

AInputReciever_FR* AGameMode_FR::SpawnInputReceiver(AActor* PlayerStart, const int32 Index)
{
	// Spawn the InputReceiver and set its player index
	// const auto InputReceiver = Cast<AInputReciever_FR>(GetWorld()->SpawnActor(AInputReciever_FR::StaticClass(), &PlayerStart->GetActorTransform()));
	const auto InputReceiver = GetWorld()->SpawnActor<AInputReciever_FR>(InputReceiverToSpawn, PlayerStart->GetActorTransform());
	InputReceiver->PlayerIndex = Index;
	InputReceivers.AddUnique(InputReceiver);

	return InputReceiver;
}

void AGameMode_FR::SpawnPlayer_Implementation(int32 CurrentPlayerIndex, AInputReciever_FR* InputReceiver)
{
	UE_LOG(LogTemp, Display, TEXT("SpawnPlayer"));
}
