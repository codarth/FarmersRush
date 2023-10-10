// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCustomizePawn.h"

#include "EnhancedInputComponent.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "LocalMultiplayer/Core/MainMenu/MainMenu_GameMode.h"
#include "LocalMultiplayer/UI/MainMenu/MainMenuWidget.h"
#include "LocalMultiplayer/UI/MainMenu/PlayerSlot.h"


// Sets default values
APlayerCustomizePawn::APlayerCustomizePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCustomizePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCustomizePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCustomizePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind input actions Join
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(JoinAction, ETriggerEvent::Triggered, this, &APlayerCustomizePawn::Join);
	}
}

void APlayerCustomizePawn::SetPlayerIndex(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;
}

void APlayerCustomizePawn::Join(const FInputActionValue& Value)
{
	// Print to screen and log
	const FString Message = FString::Printf(TEXT("Player %d joined"), PlayerIndex);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);

	// Check if PlayerCustomizerSlotBox if visible if not make it visible
	if (const AMainMenu_GameMode* GameMode = Cast<AMainMenu_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (const auto MainMenu = Cast<UMainMenuWidget>(GameMode->MainMenuWidget))
		{
			if (MainMenu->PlayerSlotBox->GetVisibility() != ESlateVisibility::Visible)
			{
				MainMenu->PlayerSlotBox->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	
	// Get main menu widget and set the Player customizer Box slot visibility to visible
	if (const AMainMenu_GameMode* GameMode = Cast<AMainMenu_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (const auto MainMenu = Cast<UMainMenuWidget>(GameMode->MainMenuWidget))
		{
			if (auto SlotChildren = MainMenu->PlayerSlotBox->GetAllChildren(); SlotChildren.Num() > 0)
			{
				for (const auto Child : SlotChildren)
				{
					if (const auto Slot = Cast<UPlayerSlot>(Child))
					{
						if(Slot->PlayerIndex == PlayerIndex)
						{
							Slot->SetVisibility(ESlateVisibility::Visible);
						}
					}
				}
			}
		}		
	}
}

